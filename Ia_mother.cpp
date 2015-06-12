#include "Ia.hpp"
#include "Client.hpp"

int			Ia::mother_init(Client &client)
{
	(void)client;
	std::cout << "INIT" << std::endl;
	return (0);
}
