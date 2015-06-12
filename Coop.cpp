#include "Coop.hpp"

Coop::Coop( void )
{
}

Coop::Coop(int id, int dir, std::string team, Inventory &inventory) : id(id), dir(dir), team(team), inventory(inventory){
	role = 0;
}

Coop::Coop( Coop const & src )
{
	*this = src;
}

Coop::~Coop( void )
{
}

Coop & Coop::operator=( Coop const & rhs )
{
	(void)rhs;
	return *this;
}

std::ostream & 		operator<<(std::ostream &o, Coop const &rhs)
{
	o << rhs.id << " -> " << rhs.team;
	return o;
}
