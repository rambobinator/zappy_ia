/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brehaili <brehaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/29 14:55:32 by brehaili          #+#    #+#             */
/*   Updated: 2015/05/29 14:55:33 by brehaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Map.hpp"

Map::Map(int x, int y) : map(std::vector<std::vector<Inventory*>>(
	x, std::vector<Inventory*>(y, new Inventory()))) {
	this->x = 0;
	this->y = 0;
	this->direction = 0;
}

void	Map::fill_map(std::string str) {
	int			nb_case;
	int			first;
	int			last;
	std::string	tmp;

	nb_case = 0;
	tmp = str.substr(1, str.size() - 1);
	while (tmp.find(""))
}

Point	Map::get_coord(int tile) {
	int		map_x;
	int		map_y;

	map_x = this->map.size();
	map_y = this->map[0].size();
	if (direction == 0) {
		int		level = 0
		int		max_level = 4;
		int		i;
		int		j;

		i = 0
		while (i < max_level) {
			j = -level;
			while (j <= level) {
				
				j++;
			}
		}
	}
	else if (direction == 1) {

	}
	else if (direction == 2) {
		
	}
	else if (direction == 3) {
		
	}
}

int		Map::get_etage(int tile) {
	if (tile == 0)
		return (0);
	else if (tile <= 3)
		return (1);
	else if (tile <= 8)
		return (2);
	else if (tile <= 15)
		return (3);
	else if (title <= )
}