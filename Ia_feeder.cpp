#include "Ia.hpp"
#include "Client.hpp"

enum	e_transition_tab_values
{
	VISION, /*GOT SUFFISANT VISION AND NOT TOO OLD*/
	ELEM_PRESENT, /*SEEKED ELEMENT PRESENT IN THIS BLOC*/
	GO_TO, /*GO TO THIS STATE IF OK*/
	BACK_TO, /*ELSE GO HERE*/
	TRANSITION_NBR
};

// const int		feeder_transition_tab[ALONE_STATES_NBR][TRANSITION_NBR] =
// {
// 	{GOT_VISION, USELESS, FEEDER_PICKUP, FEEDER_VOIR},/*INIT*/
// 	{USELESS, ELEM_HERE, FEEDER_PICKUP, FEEDER_GOTO},/*VOIR*/
// 	{GOT_VISION, USELESS, FEEDER_VOIR, FEEDER_GOTO},/*PICKUP*/
// 	{USELESS, ELEM_HERE, FEEDER_PICKUP, FEEDER_INIT}/*GOTO*/
// };

int			Ia::feeder_init(Client &client) {
	if (client.inventory.getData()["nourriture"] % 20 == 0) {
		client.busy = true;
		client.list_cmd.push_back(new Inventaire(&client));
	}
	// else if (client.inventory.getData()["nourriture"] > 20 && client.others.size() < 6) {
	// 	client.busy = true;
	// 	client.list_cmd.push_back(new Fork(&client));
	// }
	// if (client.inventory.isEmpty() != 0) {
	// 	role = PICKER;
	// 	return (FEEDER_INIT);
	// }
	if (client.map->get_nb("nourriture") > 0)
		return (FEEDER_PICKUP);
	else if (client.inventory.getData()["nourriture"] > 15 && level == 1) {
		return (FEEDER_STONE);
	}
	else
		return (FEEDER_VOIR);
}

int			Ia::feeder_voir(Client &client) {
	std::list<Icmd*>	li;

	client.busy = true;
	if (client.ia.last_vision == -1)
		client.list_cmd.push_back(new Voir(&client));
	else {
		if ((li = client.map->path_find("nourriture")).size() != 0) {
			client.list_cmd.splice(client.list_cmd.end(), li);
			return (FEEDER_PICKUP);
		}
		else {
			if (rand() % 2 == 0)
				client.list_cmd.push_back(new Gauche(&client));
			else
				client.list_cmd.push_back(new Droite(&client));	
			client.list_cmd.push_back(new Avance(&client));
			client.list_cmd.push_back(new Avance(&client));
			return (FEEDER_INIT);
		}
	}
	return (FEEDER_INIT);
}

int			Ia::feeder_pickup(Client &client) {
	client.busy = true;
	client.list_cmd.push_back(new Prend(&client, "nourriture"));
	return (FEEDER_INIT);
}

int			Ia::feeder_goto(Client &client) {
	(void)client;
	return (1);
}

int			Ia::feeder_stone(Client &client) {
	std::list<Icmd*>	li;

	client.busy = true;
	if (client.ia.last_vision == -1)
		client.list_cmd.push_back(new Voir(&client));
	else {
		if ((li = client.map->path_find("linemate")).size() != 0) {
			client.list_cmd.splice(client.list_cmd.end(), li);
			client.list_cmd.push_back(new Prend(&client, "linemate"));
			return (FEEDER_INCANT);
		}
		else {
			if (rand() % 2 == 0)
				client.list_cmd.push_back(new Gauche(&client));
			else
				client.list_cmd.push_back(new Droite(&client));	
			client.list_cmd.push_back(new Avance(&client));
			client.list_cmd.push_back(new Avance(&client));
			return (FEEDER_INIT);
		}
	}
	return (FEEDER_INIT);
}

int			Ia::feeder_incant(Client &client) {
	client.busy = true;
	level++;
	client.list_cmd.push_back(new Incantation());
	return (FEEDER_INIT);
}