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

void						Inventory::init_player_stuff(void){
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

void						Inventory::setData(std::string str) {
	int				last;
	std::string		tmp;

	this->resetData();
	while ((last = str.find(" ")) != (int)str.npos) {
		tmp = str.substr(0, last);
		if (this->_data.find(tmp) != this->_data.end())
			this->_data[tmp]++;
		str.erase(0, last + 1);
	}
	tmp = str;
	if (this->_data.find(tmp) != this->_data.end()) {
		this->_data[tmp]++;
	}
}

void						Inventory::resetData(void) {
	_data["nourriture"] = 0;
	_data["linemate"] = 0;
	_data["deraumere"] = 0;
	_data["sibur"] = 0;
	_data["mendiane"] = 0;
	_data["phiras"] = 0;
	_data["thystame"] = 0;
}

void						Inventory::print(void) {
	std::map<std::string, int>::iterator	it;

	it = this->_data.begin();
	while (it != this->_data.end()) {
		std::cout << it->first << " => ";
		std::cout << it->second << std::endl;
		it++;
	}
}

char						Inventory::minify(void){
	unsigned char			c = 0;
	unsigned char			mask = 1;
	int						i = 1;

	for(auto &it : _data){
		i++;
		if (it.second > 0)
			c |= (mask << i);
	}
	return (c);
}
