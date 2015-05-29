/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brehaili <brehaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 15:53:09 by brehaili          #+#    #+#             */
/*   Updated: 2015/05/26 15:53:10 by brehaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <map>
#include <list>
#include <string>
#include "Buffer.hpp"
#include "Inventory.hpp"
#include "Map.hpp"

class Icmd;

class Client
{
	public:
		Client(){};
		Client(char **av);
		~Client();
		Client &			operator=(const Client & obj);
		std::list<Icmd*>	list_cmd;
		Inventory			inventory;
		Buffer				buf_read;
		Buffer				buf_write;
		Map					*map;
		int					sock;
		int					remaining_slots;
		int					map_x;
		int					map_y;
		fd_set				read_fds;
		fd_set				write_fds;
		std::string			team_name;
		char				**args;
		void				start(void);
		void				process(void);
		void				loop_client(void);
		void				test_read(void);
		void				process_read(void);
		void				parse_cmd(std::string cmd);
		void				test_write(void);
		void				quit(void);
		int					connect(std::string ip, std::string port);
		void				new_client(void);

		/*DIRECT CMD*/
		void				cmd_broadcast(std::string cmd);
		void				cmd_die(std::string cmd);
		void				cmd_expulse(std::string cmd);
		void				cmd_answer(std::string cmd);
		std::map<std::string, void (Client::*)(std::string)>		cmd_tab;
		/*___________*/

	private:
};

#endif
