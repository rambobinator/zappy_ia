#ifndef COOP_HPP
# define COOP_HPP

#include <iostream>
#include "Inventory.hpp"
#include "Point.hpp"

class Coop
{
	public:
		Coop();
		Coop(int id, int dir, std::string team, Inventory &inventory);
		Coop( Coop const & src );
		~Coop();
		Coop &		operator=( Coop const & rhs );
		int			role;
		int			id;
		int			dir;
		Point		coord;
		std::string	team;
		Inventory	inventory;

	private:

};

std::ostream & 		operator<<(std::ostream &o, Coop const &rhs);

#endif