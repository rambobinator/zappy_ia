#ifndef MESSAGES_HPP
# define MESSAGES_HPP

#include <iostream>
#include <sstream>
#include <list>
#include <vector>
#include "Inventory.hpp"

enum	e_states
{
	END,
	PID,
	ROLL_CALL,
	PRESENT,
	SET_AS_FEEDER,
	SET_AS_PICKER,
	FOLLOW_ME,
	I_AM_HERE,
	CMD_CALLBACK_NBR
};

class Message
{
	public:
		Message(){
			adressee = 0;
			read = false;
		};
		Message(std::string team, int id, int dir, Inventory inv, std::string data) : team(team), id(id), dir(dir), inventory(inv), data(data), read(false), adressee(0){};
		~Message();
		std::string			team;
		int					id;
		int					adressee;
		int					dir;
		Inventory			inventory;
		std::string			data;
		bool				read;
};

class Messages
{
	public:
		Messages();
		Messages(std::string team, int id, Inventory *inventory);
		Messages( Messages const & src );
		~Messages();
		Messages &				operator=( Messages const & rhs );
		void					setTeam(std::string team_name);
		std::string				getTeam(void) const;
		void					receive(std::string cmd);
		std::string				sending(std::string cmd);
		std::list<Message *>	recv;

	private:
		Inventory		*_my_inventory;
		std::string		_team_name;
		int				_id;
};

std::ostream & 		operator<<(std::ostream &o, Message const &rhs);
std::ostream & 		operator<<(std::ostream &o, Messages const &rhs);

#endif
