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

#include <vector>
#include "Inventory.hpp"

class Point {
public:
	int x;
	int y;
};

class Map {
public:
	Map(int x, int y);
	~Map(void);
	// void 	fill_map(std::string str);
	// void 	fill_case(std::string str, int tile);
	Point	get_coord(int tile);
	std::vector<std::vector<Inventory*>>		map;
	int											x;
	int											y;
	int											direction;
};