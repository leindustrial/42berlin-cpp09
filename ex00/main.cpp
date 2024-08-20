/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ole <ole@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:31:20 by ole               #+#    #+#             */
/*   Updated: 2024/08/20 11:31:24 by ole              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Error: invalid argument. Please, enter a file name." << std::endl;
		return (0);
	}
	else
	{
		BitcoinExchange btc1;
		btc1.exchange(av[1]);
	}
	return (0);
}
