/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brehaili <brehaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/29 14:55:37 by brehaili          #+#    #+#             */
/*   Updated: 2015/05/29 14:55:38 by brehaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <list>
#include "Icmd.hpp"
#include "Inventory.hpp"
#include "Point.hpp"
#include "Client.hpp"

class Client;
class Icmd;

class Map {
public:
	Map(int x, int y, Client *client);
	~Map(void);
	void 						fill_map(std::string str);
	std::vector<std::string>	parse_str(std::string str);
	Point						get_coord(int tile);
	void						fill_case(Point p, std::string str);
	void						print(void);
	int							get_nb(std::string str);
	void						remove(std::string str);
	void						reset(std::string str);
	void						add_direction(int i);
	void						add_avance(void);

	Point						normalizer(Point p);
	std::list<Icmd*>			path_find(std::string str);
	std::list<Icmd*>			best_path(Point p);
	std::list<Icmd*>			gen_avance(int n);

	Client										*client;
	std::vector<std::vector<Inventory*>>		map;
	int											map_x;
	int											map_y;
	int											x;
	int											y;
	int											direction;
};

std::ostream & 		operator<<(std::ostream &o, Map const &rhs);

#endif
