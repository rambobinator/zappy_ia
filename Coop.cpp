#include "Coop.hpp"

Coop::Coop( void )
{
}

Coop::Coop(int id, int dir, std::string team, Inventory &inventory) : id(id), dir(dir), team(team), inventory(inventory){
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
	(void)rhs;
	o << "";
	return o;
}
