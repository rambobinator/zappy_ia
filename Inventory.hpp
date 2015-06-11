#ifndef INVENTORY_HPP
# define INVENTORY_HPP

#include <iostream>
#include <sstream>
#include <map>

class Inventory
{
	public:
		Inventory();
		Inventory(int a, int b, int c, int d, int e, int f, int g);
		Inventory( Inventory const & src );
		~Inventory();
		Inventory &		operator=( Inventory const & rhs );
		void			init_player_stuff(void);
		std::map<std::string, int>	getData(void)const;
		void						setData(std::stringstream &ss);
		void						setData(std::string str);
		void						setData(std::string str, int n);
		void						setData2(std::string str);
		void						minusData(std::string str);
		void						addData(std::string str);
		Inventory					subInventory(Inventory & inv);
		void						resetData(void);
		void						print(void);
		char						minify(void);

	private:
		std::map<std::string, int>	_data;
};

std::ostream & 		operator<<(std::ostream &o, Inventory const &rhs);

#endif