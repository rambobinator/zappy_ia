/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brehaili <brehaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 15:53:01 by brehaili          #+#    #+#             */
/*   Updated: 2015/05/26 15:53:03 by brehaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "Client.hpp"
#include "Icmd.hpp"

Client::Client(char **av) : team_name(av[1]), args(av) {
	busy = true;
	id = getpid();
	inventory.init_player_stuff();
	coord = new Point(0, 0);
	msgs = new Messages(av[1], id, &inventory);
	msgs_callback[ROLL_CALL] = &Client::send_present;
	msgs_callback[PRESENT] = &Client::count_team;
	this->sock = this->connect(av[3], av[2]);
	this->cmd_tab = {
		{"message", &Client::cmd_broadcast},
		{"mort", &Client::cmd_die},
		{"deplacement", &Client::cmd_expulse}
	};
}

Client::~Client(){
}

int		Client::connect(std::string ip, std::string port) {
	struct addrinfo			hints;
	struct addrinfo			*res;
	int						sock;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = getprotobyname("tcp")->p_proto;
	if (getaddrinfo(ip.c_str(), port.c_str(), &hints, &res) != 0)
	{
		std::cout << "getaddrinfo error" << std::endl;
		exit(2);
	}
	while (res)
	{
		sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if ((::connect(sock, res->ai_addr, res->ai_addrlen)) != -1)
			return (sock);
		close(sock);
		res = res->ai_next;
	}
	std::cout << "connect error" << std::endl;
	exit(2);
}

void	Client::process(void) {
	std::list<Icmd*>::iterator		tmp;

	tmp = this->list_cmd.begin();
	while (tmp != this->list_cmd.end()) {
		if ((*tmp)->_done == false) {
			(*tmp)->execute();
		}
		tmp++;
	}
	if (!busy )//&& !list_cmd.size())
		ia.think(*this); /*     <---------------------     HERE IS THE BLACK BOX*/
}

void	Client::loop_client(void){
	while (1) {
		FD_ZERO(&this->read_fds);
		FD_ZERO(&this->write_fds);
		FD_SET(this->sock, &this->read_fds);
		FD_SET(this->sock, &this->write_fds);
		select(this->sock + 1, &this->read_fds, &this->write_fds, NULL, NULL);
		this->test_read();
		this->process();
		this->test_write();
	}
}

void	Client::test_read(void) {
	int		size;
	char	str[BUFF_SIZE];

	if (FD_ISSET(this->sock, &this->read_fds) != 0) {
		if ((size = read(this->sock, str, BUFF_SIZE)) == 0)
			this->quit();
		str[size] = '\0';
		this->buf_read.add(str);
		this->process_read();
	}
}

void	Client::process_read(void) {
	std::string		tmp;
	size_t			nb;

	tmp = this->buf_read.to_str();
	while ((nb = tmp.find("\n")) != std::string::npos) {
		this->parse_cmd(tmp.substr(0, nb));
		tmp.erase(0, nb + 1);
		this->buf_read.del(nb + 1);
	}
}

void	Client::parse_cmd(std::string cmd) {
	std::string		first;

	void (Client::*test)(std::string);

	first = cmd.substr(0, cmd.find(" "));
	if (this->cmd_tab.find(first) != this->cmd_tab.end()) {
		test = this->cmd_tab[first];
		(this->*test)(cmd);
	}
	else
		this->cmd_answer(cmd);
}

void	Client::test_write(void) {
	int			size;
	std::string	str;

	if (FD_ISSET(this->sock, &this->write_fds) != 0) {
		str = this->buf_write.to_str();
		size = str.size();
		write(this->sock, str.c_str(), size);
		this->buf_write.del(size);
	}
}

void	Client::quit(void) {
	exit(2);
}

void	Client::new_client(void) {
	pid_t	pid;

	if ((pid = fork()) == 0)
		execve("client", this->args, NULL);
}

void	Client::read_messages(void){ /*STACK THE RIGHT CMD DEPENDING ON THE ORDERS*/
	std::string			buf;
	std::stringstream	ss;
	int					callback_code;

	for (std::list<Message *>::iterator it = msgs->recv.begin(); it != msgs->recv.end(); it++)
	{
		if (!(*it)->read)
		{
			ss.str((*it)->data);
			while (ss >> buf)
			{
				callback_code = stoi(buf);
				if (callback_code > 0 && callback_code < CMD_CALLBACK_NBR)
					(*this.*msgs_callback[callback_code])(*it); /*WTF*/
			}
			(*it)->read = true;
			// std::cout << *msgs;/*RM*/
		}
	}
}

void	Client::cmd_broadcast(std::string cmd) {/*CLIENT RECEIVE <message>*/
	msgs->receive(cmd);

	/*HERE SHOULD DEFINE IF THE ACTUAL GOAL ISN'T BLOCKING*/
	/*if ...*/
	read_messages();
}

void	Client::cmd_die(std::string cmd) {/*CLIENT RECEIVE <mort>*/
	(void)cmd;
	std::cout << "YOU DIED !" << std::endl;
	quit();
}

void	Client::cmd_expulse(std::string cmd) {/*CLIENT RECEIVE <deplacement>*/
	(void)cmd;
	std::cout << "EXPULSED" << std::endl;
}

void	Client::cmd_answer(std::string cmd) {/*CLIENT RECEIVE AN OTHER CMD*/
	(void)cmd;
	std::list<Icmd*>::iterator	tmp;

	if (cmd.compare("BIENVENUE") == 0)
		this->list_cmd.push_back(new Welcome(*this));
	else {
		tmp = this->list_cmd.begin();
		while (tmp != this->list_cmd.end()) {
			if ((*tmp)->_done == true) {
				(*tmp)->parseAnswer(cmd);
				return ;
			}
			tmp++;
		}
	}
}

/*CALLBACK IMPLEMENTATIONS*/

void		Client::send_present(Message *mes){
	(void)mes;
	list_cmd.push_back(new Broadcast(*this, args2string(1, PRESENT)));
}

bool		sort_by_pid(Coop *a, Coop *b){return (a->id < b->id);} /*COUNT UTILS*/
bool		unique_by_pid(Coop *a, Coop *b){return (a->id == b->id);}/*COUNT UTILS*/

void		Client::count_team(Message *mes){
	if (mes->team != team_name)
		return ;
	others.push_back(new Coop(mes->id, mes->dir, mes->team, mes->inventory));
	others.sort(sort_by_pid);
	others.unique(unique_by_pid);
	std::cout << "WE ARE " << others.size() << " CURRENTLY IN GAME " << std::endl; /*DEBUG BUT WORKING :)*/
	// for (std::list<Coop *>::iterator it = others.begin(); it != others.end(); it++)
	// 	std::cout << "MESS by " << *(*it) << std::endl;
}
