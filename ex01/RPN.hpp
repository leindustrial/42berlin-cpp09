/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ole <ole@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:32:04 by ole               #+#    #+#             */
/*   Updated: 2024/08/20 11:32:06 by ole              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <stack>
#include <algorithm>
#include <string>

class RPN
{
private:
	std::stack<int>	_stack;

public:
	RPN();
	~RPN();
	RPN(RPN const & copy);
	RPN & operator= (RPN const & copy);

	void error(const std::string & comment);
	void calculate(const std::string input);
};
