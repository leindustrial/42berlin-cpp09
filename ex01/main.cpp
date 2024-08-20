/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ole <ole@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:31:53 by ole               #+#    #+#             */
/*   Updated: 2024/08/20 11:31:55 by ole              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Error: invalid argument. Enter an inverted Polish mathematical expression." << std::endl;
		std::cout << "Example: '8 9 * 9 - 9 - 9 - 4 - 1 +'" << std::endl;
		return (0);
	}
	else
	{
		RPN rpn1;
		rpn1.calculate(av[1]);
	}

	return (0);
}
