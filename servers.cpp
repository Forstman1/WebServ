/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   servers.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <sahafid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:19:21 by sahafid           #+#    #+#             */
/*   Updated: 2023/01/24 11:13:05 by sahafid          ###   ########.fr       */
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
            while (it != server_info.end() && ((*it)[0] != '}' || braket == 2))
            {
                info = split(*it, ' ');
                if (info.size() == 3 && info[0] == "limit_except" && info[2] == "{")
                    braket++;
                if (info[0][0] == '}')
                    braket--;
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


void    checkSemicolone(std::vector<std::string> info)
{
    int semi = 0;
    if (info[info.size() - 1][info[info.size() - 1].size() -1] == ';')
    {
        for (std::vector<std::string>::iterator it = info.begin(); it != info.end(); it++)
        {
            std::string word = *it;
            for (int i =0; i < word.length(); i++)
                if (word[i] == ';')
                    semi++;
        }
    }
    else
        if (!(info[0]).empty())
            throw std::invalid_argument("Syntax Error: semicolone missing"); 
    if (semi > 1)
        throw std::invalid_argument("Syntax Error: extra semicolone");
}



void    checkHost(std::string info)
{
    int point = 0;
    std::string check;
    for (std::string::iterator it = info.begin(); it != info.end(); it++)
    {
        if (*it == '.')
        {
            int number = ft_stoi(check);
            if (number > 255 || number < 0)
                throw std::invalid_argument("Syntax Error: invalid host");
            point++;
            check.clear();
        }
        else if (point <= 3 && isdigit(*it))
            check += *it;
        else
            throw std::invalid_argument("Syntax Error: invalid host");
    }
    if (point != 3)
        throw std::invalid_argument("Syntax Error: invalid host");
    int number = ft_stoi(check);
    if (number > 255 || number < 0)
        throw std::invalid_argument("Syntax Error: invalid host");
}


void    Servers::enterData(std::vector<std::string> info)
{
    trim(info[info.size()-1], ';');
    if (info.size() > 1 && info[0] == "listen")
    {
        int port = ft_stoi(info[1]);
        if (port < 0)
            throw std::invalid_argument("Syntax Error: invalid port number");
        else
            this->port = port;
    }
    else if (info.size() > 2 && info[0] == "server_name")
    {
        for (std::vector<std::string>::iterator iter = info.begin() + 1; iter != info.end(); iter++)
        {
            if (info.begin() + 1 != iter)
                this->server_name += " ";
            this->server_name += *iter;
        }
    }
    else if (info.size() > 1 && info[0] == "error_page")
    {
        for (std::vector<std::string>::iterator iter = info.begin() + 1; iter != info.end(); iter++)
        {
            if (info.begin() + 1 != iter)
                this->error_page += " ";
            this->error_page += *iter;
        }
    }
    else if (info.size() > 1 && info[0] == "client_max_body_size")
    {
        if (info.size() != 3)
        {
            std::string sizeBody = info[1];
            //  A value of '0' which means no limit and this is not recommended in production environment
            if (sizeBody.size() == 2 && sizeBody[0] != 0)
                throw std::invalid_argument("invalid max body size");
            char unit = tolower(sizeBody[sizeBody.size() - 1]);
            if (sizeBody.size() > 2 &&  (unit != 'm' && unit != 'k'))
                throw std::invalid_argument("invalid max body size");
            if (unit == 'k')
            {
                trim(sizeBody, 'k');
                client_max_body_size = ft_stoi(sizeBody);
                if (client_max_body_size < 0)
                    throw std::invalid_argument("invalid max body size");
                client_max_body_size = client_max_body_size / 1000;                
            }
            else
            {
                trim(sizeBody, 'm');
                client_max_body_size = ft_stoi(sizeBody);
                if (client_max_body_size < 0)
                    throw std::invalid_argument("invalid max body size");
            }
            std::cout << client_max_body_size << std::endl;
        }
        else
            throw std::invalid_argument("Syntax Error: wrong number of arguments"); 
    }
    else if (info.size() > 1 && info[0] == "host")
    {
        if (info.size() == 2)
        {
            trim(info[1], ';');
            checkHost(info[1]);
        }
        else
            throw std::invalid_argument("Syntax Error: wrong number of arguments"); 
    }
}

void    Servers::check_syntaxError(std::vector<std::string> &server_info)
{
    server_info.erase(server_info.begin());        
    for (std::vector<std::string>::iterator it = server_info.begin(); it != server_info.end(); it++)
    {
        std::vector<std::string> info = split(*it, ' ');
        checkSemicolone(info);
        enterData(info);
    }
}