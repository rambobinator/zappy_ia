#include "Client.hpp"
#include "Icmd.hpp"
#define USAGE "<team> <port> <adress>"

int		main(int ac, char **av)
{
	if (ac != 4)
	{
		std::cout << USAGE << std::endl;
		return (-1);
	}
	Client	c(av);
	c.loop_client();

	return (0);
}
