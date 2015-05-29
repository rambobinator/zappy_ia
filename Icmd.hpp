#ifndef ICMD_HPP
#define ICMD_HPP

#define AVANCE_DELAY 7
#define AVANCE_NAME "avance"

#define DROITE_DELAY 7
#define DROITE_NAME "droite"

#define GAUCHE_DELAY 7
#define GAUCHE_NAME "gauche"

#define VOIR_DELAY 7
#define VOIR_NAME "voir"

#define INVENTAIRE_DELAY 7
#define INVENTAIRE_NAME "inventaire"

#define PREND_DELAY 7
#define PREND_NAME "prend"

#define POSE_DELAY 7
#define POSE_NAME "pose"

#define EXPULSE_DELAY 7
#define EXPULSE_NAME "expulse"

#define BROADCAST_DELAY 7
#define BROADCAST_NAME "broadcast"

#define INCANTATION_DELAY 300
#define INCANTATION_NAME "incantation"

#define FORK_DELAY 42
#define FORK_NAME "fork"

#define CONNECT_NBR_DELAY 0
#define CONNECT_NBR_NAME "connect_nbr"

#include <iostream>
#include "client.hpp"

class Icmd
{
	public:
		virtual ~Icmd(){};
		virtual std::string	getCmd() = 0;
		virtual void		execute() = 0;
		virtual void		parseAnswer(std::string) = 0;
		bool		_done;

	protected:
		int			_delay;
		std::string	_cmd_name;
		std::string	_cmd_final;
		Client		*_client;
};

class Avance : public Icmd
{
	public:
		Avance(Client &new_client);
		~Avance();
		std::string	getCmd();
		void		execute();
		void		parseAnswer(std::string);
};

class Droite : public Icmd
{
	public:
		Droite();
		~Droite();
		std::string	getCmd();
		void		execute();
		void		parseAnswer(std::string);
};

class Gauche : public Icmd
{
	public:
		Gauche();
		~Gauche();
		std::string	getCmd();
		void		execute();
		void		parseAnswer(std::string);
};

class Voir : public Icmd
{
	public:
		Voir();
		~Voir();
		std::string	getCmd();
		void		execute();
		void		parseAnswer(std::string);
};

class Inventaire : public Icmd
{
	public:
		Inventaire();
		~Inventaire();
		std::string	getCmd();
		void		execute();
		void		parseAnswer(std::string);
};

class Prend : public Icmd
{
	public:
		Prend();
		~Prend();
		std::string	getCmd();
		void		execute();
		void		parseAnswer(std::string);
};

class Pose : public Icmd
{
	public:
		Pose();
		~Pose();
		std::string	getCmd();
		void		execute();
		void		parseAnswer(std::string);
};

class Expulse : public Icmd
{
	public:
		Expulse();
		~Expulse();
		std::string	getCmd();
		void		execute();
		void		parseAnswer(std::string);
};

class Broadcast : public Icmd
{
	public:
		Broadcast();
		~Broadcast();
		std::string	getCmd();
		void		execute();
		void		parseAnswer(std::string);
};

class Incantation : public Icmd
{
	public:
		Incantation();
		~Incantation();
		std::string	getCmd();
		void		execute();
		void		parseAnswer(std::string);
};

class Fork : public Icmd
{
	public:
		Fork();
		~Fork();
		std::string	getCmd();
		void		execute();
		void		parseAnswer(std::string);
};

class Connect_nbr : public Icmd
{
	public:
		Connect_nbr();
		~Connect_nbr();
		std::string	getCmd();
		void		execute();
		void		parseAnswer(std::string);
};

class Welcome : public Icmd
{
	public:
		Welcome(Client &new_client);
		~Welcome();
		std::string	getCmd();
		void		execute();
		void		parseAnswer(std::string);
		int			nb_answer;
};

#endif
