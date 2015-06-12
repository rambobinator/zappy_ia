/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ia_picker.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brehaili <brehaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/12 16:18:48 by brehaili          #+#    #+#             */
/*   Updated: 2015/06/12 16:18:49 by brehaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ia.hpp"
#include "Client.hpp"

int			Ia::picker_init(Client &client) {
	if (client.needs.isEmpty()) {
		role = FEEDER;
		return (PICKER_INIT);
	}
	return (PICKER_INIT);
}