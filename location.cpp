/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <sahafid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:34:43 by sahafid           #+#    #+#             */
/*   Updated: 2023/01/24 11:19:24 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.hpp"


void    Servers::split_locations(std::vector<std::string> &server_info)
{
    for (std::vector<std::string>::iterator it = server_info.begin(); it != server_info.end(); it++)
    {
        Locations location;
        int braket = 0;
        std::vector<std::string> info = split(*it, ' ');
        if (info[0] == "location")
        {
            if (info.size() != 3 || info[1][0] != '/' || info[2] != "{")
                throw std::invalid_argument("Syntax Error: invalid location");
            braket++;
            std::vector<std::string> rawlocation;
            rawlocation.push_back(info[1]);
            it = server_info.erase(it);
            while (it != server_info.end() && (*it)[0] != '}')
            {
                if (!((*it).empty()))
                    rawlocation.push_back(*it);
                it = server_info.erase(it);
            }
            location.raw_location = rawlocation;
            locations.push_back(location);
        }
        if ((*it)[0] == '}')
            *it = "";
    }
}

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