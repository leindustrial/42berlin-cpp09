/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ole <ole@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:30:51 by ole               #+#    #+#             */
/*   Updated: 2024/08/20 11:30:55 by ole              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
	this->create_database(DB);
}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(BitcoinExchange const & copy)
{
	*this = copy;
}

BitcoinExchange & BitcoinExchange::operator= (BitcoinExchange const & copy)
{
	this->_database = copy._database;
	return (*this);
}

void BitcoinExchange::create_database(const std::string &fileName)
{
	std::ifstream ifs(fileName.c_str());
	if (!ifs.is_open())
	{
		error("Can't open a file: ", fileName);
		return ;
	}

	std::string	key;
	float		value;
	std::string	line;

	while (std::getline(ifs, line))
	{
		if (std::isdigit(line[0]) && (line.find(',') != std::string::npos))
		{
			key = line.substr(0, line.find(','));
			value = std::atof(line.substr((line.find(',') + 1)).c_str());
			this->_database[key] = value;
		}
	}
	ifs.close();

	// Print database:
//	for (std::map<std::string, float>::iterator it = _database.begin(); it != _database.end(); it++)
//		std::cout << it->first << " " << it->second << std::endl;
}

void BitcoinExchange::exchange(const std::string & fileName)
{
	std::ifstream ifs(fileName.c_str());
	if (!ifs.is_open())
	{
		error("Can't open a file: ", fileName);
		return ;
	}

	std::string	date;
	float		value;
	std::string	line;

	while (std::getline(ifs, line))
	{
		if (std::isdigit(line[0]) || (std::isdigit(line[0]) && (line.find('|') != std::string::npos)))
		{
			date = line.substr(0, line.find('|') - 1);

			if (line.find('|') == std::string::npos)
				value = -1;
			else
				value = std::atof(line.substr((line.find('|') + 1)).c_str());
			//std::cout << "Date: '" << date << "', Value: '" << value << "'" << std::endl;

			// Ckeck date and value from .txt file
			// If OK, find value in database and multiply
			if (this->checkDate(date))
			{
				if (this->checkValue(value))
				{
					std::map<std::string, float>::const_iterator it = _database.lower_bound(date);
					// std::cout << "Lower bound:    " << it->first << " " << it->second << std::endl;
					if (it != _database.begin() && it->first != date)
						--it;
					// std::cout << "Lower bound -1: " << it->first << " " << it->second << std::endl;
					std::cout << date << " => " << value << " = " << it->second * value << std::endl;
				}
			}
		}
	}
	ifs.close();
}

int BitcoinExchange::checkDate(const std::string & date)
{
	if (date.length() < 10 || date.length() > 10)
	{
		error("wrong date format => ", date);
		return (0);
	}

	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());

	if (((year < 2009 || year > 2024) || (month < 1 || month > 12) || (day < 1 || day > 31)) \
		|| ((year == 2012 || year == 2016 || year == 2020 || year == 2024) && (month == 2) && (day > 29)) \
		|| ((year != 2012 && year != 2016 && year != 2020 && year != 2024) && (month == 2) && (day > 28)) \
		|| ((month == 4 || month == 6 || month == 9 || month == 11) && (day > 30)))
	{
		error("wrong date format => ", date);
		return (0);
	}

	return (1);
}

int BitcoinExchange::checkValue(float value)
{
	if (value < 0)
	{
		this->error("the value less than 0", "NULL");
		return(0);
	}
	else if (value > 1000)
	{
		this->error("the value is too large", "NULL");
		return(0);
	}
	return (1);
}

void BitcoinExchange::error(const std::string & comment, const std::string & comment2)
{
	if (comment2 == "NULL")
		std::cerr << "Error: " << comment << std::endl;
	else
		std::cerr << "Error: " << comment << comment2 << std::endl;
}
