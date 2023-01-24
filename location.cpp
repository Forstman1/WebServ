/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <sahafid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:34:43 by sahafid           #+#    #+#             */
/*   Updated: 2023/01/23 18:33:02 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.hpp"

void    check_syntax(std::vector<Locations> &locations)
{
    
    for (std::vector<Locations>::iterator it = locations.begin(); it != locations.end(); it++)
    {
        Locations &currentDirective = *it;
        std::vector<std::string> location = currentDirective.raw_location;
        currentDirective.directive = location[0];
        for (std::vector<std::string>::iterator iter = location.begin(); iter != location.end(); iter++)
        {
            std::vector<std::string> info = split(*iter, ' ');
            // if (info)
        }
    }
}