#include "Inventory.hpp"
#include <cstdlib>

Inventory::Inventory(void){
	_data["nourriture"] = 0;
	_data["linemate"] = 0;
	_data["deraumere"] = 0;
	_data["sibur"] = 0;
	_data["mendiane"] = 0;
	_data["phiras"] = 0;
	_data["thystame"] = 0;
}

Inventory::Inventory(int a, int b, int c, int d, int e, int f, int g) {
	_data["nourriture"] = a;
	_data["linemate"] = b;
	_data["deraumere"] = c;
	_data["sibur"] = d;
	_data["mendiane"] = e;
	_data["phiras"] = f;
	_data["thystame"] = g;
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

void						Inventory::setData2(std::string str) {
	int				last;
	int				last2;
	std::string		tmp;
	std::string		tmp2;

	str = str.substr(1, str.size() - 2);
	while ((last = str.find(",")) != (int)str.npos) {
		last2 = str.find(" ");
		tmp2 = str.substr(0, last2);
		tmp = str.substr(last2 + 1, last - last2 - 1);
		this->_data[tmp2] = atoi(tmp.c_str());
		str.erase(0, last + 2);
	}
	last2 = str.find(" ");
	tmp2 = str.substr(0, last2);
	tmp = str.substr(last2 + 1, str.size() - last2 - 1);
	this->_data[tmp2] = atoi(tmp.c_str());
}

int							Inventory::isEmpty(void) {
	if (_data["nourriture"] != 0)
		return (0);
	if (_data["linemate"] != 0)
		return (0);
	if (_data["deraumere"] != 0)
		return (0);
	if (_data["sibur"] != 0)
		return (0);
	if (_data["mendiane"] != 0)
		return (0);
	if (_data["phiras"] != 0)
		return (0);
	if (_data["thystame"] != 0)
		return (0);
	return (1);
}

void						Inventory::setData(std::string str, int n) {
	this->_data[str] = n;
}

void							Inventory::minusData(std::string str) {
	if (this->_data[str] > 0)
		this->_data[str]--;
}

void							Inventory::addData(std::string str) {
		this->_data[str]++;
}

Inventory						Inventory::subInventory(Inventory & inv) {
	Inventory								ret;
	std::map<std::string, int>::iterator	it;

	it = inv._data.begin();
	while (it != inv._data.end()) {
		if (_data[it->first] > it->second)
			ret._data[it->first] = 0;
		else
			ret._data[it->first] = it->second - _data[it->first];
		it++;
	}
	return (ret);
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
