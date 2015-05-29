#ifndef INVENTORY_HPP
# define INVENTORY_HPP

#include <iostream>
#include <map>

class Inventory
{
	public:
		Inventory();
		Inventory( Inventory const & src );
		~Inventory();
		Inventory &		operator=( Inventory const & rhs );
		void			init_player_stuff(void);

	private:
		std::map<std::string, int>	_data;
};

std::ostream & 		operator<<(std::ostream &o, Inventory const &rhs);

#endif