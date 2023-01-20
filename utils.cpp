/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <sahafid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:48:22 by sahafid           #+#    #+#             */
/*   Updated: 2023/01/20 15:16:42 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "config.hpp"

using namespace std;

int	ft_stoi(string str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + str[i++] - '0';
	if (i != str.length())
		res = -1;
	return (res);
}

string trim(string s, char c)
{
	string  str;
	size_t index = s.find_first_not_of(c);
    if (index != string::npos)
        str += s.substr(index);
    index = str.find_last_not_of(c);
    if (index != string::npos)
        str = str.substr(0, index + 1);
	return (str);
}

vector<string> split(string s, char c)
{
    string  str;
    vector<string> splited;
    int del=0,i=0,p=0,j=0;
    
	str = trim(s, c);
    for (int i = 0; i < str.length(); i++)
		if (str[i] == c && str[i + 1] != c)
			del++;
    while (del-- >= 0)
	{
		i = 0;
		while (str[p] != c && str[p++])
			i++;
		splited.push_back(str.substr(j, i));
		while (str[p] == c)
			p++;
		j = p;
	}
	return (splited);
}