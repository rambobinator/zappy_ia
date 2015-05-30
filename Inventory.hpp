#ifndef INVENTORY_HPP
# define INVENTORY_HPP

#include <iostream>
#include <sstream>
#include <map>

class Inventory
{
	public:
		Inventory();
		Inventory( Inventory const & src );
		~Inventory();
		Inventory &		operator=( Inventory const & rhs );
		void			init_player_stuff(void);
		std::map<std::string, int>	getData(void)const;
		void						setData(std::stringstream &ss);

	private:
		std::map<std::string, int>	_data;
};

std::ostream & 		operator<<(std::ostream &o, Inventory const &rhs);

#endif