/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkvalid.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <sahafid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:43:04 by sahafid           #+#    #+#             */
/*   Updated: 2023/01/26 14:32:05 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.hpp"



void    checkFile(std::vector<errorPages> error_pages)
{
    for (std::vector<errorPages>::iterator it = error_pages.begin(); it != error_pages.end(); it++)
    {
        std::ifstream file;
        file.open((*it).path);
        if (!file)
            (*it).path = "./error/";
    }
}

void    checkDataValidity(Servers &server)
{
    std::vector<int> ports;
    if (server.port.size() > 0)
    {
        for (std::vector<int>::iterator it = server.port.begin(); it != server.port.end(); it++)
        {
            if (!(find(ports.begin(), ports.end(), *it) != ports.end()))
                ports.push_back(*it);
            else
                throw std::invalid_argument("invalid input: duplicate port number");
        }
    }
    else
        throw std::invalid_argument("invalid input: no port number");
    
    if (server.host.empty())
        throw std::invalid_argument("invalid input: no host");

}