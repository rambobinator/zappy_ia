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

const int		alone_transition_tab[ALONE_STATES_NBR][TRANSITION_NBR] = /*PLAYER IS IN ALONE MODE HERE*/
{
	{GOT_VISION, USELESS, ALONE_PICKUP, ALONE_VOIR},/*INIT*/
	{USELESS, ELEM_HERE, ALONE_PICKUP, ALONE_GOTO},/*VOIR*/
	{GOT_VISION, USELESS, ALONE_VOIR, ALONE_GOTO},/*PICKUP*/
	{USELESS, ELEM_HERE, ALONE_PICKUP, ALONE_INIT}/*GOTO*/
};

int			Ia::alone_init(Client &client)
{
	std::cout << "INIT" << std::endl;
	if (client.ia.last_vision == -1 || client.ia.wanted_elem == -1)
		return (ALONE_VOIR);
	return ((client.ia.last_vision <= alone_transition_tab[ALONE_INIT][VISION]) ?
		alone_transition_tab[ALONE_INIT][GO_TO] : alone_transition_tab[ALONE_INIT][BACK_TO]);
}

int			Ia::alone_voir(Client &client)
{
	std::cout << "VOIR" << std::endl;
	client.list_cmd.push_back(new Voir(&client));
	return ((client.ia.wanted_elem <= alone_transition_tab[ALONE_VOIR][ELEM_PRESENT]) ?
		alone_transition_tab[ALONE_VOIR][GO_TO] : alone_transition_tab[ALONE_VOIR][BACK_TO]);
}

int			Ia::alone_pickup(Client &client)
{
	std::cout << "PICKUP" << std::endl;
	client.list_cmd.push_back(new Prend(&client, "nourriture"));
	return (ALONE_GOTO);
	//return ((client.ia.last_vision <= alone_transition_tab[ALONE_PICKUP][VISION]) ?
	//	alone_transition_tab[ALONE_PICKUP][GO_TO] : alone_transition_tab[ALONE_PICKUP][BACK_TO]);
}

int			Ia::alone_goto(Client &client)
{
	std::cout << "GOTO" << std::endl;
	client.list_cmd.push_back(new Avance(&client));
	return ((client.ia.wanted_elem <= alone_transition_tab[ALONE_GOTO][ELEM_PRESENT]) ?
		alone_transition_tab[ALONE_PICKUP][GO_TO] : alone_transition_tab[ALONE_PICKUP][BACK_TO]);
}
