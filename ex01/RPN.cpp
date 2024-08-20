/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ole <ole@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:32:16 by ole               #+#    #+#             */
/*   Updated: 2024/08/20 11:32:17 by ole              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(){}
RPN::~RPN(){}
RPN::RPN(RPN const & copy)
{
	*this = copy;
}

RPN & RPN::operator=(const RPN &copy)
{
	this->_stack = copy._stack;
	return (*this);
}

void RPN::error(const std::string &comment)
{
	std::cout << "Error: " << comment << std::endl;
}

void RPN::calculate(const std::string input)
{
	std::string::const_iterator it = input.begin();
	std::string::const_iterator ite = input.end();

	while (it != ite)
	{
		if(std::isdigit(*it))
		{
			//std::cout << "*it: " << *it << std::endl;
			int n = *it - '0';
//			std::cout << "n: " << n << std::endl;
			_stack.push(n);
		}
		else if (*it == '+' || *it == '-' || *it == '*' || *it == '/')
		{
			if (_stack.size() < 2)
			{
				error("invalid input. Not a RPN");
				return ;
			}
			int num2 = _stack.top();
			_stack.pop();
			int num1 = _stack.top();
			_stack.pop();
			if (*it == '+')
			{
				_stack.push(num1 + num2);
//				std::cout << "NUM: " << num1 << " " << num2 << std::endl;
//				std::cout << "Top: " << _stack.top() << std::endl;
			}
			if (*it == '-')
			{
				_stack.push(num1 - num2);
//				std::cout << "NUM: " << num1 << " " << num2 << std::endl;
//				std::cout << "Top: " << _stack.top() << std::endl;
			}
			if (*it == '*')
			{
				_stack.push(num1 * num2);
//				std::cout << "NUM: " << num1 << " " << num2 << std::endl;
//				std::cout << "Top: " << _stack.top() << std::endl;
			}
			if (*it == '/')
			{
				if (num2 == 0)
				{
					error("invalid input. Can't divide by '0'");
					return ;
				}
				else
				{
					_stack.push(num1 / num2);
//					std::cout << "NUM: " << num1 << " " << num2 << std::endl;
//					std::cout << "Top: " << _stack.top() << std::endl;
				}
			}

		}
		else if (*it != ' ')
		{
			error("invalid input.");
			return ;
		}
		it++;
	}
//	std::cout << "Stack size: " <<_stack.size()<< std::endl;
//	std::cout << "Stack top: " <<_stack.top()<< std::endl;

	std::cout << "Result: " <<_stack.top()<< std::endl;
}
