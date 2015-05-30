#include "Messages.hpp"

Messages::Messages( void )
{
}

Messages::Messages(std::string team, int id, Inventory *inventory) : _my_inventory(inventory), _team_name(team), _id(id){
}

Messages::Messages( Messages const & src )
{
	*this = src;
}

Messages::~Messages( void )
{
}

void			Messages::setTeam(std::string team_name){_team_name = team_name;}
std::string		Messages::getTeam(void) const{return(_team_name);}

void			Messages::receive(std::string cmd){
	Message		*tmp = new Message();
	std::stringstream 	ss;
	std::string			buf;
	std::string			data;
	ss.str(cmd);
	ss >> buf;
	std::getline(ss, buf, ',');
	tmp->dir = stoi(buf);
	while (ss >> buf)
	{
		if (!buf.compare("0"))
			break ;
		data += buf + " ";
	}
	ss >> buf;
	tmp->team = buf;
	ss >> buf;
	tmp->id = stoi(buf);
	tmp->data = data;
	tmp->inventory.setData(ss);
	recv.push_front(tmp);
	std::cout << *this;
}

std::string			Messages::sending(std::string cmd){
	std::stringstream 	ret;
	ret << cmd << " " << END << " " << _team_name << " " << _id << *_my_inventory << std::endl;
	return (ret.str());
}

Messages & Messages::operator=( Messages const & rhs )
{
	(void)rhs;
	return *this;
}

std::ostream & 		operator<<(std::ostream &o, Messages const &rhs){
	for (std::list<Message *>::const_iterator it = rhs.recv.begin(); it != rhs.recv.end(); it++)
		o << *(*it);
	return o;
}

std::ostream & 		operator<<(std::ostream &o, Message const &rhs){
	o << rhs.team << " " << rhs.id << " " << rhs.dir << rhs.inventory << rhs.read << " ->" << rhs.data << std::endl;
	return (o);
}

/*
** MESSAGE PROTOCOL
** recv:
** <message> <<dir>,<CMD1> <CMD2> <CMD...> <END> <TEAM> <ID> <INVENTORY>>
**
** send:
** <brodcast> <MESSAGE>
*/
