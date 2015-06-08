#include "Icmd.hpp"

/*______________________________AVANCE*/
Avance::Avance(Client *new_client){
	_done = false;
	_delay = AVANCE_DELAY;
	_cmd_name = AVANCE_NAME;
	_client = new_client;
};

Avance::~Avance(){};

std::string	Avance::getCmd(){
	_cmd_final = _cmd_name + "\n";
	return (_cmd_final);
}

void	Avance::execute(){
	_done = true;
	_client->buf_write.add(getCmd());
	_client->map->add_avance();
};

void	Avance::parseAnswer(std::string answer){
	std::cout << _cmd_name << ": " << answer << std::endl;
	this->_client->list_cmd.remove(this);
	delete(this);
}
/*____________________________________*/

/*______________________________DROITE*/
Droite::Droite(Client *new_client) {
	_done = false;
	_delay = DROITE_DELAY;
	_cmd_name = DROITE_NAME;
	_client = new_client;
};

Droite::~Droite(){};

std::string	Droite::getCmd(){
	_cmd_final = _cmd_name + "\n";
	return (_cmd_final);
}

void	Droite::execute(){
	_done = true;
	_client->map->add_direction(1);
	_client->buf_write.add(getCmd());
};

void	Droite::parseAnswer(std::string answer){
	std::cout << _cmd_name << ": " << answer << std::endl;
	this->_client->list_cmd.remove(this);
	delete(this);
}

/*____________________________________*/

/*______________________________GAUCHE*/
Gauche::Gauche(Client *new_client) {
	_done = false;
	_delay = GAUCHE_DELAY;
	_cmd_name = GAUCHE_NAME;
	_client = new_client;
};

Gauche::~Gauche(){};

std::string	Gauche::getCmd(){
	_cmd_final = _cmd_name + "\n";
	return (_cmd_final);
}

void	Gauche::execute(){
	_done = true;
	_client->map->add_direction(-1);
	_client->buf_write.add(getCmd());
};

void	Gauche::parseAnswer(std::string answer){
	std::cout << _cmd_name << ": " << answer << std::endl;
	this->_client->list_cmd.remove(this);
	delete(this);
}
/*____________________________________*/
/*______________________________VOIR*/
Voir::Voir(Client *new_client){
	_done = false;
	_delay = VOIR_DELAY;
	_cmd_name = VOIR_NAME;
	_client = new_client;
};

Voir::~Voir(){};

std::string	Voir::getCmd(){
	_cmd_final = _cmd_name + "\n";
	return (_cmd_final);
}

void	Voir::execute(){
	_done = true;
	_client->buf_write.add(this->getCmd());
};

void	Voir::parseAnswer(std::string answer){
	std::cout << _cmd_name << ": " << answer << std::endl;
	_client->ia.last_vision = 0;
	_client->map->fill_map(answer);
	this->_client->list_cmd.remove(this);
	delete(this);
}
/*____________________________________*/
/*____________________________INVENTAIRE*/
Inventaire::Inventaire(){
	_done = false;
	_delay = INVENTAIRE_DELAY;
	_cmd_name = INVENTAIRE_NAME;
};

Inventaire::~Inventaire(){};

std::string	Inventaire::getCmd(){
	_cmd_final = _cmd_name + "\n";
	return (_cmd_final);
}

void	Inventaire::execute(){
	_done = true;
	_client->buf_write.add(getCmd());
};

void	Inventaire::parseAnswer(std::string answer){
	std::cout << _cmd_name << ": " << answer << std::endl;
	this->_client->list_cmd.remove(this);
	delete(this);
}
/*____________________________________*/
/*______________________________PREND*/
Prend::Prend(){
}

Prend::Prend(Client *new_client, std::string args){
	_done = false;
	_delay = PREND_DELAY;
	_cmd_name = PREND_NAME;
	_client = new_client;
	_args = args;
};

Prend::~Prend(){};

std::string	Prend::getCmd(){
	_cmd_final = _cmd_name + " " + _args + "\n";
	return (_cmd_final);
}

void	Prend::execute(){
	_done = true;
	_client->buf_write.add(getCmd());
};

void	Prend::parseAnswer(std::string answer){
	std::cout << _cmd_name << ": " << answer << std::endl;
	this->_client->list_cmd.remove(this);
	delete(this);
}
/*____________________________________*/
/*______________________________POSE*/
Pose::Pose(Client *new_client, std::string args){
	_done = false;
	_delay = POSE_DELAY;
	_cmd_name = POSE_NAME;
	_client = new_client;
	_args = args;
};

Pose::~Pose(){};

std::string	Pose::getCmd(){
	_cmd_final = _cmd_name + " " + _args + "\n";
	return (_cmd_final);
}

void	Pose::execute(){
	_done = true;
	_client->buf_write.add(getCmd());
};

