/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   servers.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <sahafid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:19:21 by sahafid           #+#    #+#             */
/*   Updated: 2023/01/25 00:01:06 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.hpp"


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



void    Servers::checkHost(std::string info)
{
    int point = 0;
    std::string check;
    std::string host;
    if (info == "localhost")
    {
        this->host = "127.0.0.1";
        return ;
    }
    for (std::string::iterator it = info.begin(); it != info.end(); it++)
    {
        if (*it == '.')
        {
            int number = ft_stoi(check);
            if (number > 255 || number < 0)
                throw std::invalid_argument("Syntax Error: invalid host");
            point++;
            host += check;
            host += '.';
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
    
    host += check;
    this->host = host;
}

int    allcodes(int code)
{
    std::vector<int> codes;
    codes.push_back(401);
    codes.push_back(400);
    codes.push_back(403);
    codes.push_back(404);
    codes.push_back(500);
    codes.push_back(502);
    codes.push_back(503);
    if (std::find(codes.begin(), codes.end(), code) != codes.end())
        return true;
    return false;
}

void    Servers::errorPage(std::vector<std::string> info)
{
    static std::vector<int> saved_codes;

    int status = ft_stoi(info[1]);
    if (std::find(saved_codes.begin(), saved_codes.end(), status) != saved_codes.end())
        throw std::invalid_argument("Syntax error: duplicate status code");

    if (allcodes(status))
    {
        saved_codes.push_back(status);
        errorPages current;
        std::ifstream file;
        current.status_code = status;
        if (info.size() == 3)
        {
            file.open(info[2]);
            current.path = info[2];
            if (!file)
                current.path = "./error/error.html";
        }
        else
            current.path = "./error/error.html";
        this->error_page.push_back(current);
    }
    else
        throw std::invalid_argument("Syntax error: invalid status code");
}


void    Servers::enterData(std::vector<std::string> info)
{
    trim(info[info.size()-1], ';');
    if (info.size() > 1 && info[0] == "listen")
    {
        for (std::vector<std::string>::iterator it = info.begin() + 1; it != info.end(); it++)
        {
            int port = ft_stoi(*it);
            if (port < 0)
                throw std::invalid_argument("Syntax Error: invalid port number");
            else
            {
                if (std::find(this->port.begin(), this->port.end(), port) != this->port.end())
                    throw std::invalid_argument("Syntax Error: duplicate port number");
                this->port.push_back(port);
            }
        }
        
    }
    else if (info.size() > 2 && info[0] == "server_name")
    {
        for (std::vector<std::string>::iterator iter = info.begin() + 1; iter != info.end(); iter++)
            this->server_name.push_back(*iter);
    }
    else if (info.size() > 1 && info[0] == "error_page")
    {
        if (info.size() == 3 || info.size() == 2)
            errorPage(info);
        else
            throw std::invalid_argument("wrong number of arguments");
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
        }
        else
            throw std::invalid_argument("Syntax Error: wrong number of arguments");
    }
    else if (info.size() > 1 && info[0] == "host")
    {
        if (info.size() == 2)
            checkHost(info[1]);
        else
            throw std::invalid_argument("Syntax Error: wrong number of arguments"); 
    }
    else if (info.size() > 1 && info[0] == "root")
    {
        if (info.size() == 2)
            this->root = info[1];
        else
            throw std::invalid_argument("Syntax Error: wrong number of arguments"); 
    }
    else
        if (!info[0].empty())
            throw std::invalid_argument("Syntax Error: unknow argument"); 
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