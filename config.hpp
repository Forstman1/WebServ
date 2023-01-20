/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <sahafid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:45:25 by sahafid           #+#    #+#             */
/*   Updated: 2023/01/20 16:38:14 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "fcntl.h"
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <exception>

class Locations {
    public:
        std::vector<std::string> raw_location;
        
};

class Servers {
    public:
        std::vector<std::string> raw_server;
        int port;
        std::string server_name;
        std::string root;
        std::vector<Locations> locations;
        void    split_locations(std::vector<std::string> &server_info);
        void    check_syntaxError(std::vector<std::string> &server_info);
};

class Config {
    private:
        int i;
        std::vector<Servers> servers;
    public :
        void    parse(std::string filename);
        void    parse_servers(Servers &server);
        
};

std::vector<std::string> split(std::string s, char c);
std::string trim(std::string s, char c);
int	ft_stoi(std::string str);
