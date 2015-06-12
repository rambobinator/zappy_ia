#include "Ia.hpp"
#include "Client.hpp"
#define FEEDER_PERCENT 50 /*mean there will be 50 % of feeder*/

int			Ia::mother_init(Client &client)
{
	(void)client;
	// std::cout << "MOTHER INIT" << std::endl;
	return (MOTHER_DISPATCH);
}

int			Ia::mother_dispatch_role(Client &client)
{
	int		feeder_nbr;

	// std::cout << "MOTHER DISPATCH" << client.others.size() << std::endl;
	feeder_nbr = ((client.others.size() - 1) * FEEDER_PERCENT) / 100;
	for (std::list<Coop *>::iterator it = client.others.begin(); it != client.others.end(); it++){
		if ((*it)->id == client.id)
			continue ;
		if (feeder_nbr--)
		{
			client.list_cmd.push_back(new Broadcast(client, args2string(3, PID, (*it)->id, SET_AS_FEEDER)));
			// std::cout << "FEEDER" << std::endl;
		}
		else
		{
			client.list_cmd.push_back(new Broadcast(client, args2string(3, PID, (*it)->id, SET_AS_PICKER)));
			// std::cout << "PICKER" << std::endl;
		}
	}
	return (MOTHER_INIT);
}
