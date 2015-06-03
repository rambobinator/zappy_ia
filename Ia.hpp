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
		void		think(Client &client);

		/*ALONE*/
		void		role_alone(Client &client);
		Alone		alone_funct[ALONE_STATES_NBR];
		int			alone_init(int, int);
		int			alone_voir(int, int);
		int			alone_pickup(int, int);
		int			alone_goto(int, int);

		/*MOTHER*/
		void		role_mother(Client &client);

		/*FEEDER*/
		void		role_feeder(Client &client);

		/*PICKER*/
		void		role_picker(Client &client);

	private:

};

std::ostream & 		operator<<(std::ostream &o, Ia const &rhs);

#endif