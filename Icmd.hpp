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
#include "Client.hpp"
#include "Messages.hpp"

std::string			args2string(int data, ...);
class Client;

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
		Avance(Client *new_client);
		virtual ~Avance();
		std::string	getCmd();
		void		execute();
		void		parseAnswer(std::string);
};

class Droite : public Icmd
{
	public:
		Droite(Client *new_client);
		virtual ~Droite();
		std::string	getCmd();
		void		execute();
		void		parseAnswer(std::string);
};

class Gauche : public Icmd
{
	public:
		Gauche(Client *new_client);
		virtual ~Gauche();
		std::string	getCmd();
		void		execute();
		void		parseAnswer(std::string);
};

class Voir : public Icmd
{
	public:
		Voir(Client *new_client);
		virtual ~Voir();
		std::string	getCmd();
		void		execute();
		void		parseAnswer(std::string);
};

class Inventaire : public Icmd
{
	public:
		Inventaire();
		virtual ~Inventaire();
		std::string	getCmd();
		void		execute();
		void		parseAnswer(std::string);
};

class Prend : public Icmd
{
	public:
		Prend();
		Prend(Client *new_client, std::string args);
		virtual ~Prend();
		std::string	getCmd();
		void		execute();
		void		parseAnswer(std::string);

	private:
		std::string	_args;
};

class Pose : public Icmd
{
	public:
		Pose(Client *new_client, std::string args);
		virtual ~Pose();
		std::string	getCmd();
		void		execute();
		void		parseAnswer(std::string);

	private:
		std::string	_args;
};

class Expulse : public Icmd
{
	public:
		Expulse();
		virtual ~Expulse();
		std::string	getCmd();
		void		execute();
		void		parseAnswer(std::string);
};

class Broadcast : public Icmd
{
	public:
		Broadcast(Client &new_client);
		Broadcast(Client &new_client, std::string args);
		virtual ~Broadcast();
		std::string	getCmd();
		void		execute();
		void		parseAnswer(std::string);

	private:
		std::string	_args;
};

class Incantation : public Icmd
{
	public:
		Incantation();
		virtual ~Incantation();
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
		virtual ~Connect_nbr();
		std::string	getCmd();
		void		execute();
		void		parseAnswer(std::string);
};

class Welcome : public Icmd
{
	public:
		Welcome(Client &new_client);
		virtual ~Welcome();
		std::string	getCmd();
		void		execute();
		void		parseAnswer(std::string);
		int			nb_answer;
};

#endif
