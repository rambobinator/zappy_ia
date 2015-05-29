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
	int				nb;

	tmp = this->buf_read.to_str();
													std::cout << tmp << std::endl;
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

void	Client::cmd_broadcast(std::string cmd) {
	(void)cmd;
	std::cout << "BRODCASTED" << std::endl;
}

void	Client::cmd_die(std::string cmd) {
	(void)cmd;
	std::cout << "DIED" << std::endl;
}

void	Client::cmd_expulse(std::string cmd) {
	(void)cmd;
	std::cout << "EXPULSED" << std::endl;
}

void	Client::cmd_answer(std::string cmd) {
	std::list<Icmd*>::iterator	tmp;

	std::cout << "cmd_answer: " << cmd << std::endl;
	if (cmd.compare("BIENVENUE") == 0)
		this->list_cmd.push_back(new Welcome(*this));
	else {
		tmp = this->list_cmd.begin();
		while (tmp != this->list_cmd.end()) {
			if ((*tmp)->_done == true) {
				std::cout << "DONE" << std::endl;
				(*tmp)->parseAnswer(cmd);
				return ;
			}
			tmp++;
		}
	}
}