void	Pose::parseAnswer(std::string answer){
	std::cout << _cmd_name << ": " << answer << std::endl;
	this->_client->list_cmd.remove(this);
	delete(this);
}
/*____________________________________*/
/*______________________________EXPULSE*/
Expulse::Expulse(){
	_done = false;
	_delay = EXPULSE_DELAY;
	_cmd_name = EXPULSE_NAME;
};

Expulse::~Expulse(){};

std::string	Expulse::getCmd(){
	_cmd_final = _cmd_name + "\n";
	return (_cmd_final);
}

void	Expulse::execute(){
	_done = true;
	std::cout << getCmd();/*ADD IN BUF INSTEAD*/
};

void	Expulse::parseAnswer(std::string answer){
	std::cout << _cmd_name << ": " << answer << std::endl;
	this->_client->list_cmd.remove(this);
	delete(this);
}
/*____________________________________*/
/*______________________________BROADCAST*/
Broadcast::Broadcast(Client &new_client){
	_done = false;
	_delay = BROADCAST_DELAY;
	_cmd_name = BROADCAST_NAME;
	_client = &new_client;
};

Broadcast::Broadcast(Client &new_client, std::string args){
	_done = false;
	_delay = BROADCAST_DELAY;
	_cmd_name = BROADCAST_NAME;
	_client = &new_client;
	_args = args;
};

Broadcast::~Broadcast(){};

std::string	Broadcast::getCmd(){
	_cmd_final = _cmd_name + _args;
	return (_cmd_final);
}

void	Broadcast::execute(){
	_done = true;
	_client->buf_write.add(_client->msgs->sending(getCmd()));
};

void	Broadcast::parseAnswer(std::string answer){
	std::cout << _cmd_name << ": " << answer << std::endl;
	this->_client->list_cmd.remove(this);
	delete(this);
}
/*____________________________________*/
/*_____________________________INCANTATION*/
Incantation::Incantation(){
	_done = false;
	_delay = INCANTATION_DELAY;
	_cmd_name = INCANTATION_NAME;
};

Incantation::~Incantation(){};

std::string	Incantation::getCmd(){
	_cmd_final = _cmd_name + "\n";
	return (_cmd_final);
}

void	Incantation::execute(){
	_done = true;
	std::cout << getCmd();/*ADD IN BUF INSTEAD*/
};

void	Incantation::parseAnswer(std::string answer){
	std::cout << _cmd_name << ": " << answer << std::endl;
	delete(this);
}
/*____________________________________*/
/*_____________________________FORK*/
Fork::Fork(){
	_done = false;
	_delay = FORK_DELAY;
	_cmd_name = FORK_NAME;
};

Fork::~Fork(){};

std::string	Fork::getCmd(){
	_cmd_final = _cmd_name + "\n";
	return (_cmd_final);
}

void	Fork::execute(){
	_done = true;
	std::cout << getCmd();/*ADD IN BUF INSTEAD*/
};

void	Fork::parseAnswer(std::string answer){
	std::cout << _cmd_name << ": " << answer << std::endl;
	delete(this);
}
/*____________________________________*/
/*___________________________CONNECT_NBR*/
Connect_nbr::Connect_nbr(){
	_done = false;
	_delay = CONNECT_NBR_DELAY;
	_cmd_name = CONNECT_NBR_NAME;
};

Connect_nbr::~Connect_nbr(){};

std::string	Connect_nbr::getCmd(){
	_cmd_final = _cmd_name + "\n";
	return (_cmd_final);
}

void	Connect_nbr::execute(){
	_done = true;
	_client->buf_write.add(getCmd());
};

void	Connect_nbr::parseAnswer(std::string answer){
	std::cout << _cmd_name << ": " << answer << std::endl;
	this->_client->list_cmd.remove(this);
	delete(this);
}
/*____________________________________*/
/*___________________________WELCOME*/
Welcome::Welcome(Client &new_client) {
	_done = false;
	_delay = 0;
	_cmd_name = new_client.team_name;
	_client = &new_client;
	nb_answer = 0;
};

Welcome::~Welcome(){};

std::string	Welcome::getCmd(){
	_cmd_final = _cmd_name + "\n";
	return (_cmd_final);
}

void	Welcome::execute(){
	_done = true;
	this->_client->buf_write.add(this->getCmd());
};

void	Welcome::parseAnswer(std::string answer){
	int		space;

	if (nb_answer == 0) {
		if ((this->_client->remaining_slots = stoi(answer)) > 0)
			this->_client->new_client();
		nb_answer++;
	}
	else if (nb_answer == 1) {
		space = answer.find(" ");
		this->_client->map_x = stoi(answer.substr(0, space));
		this->_client->map_y =  stoi(answer.substr(space + 1, answer.size() - space));
		_client->map = new Map(_client->map_x, _client->map_y, _client); /*RM*/
		_client->busy = false;
		this->_client->list_cmd.remove(this);
		if (_client->remaining_slots <= 0)
			_client->list_cmd.push_back(new Broadcast(*_client, args2string(1, ROLL_CALL)));
		delete(this);
	}
}
/*____________________________________*/
