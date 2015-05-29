/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brehaili <brehaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 14:17:16 by brehaili          #+#    #+#             */
/*   Updated: 2015/05/26 14:17:17 by brehaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include "buffer.hpp"

Buffer::Buffer() : buff(std::string(BUFF_SIZE, '\0')), start(0), end(0) {

}

Buffer::Buffer(const Buffer & obj) {
	*this = obj;
}

Buffer::~Buffer() {

}

Buffer &	Buffer::operator=(const Buffer & obj) {
	this->start = obj.start;
	this->end = obj.end;
	this->buff = obj.buff;
	return (*this);
}

void			Buffer::add(std::string str) {
	int		rest;
	int		size;

	size = str.size();
	rest = BUFF_SIZE - this->end;
	if (size <= rest) {
		this->buff.replace(this->end, size, str);
		this->end += size;
	}
	else {
		this->buff.replace(this->end, rest, str, 0, rest);
		this->buff.replace(0, size - rest, str, rest, size - rest);
		this->end = size - rest;
	}
}

void			Buffer::del(int nb) {
	int		rest;

	rest = BUFF_SIZE - this->start - 1;
	if (nb <= rest)
		this->start += nb;
	else
		this->start = nb - rest - 1;
}

std::string		Buffer::to_str(void) {
	std::string	tmp;

	if (this->end == this->start)
		return ("");
	else if (this->end > this->start)
		return (this->buff.substr(this->start, this->end - this->start));
	else {
		tmp += this->buff.substr(this->start, BUFF_SIZE - this->start);
		tmp += this->buff.substr(0, this->end);
		return (tmp);
	}
}

void			Buffer::print(void) {
	std::cout << "--------print----------" << std::endl;
	std::cout << "Raw: " << this->buff << std::endl;
	std::cout << "Str: " << this->to_str() << std::endl;
	std::cout << "-----------------------" << std::endl;
}
