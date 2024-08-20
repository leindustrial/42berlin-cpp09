/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ole <ole@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:32:36 by ole               #+#    #+#             */
/*   Updated: 2024/08/20 11:32:38 by ole              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main (int ac, char **av)
{
	PmergeMe newSort;

	if (ac < 2)
	{
		newSort.error("invalid input. Enter a positive integer sequence.");
		//std::cout << RED << "Error: invalid input. Enter a positive integer sequence." << RES << std::endl;
		return (0);
	}
	newSort.sort(ac - 1, &av[1]);
	return (0);
}
