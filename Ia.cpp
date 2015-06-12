#include "Ia.hpp"
#include "Client.hpp"

Ia::Ia( void )
{
	role = FEEDER;
	last_vision = -1;
	wanted_elem = -1;

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

	/*FEEDER*/
	feeder_funct[FEEDER_INIT] = &Ia::feeder_init;
	feeder_funct[FEEDER_VOIR] = &Ia::feeder_voir;
	feeder_funct[FEEDER_PICKUP] = &Ia::feeder_pickup;
	feeder_funct[FEEDER_GOTO] = &Ia::feeder_goto;

	/*Incant Tab*/
	incant_tab.push_back(new Inventory(0,1,0,0,0,0,0));
	incant_tab.push_back(new Inventory(0,1,1,1,0,0,0));
	incant_tab.push_back(new Inventory(0,2,0,1,0,2,0));
	incant_tab.push_back(new Inventory(0,1,1,2,0,1,0));
	incant_tab.push_back(new Inventory(0,1,2,1,3,0,0));
	incant_tab.push_back(new Inventory(0,1,2,3,0,1,0));
	incant_tab.push_back(new Inventory(0,2,2,2,2,2,1));
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

	i = -1;
	ret = 0;
	while (++i < MAX_CMD)
		ret = (*this.*alone_funct[ret])(client);
}

void	Ia::role_mother(Client &client)
{
	(void)client;
	// std::cout << "I AM YOUR MOTHER" << std::endl;
	sleep(1);
}

void	Ia::role_feeder(Client &client)
{
	static int		ret = 0;

	while (client.busy != true) {
		ret = (*this.*feeder_funct[ret])(client);
	}
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
