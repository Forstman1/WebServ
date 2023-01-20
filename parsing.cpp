/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <sahafid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:12:23 by sahafid           #+#    #+#             */
/*   Updated: 2023/01/20 16:51:43 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.hpp"

void    check_brackets(std::vector<std::string> &lines)
{
    int braket = 0;
    for (std::vector<std::string>::iterator it = lines.begin(); it != lines.end(); it++)
    {
        std::vector<std::string> line = split(*it, ' ');
        if (line[0] == "server")
        {
            if (line.size() > 2 && line[1] != "{")
                throw std::invalid_argument("Syntax Error");
            braket++;
        }
        else
        {
            for (std::vector<std::string>::iterator iter = line.begin(); iter != line.end(); iter++)
            {
                if (*iter == "{")
                    braket++;
                else if (*iter == "}")
                    braket--;
            }
        }
    }
    if (braket != 0)
        throw std::invalid_argument("Syntax Error");
}


void    split_servers(std::vector<std::string> &lines, std::vector<Servers> &servers)
{
    int braket = 0;
    std::vector<std::string> raw;
    for (std::vector<std::string>::iterator it = lines.begin(); it != lines.end(); it++)
    {
        std::vector<std::string> line = split(*it, ' ');
        if (it == lines.begin())
            braket++;
        else
        {
            for (std::vector<std::string>::iterator iter = line.begin(); iter != line.end(); iter++)
            {
                if (*iter == "{")
                    braket++;
                else if (*iter == "}")
                    braket--;
            }
        }
        raw.push_back(*it);
        if (braket == 0)
        {
            Servers server;
            for (std::vector<std::string>::iterator itera = raw.begin(); itera != raw.end(); itera++)
            {
                *itera = trim(*itera, ' ');
                *itera = trim(*itera, 9);
            }
            server.raw_server = raw;
            servers.push_back(server);
            raw.clear();
        }
    }
}

void    Servers::split_locations(std::vector<std::string> &server_info)
{
    for (std::vector<std::string>::iterator it = server_info.begin(); it != server_info.end(); it++)
    {
        Locations location;
        std::vector<std::string> info = split(*it, ' ');
        if (info[0] == "location")
        {
            if (info.size() != 4 || info[1][0] != '/' || info[2] != "{")
            {
                // std::cout << info[1][0] << " " << info[2] << " " << info.size() << std::endl;
                throw std::invalid_argument("Syntax Error: invalid location");
            }
            std::vector<std::string> rawlocation;
            rawlocation.push_back(info[1]);
            it++;
            while (it != server_info.end() && it[0] != "}")
            {
                rawlocation.push_back(*it);
                it++;
                std::cerr << it[0] << " t" << std::endl;
            }
            location.raw_location = rawlocation;
            locations.push_back(location);
        }
    }
}


void    Servers::check_syntaxError(std::vector<std::string> &server_info)
{
    for (std::vector<std::string>::iterator it = server_info.begin(); it != server_info.end(); it++)
    {
        std::vector<std::string> info = split(*it, ' ');
        if (info[info.size() - 1][info[info.size() - 1].size() -1] == ';')
        {
            if (info.size() > 1 && info[0] == "listen")
            {
                int port = ft_stoi(info[1]);
                if (port < 0)
                    throw std::invalid_argument("Syntax Error: invalid port number");
                else
                    this->port = port;
            }
        }
        else
            if (info[0] != "server")
                throw std::invalid_argument("Syntax Error: semicolone missing");
    }
}

void    Config::parse_servers(Servers &server)
{
    std::vector<std::string> server_info = server.raw_server;
    

    server.split_locations(server_info);
    // server.check_syntaxError(server_info);
    
}

void    Config::parse(std::string filename)
{
    std::ifstream fd;
    fd.open(filename);

    std::vector<std::string> lines;
    std::string line;
    if (!fd.is_open())
		throw std::invalid_argument("can't open file");
    while (getline(fd, line))
        if (!line.empty())
		    lines.push_back(line.append(" \n"));
    check_brackets(lines);
    split_servers(lines, servers);
    // for (std::vector<Servers>::iterator it = servers.begin(); it != servers.end(); it++)
    // {
    //     std::vector<std::string> test = (*it).raw_server;
    //     for (std::vector<std::string>::iterator iter = test.begin(); iter != test.end(); iter++)
    //         std::cout << *iter;
    //     std::cout << std::endl;
    // }
    
    for (std::vector<Servers>::iterator it = servers.begin(); it != servers.end(); it++)
        parse_servers(*it);
}