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
	msgs_callback[SET_AS_FEEDER] = &Client::set_as_feeder;
	msgs_callback[SET_AS_PICKER] = &Client::set_as_picker;
	msgs_callback[FOLLOW_ME] = &Client::follow_me;
	msgs_callback[I_AM_HERE] = &Client::i_am_here;
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
		{
			freeaddrinfo(res);
			return (sock);
		}
		close(sock);
		res = res->ai_next;
	}
	std::cout << "connect error" << std::endl;
	exit(2);
}

void	Client::process(void) {
	std::list<Icmd*>::iterator		tmp;
	int								i;

	i = 0;
	tmp = this->list_cmd.begin();
	while (tmp != this->list_cmd.end() && i < 10) {
		if ((*tmp)->_done == false) {
			(*tmp)->execute();
		}
		tmp++;
		i++;
	}
	if (!busy && list_cmd.size() <= 10){
		std::cout << "-----" << id << "---" << "thinking" << std::endl;
		ia.think(*this); /*     <---------------------     HERE IS THE BLACK BOX*/
	}
}

void	Client::loop_client(void){
	struct timeval    timeout;

    timeout.tv_sec = 0;
    timeout.tv_usec = 0;
	while (1) {
		FD_ZERO(&this->read_fds);
		FD_ZERO(&this->write_fds);
		FD_SET(this->sock, &this->read_fds);
		if (this->buf_write.to_str().size() > 0)
			FD_SET(this->sock, &this->write_fds);
		select(this->sock + 1, &this->read_fds, &this->write_fds, NULL, &timeout);
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
				{
					if (!(*it)->adressee) /*WE ALL DOING IT*/
						(*this.*msgs_callback[callback_code])(*it); /*WTF*/
					else if ((*it)->adressee == id) /*EXCEPTION FOR THIS ID*/
						(*this.*msgs_callback[callback_code])(*it); /*WTF*/
				}
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
	std::cout << id << "YOU DIED !" << std::endl;
	quit();
}

void	Client::cmd_expulse(std::string cmd) {/*CLIENT RECEIVE <deplacement>*/
	(void)cmd;
	std::cout << "EXPULSED" << std::endl;
}

void	Client::cmd_answer(std::string cmd) {/*CLIENT RECEIVE AN OTHER CMD*/
	(void)cmd;
	std::list<Icmd*>::iterator	tmp;

	if (cmd.compare("BIENVENUE") == 0){
		std::cout << "Bienvenue !" << std::endl;
		this->list_cmd.push_back(new Welcome(*this));
	}
	else {
		tmp = this->list_cmd.begin();
		while (tmp != this->list_cmd.end()) {
			if ((*tmp)->_done == true) {
				(*tmp)->parseAnswer(cmd);
				if (this->list_cmd.size() == 0)
					this->busy = false;
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
	if ((*others.begin())->id == id)
		ia.role = MOTHER;
	else
		ia.role = FEEDER;
	std::cout << "WE ARE " << others.size() << " CURRENTLY IN GAME " << std::endl; /*DEBUG BUT WORKING :)*/
	// for (std::list<Coop *>::iterator it = others.begin(); it != others.end(); it++)
	// 	std::cout << "MESS by " << *(*it) << std::endl;
}

void				Client::set_as_feeder(Message *mes){
	(void)mes;
	ia.role = FEEDER;
}

void				Client::set_as_picker(Message *mes){
	(void)mes;
	ia.role = PICKER;
}

std::vector<Point>	g_tab_dir = {
	{0,-1},
	{-1,-1},
	{-1,0},
	{-1,1},
	{0,1},
	{1,1},
	{1,0},
	{1,-1}
};

Point				Client::pivot_p(Point p, int dir) {
	Point	a;

	if (dir == 0) {
		a.x = p.x;
		a.y = p.y;
	}
	else if (dir == 1) {
		a.x = -p.y;
		a.y = p.x;
	}
	else if (dir == 2) {
		a.x = -p.x;
		a.y = -p.y;
	}
	else if (dir == 3) {
		a.x = p.y;
		a.y = -p.x;
	}
	return (a);
}

void				Client::follow_me(Message *mes) {
	Point	tmp;
	std::list<Icmd*>	li;

	tmp = pivot_p(g_tab_dir[mes->dir - 1], map->direction);
	tmp = map->normalizer({tmp.x + map->x, tmp.y + map->y});
	li = map->best_path(tmp);
	list_cmd.splice(list_cmd.end(), li);
}

void				Client::i_am_here(Message *mes){
	(void)mes;
	/*HERE LAUCH GO TO THE DIR (BRICE)*/
}

