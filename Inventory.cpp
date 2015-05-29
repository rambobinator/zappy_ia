#include "Inventory.hpp"

Inventory::Inventory(void){
	_data["linemate"] = 0;
	_data["deraumere"] = 0;
	_data["sibur"] = 0;
	_data["mendiane"] = 0;
	_data["phiras"] = 0;
	_data["thystame"] = 0;
	_data["nourriture"] = 0;
}

Inventory::Inventory( Inventory const & src ){
	*this = src;
}

Inventory::~Inventory( void ){
}

Inventory & Inventory::operator=( Inventory const & rhs ){
	(void)rhs;
	return *this;
}

std::ostream & 		operator<<(std::ostream &o, Inventory const &rhs){
	(void)rhs;
	o << "";
	return o;
}

void			Inventory::init_player_stuff(void){
	_data["nourriture"] += 10;
}
