/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brehaili <brehaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 14:17:04 by brehaili          #+#    #+#             */
/*   Updated: 2015/05/26 14:17:06 by brehaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_HPP
#define BUFFER_HPP
#define	BUFF_SIZE 4096


class Buffer {
public:
	Buffer();
	Buffer(const Buffer & obj);
	~Buffer();
	Buffer & 	operator=(const Buffer & obj);
	void		add(std::string);
	void		del(int nb);
	std::string	to_str(void);
	void		print(void);
	std::string	buff;
	int			start;
	int			end;

private:
};

#endif
