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

Map::Map(int x, int y, Client *client) : client(client), map(std::vector<std::vector<Inventory*>>(x,
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

	// std::cout << "p: " << p.x << "," << p.y << std::endl;
	if (this->direction == 0)
		a = this->normalizer({this->x + p.x, this->y + p.y});
	else if (this->direction == 1)
		a = this->normalizer({this->x - p.y, this->y + p.x});
	else if (this->direction == 2)
		a = this->normalizer({this->x - p.x, this->y - p.y});
	else if (this->direction == 3)
		a = this->normalizer({this->x + p.y, this->y - p.x});
	this->map[a.x][a.y]->setData(str);
	std::cout << "fill_map " << a.x << ";" << a.y << std::endl;
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
	// std::cout << "p_n: " << p.x << "," << p.y << "    "<< this->direction << std::endl;
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
		i--;
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

int							Map::get_nb(std::string str) {
	return (map[this->x][this->y]->getData()[str]);
}

void						Map::remove(std::string str) {
	map[x][y]->minusData(str);
}

void						Map::setCase(std::string str) {
	map[x][y]->setData2(str);
}

void						Map::reset(std::string str) {
	map[x][y]->setData(str, 0);
}

void						Map::add_direction(int i) {
	this->direction += i;
	if (this->direction < 0)
		this->direction += 4;
	else if (this->direction >= 4)
		this->direction = this->direction % 4;
}

void						Map::add_avance(void) {
	if (this->direction == 0)
		this->y -= 1;
	else if (this->direction == 1)
		this->x += 1;
	else if (this->direction == 2)
		this->y += 1;
	else if (this->direction == 3)
		this->x -= 1;
	if (this->x < 0)
		this->x = this->map_x + this->x;
	else if (this->x >= this->map_x)
		this->x = this->x - this->map_x;
	if (this->y < 0)
		this->y = this->map_y + this->y;
	else if (this->y >= this->map_y)
		this->y = this->y - this->map_y;

}

void						Map::free_list(std::list<Icmd*> li) {
	std::list<Icmd*>::iterator	it;

	it = li.begin();
	while (it != li.end()) {
		delete(*it);
		it++;
	}
}

std::list<Icmd*>			Map::path_find(std::string str) {
	int								i;
	int								j;
	std::vector<Point>				li;
	std::vector<std::list<Icmd*>>	vec;
	int								it;
	std::list<Icmd*>				nu;
	int								min;
	int								i_min;

	i = 0;
	while (i < this->map_x) {
		j = 0;
		while (j < this->map_y) {
			if (this->map[i][j]->getData()[str] > 0) {
				// std::cout << "phiras: " << i << "," << j << std::endl;
				li.push_back({i,j});
			}
			j++;
		}
		i++;
	}
	it = 0;
	while (it < (int)li.size()) {
		vec.push_back(this->best_path(li[it]));
		it++;
	}
	if (vec.empty())
		return (nu);
	i = 0;
	j = vec.size();
	min = 1000;
	i_min = -1;
	while (i < j) {
		if ((int)vec[i].size() < min) {
			min = vec[i].size();
			if (i_min != -1)
				free_list(vec[i_min]);
			i_min = i;
		}
		else
			free_list(vec[i]);
		i++;
	}
	std::cout << client->id << " to: {" << li[i_min].x << ";" << li[i_min].y << "}" << std::endl;
	return (vec[i_min]);
}

std::list<Icmd*>			Map::best_path(Point p) {
	std::list<Icmd*>	ret;
	int					delta_x;
	int					delta_y;
	int					mov_1;
	int					mov_2;
	int					rotate;
	std::vector<int>	min;
	int					dir = this->direction;

	delta_x = p.x - this->x;
	delta_y = p.y - this->y;
	
	if (abs(delta_x) > map_x / 2) {
		if (delta_x > 0)
			delta_x = delta_x - map_x;
		else
			delta_x = map_x + delta_x;
	}
	if (abs(delta_y) > map_y / 2) {
		if (delta_y > 0)
			delta_y = delta_y - map_y;
		else
			delta_y = map_y + delta_y;
	}

	if (delta_x <= 0)
		mov_1 = 3;
	else
		mov_1 = 1;
	if (delta_y <= 0)
		mov_2 = 0;
	else
		mov_2 = 2;

	if (abs(this->direction - mov_1) % 3 < abs(this->direction - mov_2) % 3) {
		min.push_back(mov_1);
		min.push_back(mov_2);
	}
	else {
		min.push_back(mov_2);
		min.push_back(mov_1);	
	}

	rotate = min[0] - this->direction;
	// std::cout << "Rotate " << rotate << std::endl;
	if (rotate == 3 || rotate == -1) {
		// std::cout << "Gauche" << std::endl;
		ret.push_back(new Gauche(client));
		this->add_direction(-1);
	}
	else if (rotate == 1 || rotate == -3) {
		// std::cout << "Droite" << std::endl;
		ret.push_back(new Droite(client));
		this->add_direction(1);
	}

	if (min[0] % 2 == 0) {
		// std::cout << "Avance "<< delta_y << std::endl;
		ret.splice(ret.end(), this->gen_avance(delta_y));
	}
	else {
		// std::cout << "Avance "<< delta_x << std::endl;
		ret.splice(ret.end(), this->gen_avance(delta_x));
	}


	rotate = min[1] - this->direction;
	if (rotate == 3 || rotate == -1) {
		// std::cout << "Gauche" << std::endl;
		ret.push_back(new Gauche(client));
		this->add_direction(-1);
	}
	else if (rotate == 1 || rotate == -3) {
		// std::cout << "Droite" << std::endl;
		ret.push_back(new Droite(client));
		this->add_direction(1);
	}

	if (min[1] % 2 == 0) {
		// std::cout << "Avance "<< delta_y << std::endl;
		ret.splice(ret.end(), this->gen_avance(delta_y));
	}
	else {
		// std::cout << "Avance "<< delta_x << std::endl;
		ret.splice(ret.end(), this->gen_avance(delta_x));
	}
	this->direction = dir;
	return (ret);
}

std::list<Icmd*>		Map::gen_avance(int n) {
	std::list<Icmd*>	li;
	int					i;

	n = abs(n);
	i = 0;
	while (i < n) {
		li.push_back(new Avance(client));
		i++;
	}
	return (li);
}

std::ostream & 		operator<<(std::ostream &o, Map const &rhs){
	int		i = -1;
	int		j = -1;

	while (++i < rhs.map_y)
	{
		j = -1;
		while (++j < rhs.map_x)
			o << rhs.map[i][j]->minify();
	}
	return (o);
}

// int		main(int ac, char **av) {
	
// 	if (ac == 4) {
// 		std::cout << "lala" << std::endl;
// 		Client c(av);
// 		Map a(10, 10, &c);

// 		// a.direction = 0;
// 		a.fill_map("{nourriture, joueur sibur, , , , , , , , , , , , , , ,phiras phiras, }");
// 		a.path_find("phiras");
// 	}
// 	return (0);
// }
