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
#include "Point.hpp"

class Map {
public:
	Map(int x, int y);
	~Map(void);
	void 						fill_map(std::string str);
	std::vector<std::string>	parse_str(std::string str);
	Point						get_coord(int tile);
	void						fill_case(Point p, std::string str);
	void						print(void);
	Point						normalizer(Point p);

	std::vector<std::vector<Inventory*>>		map;
	int											map_x;
	int											map_y;
	int											x;
	int											y;
	int											direction;
};
