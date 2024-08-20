/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ole <ole@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:31:04 by ole               #+#    #+#             */
/*   Updated: 2024/08/20 11:31:06 by ole              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <algorithm>
#include <iostream>
#include <string>
#include <iterator>
#include <fstream>

#define DB "data.csv"

class BitcoinExchange
{
private:
	std::map<std::string, float> _database;
public:
	BitcoinExchange();
	~BitcoinExchange();
	BitcoinExchange(BitcoinExchange const & copy);
	BitcoinExchange & operator= (BitcoinExchange const & copy);

	void create_database (const std::string & fileName);

	void exchange(const std::string & av);
	int checkDate(const std::string & date);
	int checkValue(float value);

	void error(const std::string & comment, const std::string & comment2);
};
