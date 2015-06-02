#ifndef IA_HPP
# define IA_HPP

#include <iostream>

/*UTILS*/
#define MAX_CMD 10
#define USELESS -1

/*FOOD VALUES*/
#define FOOD_MIN 5
#define FOOD_GIVING 15

/*VISION*/
#define GOT_VISION 3

/*ELEM*/
#define ELEM_HERE 1

enum	e_role
{
	ALONE, /*FIRST STATE WHEN WE HAVENT MET*/
	MOTHER, /*FIRST MEMBER OF MY GROUP (6) THE BRAIN !*/
	FEEDER, /*COLLECT FOOD AND DISTRIBUTE*/
	PICKER, /*COLLECT STONES AND GIVE THEM TO MOTHER*/
	ROLE_NBR
};

enum	e_transition_tab_values
{
	VISION, /*GOT SUFFISANT VISION AND NOT TOO OLD*/
	ELEM_PRESENT, /*SEEKED ELEMENT PRESENT IN THIS BLOC*/
	GO_TO, /*GO TO THIS STATE IF OK*/
	BACK_TO, /*ELSE GO HERE*/
	TRANSITION_NBR
};

enum	e_alone_states
{
	ALONE_INIT,
	ALONE_VOIR,
	ALONE_PICKUP,
	ALONE_GOTO,
	ALONE_STATES_NBR
};

class Client;

class Ia
{
	const int		alone_transition_tab[ALONE_STATES_NBR][TRANSITION_NBR] = /*PLAYER IS IN ALONE MODE HERE*/
	{
		{GOT_VISION, USELESS, ALONE_PICKUP, ALONE_VOIR},/*INIT*/
		{USELESS, ELEM_HERE, ALONE_PICKUP, ALONE_GOTO},/*VOIR*/
		{GOT_VISION, USELESS, ALONE_VOIR, ALONE_GOTO},/*PICKUP*/
		{USELESS, ELEM_HERE, ALONE_PICKUP, ALONE_INIT}/*GOTO*/
	};

	typedef void (Ia::*Role)(Client &);
	typedef int (Ia::*Alone)(int, int);

	public:
		Ia();
		Ia( Ia const & src );
		~Ia();
		Ia &		operator=( Ia const & rhs );

		/*ROLE MANAGEMENT*/
		int			role;
		Role		role_funct[ROLE_NBR];

		/**/
		void		role_alone(Client &client);
		Alone		alone_funct[ALONE_STATES_NBR];
		int			alone_init(int, int);
		// int			alone_voir(int*, int*);
		// int			alone_pickup(int*, int*);
		// int			alone_goto(int*, int*);

		/**/
		void		role_mother(Client &client);
		void		role_feeder(Client &client);
		void		role_picker(Client &client);

	private:

};

std::ostream & 		operator<<(std::ostream &o, Ia const &rhs);

#endif