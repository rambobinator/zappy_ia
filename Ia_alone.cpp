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

int			Ia::alone_init(int vision, int elem_pres)
{
	(void)vision;
	(void)elem_pres;
	std::cout << "INIT" << std::endl;
	return ((vision) ? alone_transition_tab[ALONE_INIT][GO_TO] : alone_transition_tab[ALONE_INIT][BACK_TO]);
}

int			Ia::alone_voir(int vision, int elem_pres)
{
	(void)vision;
	(void)elem_pres;
	std::cout << "VOIR" << std::endl;
	return ((vision) ? alone_transition_tab[ALONE_VOIR][GO_TO] : alone_transition_tab[ALONE_VOIR][BACK_TO]);
}

int			Ia::alone_pickup(int vision, int elem_pres)
{
	(void)vision;
	(void)elem_pres;
	std::cout << "PICKUP" << std::endl;
	return ((vision) ? alone_transition_tab[ALONE_PICKUP][GO_TO] : alone_transition_tab[ALONE_PICKUP][BACK_TO]);
}

int			Ia::alone_goto(int vision, int elem_pres)
{
	(void)vision;
	(void)elem_pres;
	std::cout << "GOTO" << std::endl;
	return ((vision) ? alone_transition_tab[ALONE_PICKUP][GO_TO] : alone_transition_tab[ALONE_PICKUP][BACK_TO]);
}
