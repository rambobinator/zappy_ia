#include "Inventory.hpp"

Inventory::Inventory(void){
	_data["nourriture"] = 0;
	_data["linemate"] = 0;
	_data["deraumere"] = 0;
	_data["sibur"] = 0;
	_data["mendiane"] = 0;
	_data["phiras"] = 0;
	_data["thystame"] = 0;
}

Inventory::Inventory( Inventory const & src ){
	*this = src;
}

Inventory::~Inventory( void ){
}

Inventory & Inventory::operator=( Inventory const & rhs ){
	_data = rhs.getData();
	return *this;
}

std::ostream & 		operator<<(std::ostream &o, Inventory const &rhs){
	o << " ";
	for(auto &it : rhs.getData())
		o <<  it.second << " ";
	return o;
}

void			Inventory::init_player_stuff(void){
	_data["nourriture"] = 10;
}

std::map<std::string, int>	Inventory::getData(void)const{return(_data);}

void						Inventory::setData(std::stringstream &ss){
	std::string				buf;

	for(auto &it : _data)
	{
		ss >> buf;
		it.second = stoi(buf);
	}
}
