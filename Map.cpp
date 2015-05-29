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

Map::~Map() {}

// void	Map::fill_map(std::string str) {
// 	int			nb_case;
// 	int			first;
// 	int			last;
// 	std::string	tmp;

// 	nb_case = 0;
// 	tmp = str.substr(1, str.size() - 1);
// 	// while (tmp.find(""))
// }

Point	Map::get_coord(int tile) {
	int		level = 0;
	int		max_level = 8;
	int		i;
	int		j;
	int		nb;
	Point	ret;

	i = 0;
	nb = 0;
	ret.x = -1;
	ret.y = -1;
	while (i <= max_level) {
		j = -level;
		while (j <= level) {
			if (tile == nb) {
				ret.x = j;
				ret.y = i;
				return (ret);
			}
			nb++;
			j++;
		}
		i++;
		level++;
	}
	return (ret);
}

