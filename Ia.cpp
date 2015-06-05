#include "Ia.hpp"
#include "Client.hpp"

Ia::Ia( void )
{
	role = ALONE;
	/*ROLES PTRS*/
	role_funct[ALONE] = &Ia::role_alone;
	role_funct[MOTHER] = &Ia::role_mother;
	role_funct[FEEDER] = &Ia::role_feeder;
	role_funct[PICKER] = &Ia::role_picker;

	/*ALONE*/
	alone_funct[ALONE_INIT] = &Ia::alone_init;
	alone_funct[ALONE_VOIR] = &Ia::alone_voir;
	alone_funct[ALONE_PICKUP] = &Ia::alone_pickup;
	alone_funct[ALONE_GOTO] = &Ia::alone_goto;
}

Ia::Ia( Ia const & src )
{
	*this = src;
}

Ia::~Ia( void )
{
}

void	Ia::think(Client &client)
{
	(*this.*role_funct[role])(client);
}

void	Ia::role_alone(Client &client)
{
	int	i;
	int	ret;
	(void)client;

	i = -1;
	ret = 0;
	while (++i < MAX_CMD)
		ret = (*this.*alone_funct[ret])(0, 0);
}

void	Ia::role_mother(Client &client)
{
	(void)client;
}

void	Ia::role_feeder(Client &client)
{
	(void)client;
}

void	Ia::role_picker(Client &client)
{
	(void)client;
}

Ia & Ia::operator=( Ia const & rhs )
{
	(void)rhs;
	return *this;
}

std::ostream & 		operator<<(std::ostream &o, Ia const &rhs)
{
	(void)rhs;
	o << "";
	return o;
}
