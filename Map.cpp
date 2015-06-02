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

Map::Map(int x, int y) : map(std::vector<std::vector<Inventory*>>(x,
	std::vector<Inventory*>(y, NULL))) {
	int						i;
	int						j;

	this->x = 0;
	this->y = 0;
	this->direction = 0;
	this->map_x = x;
	this->map_y = y;
	i = 0;
	while (i < this->map_x) {
		j = 0;
		while (j < this->map_y) {
			this->map[i][j] = new Inventory();
			j++;
		}
		i++;
	}
}

Map::~Map() {}

void						Map::fill_case(Point p, std::string str) {
	Point	a;

	if (this->direction == 0)
		a = this->normalizer({this->x + p.x, this->y + p.y});
	else if (this->direction == 1)
		a = this->normalizer({this->x + p.y, this->y - p.x});
	else if (this->direction == 2)
		a = this->normalizer({this->x - p.x, this->y - p.y});
	else if (this->direction == 3)
		a = this->normalizer({this->x - p.y, this->y + p.x});
	this->map[a.x][a.y]->setData(str);
}

Point		Map::normalizer(Point p) {
	if (p.x >= this->map_x)
		p.x = p.x % this->map_x;
	else if (p.x < 0)
		p.x = this->map_x + p.x;
	if (p.y >= this->map_y)
		p.y = p.y % this->map_y;
	else if (p.y < 0)
		p.y = this->map_y + p.y;
	return (p);

}

std::vector<std::string>	Map::parse_str(std::string str) {
	int							nb_case;
	int							last;
	std::string					tmp;
	std::vector<std::string>	vec;	


	nb_case = 0;
	tmp = str.substr(1, str.size() - 2);
	while ((last = tmp.find(",")) != (int)tmp.npos) {
		vec.push_back(tmp.substr(0, last));
		tmp.erase(0, last + 1);
		nb_case++;
	}

	vec.push_back(tmp);
	last = 0;
	return (vec);
}

void						Map::fill_map(std::string str) {
	std::vector<std::string>	vec;
	int							level;
	int							max;
	int							nb;
	int							i;
	int							j;
	Point						ret;

	vec = this->parse_str(str);
	max = vec.size();
	i = 0;
	level = 0;
	nb = 0;
	while (nb < max) {
		j = -level;
		while (j <= level) {
			ret.x = j;
			ret.y = i;
			this->fill_case(ret, vec[nb]);
			nb++;
			j++;
		}
		i++;
		level++;
	}
}

void						Map::print() {
	int		i;
	int		j;

	j = 0;
	while (j < this->map_y) {
		i = 0;
		while (i < this->map_x) {
			this->map[i][j]->print();
			i++;
		}
		j++;
	}
}

int		main() {
	Map a(3, 3);
	a.map[2][2]->resetData();
	a.fill_map("{nourriture, joueur sibur, phiras phiras, }");
	a.print();
}
