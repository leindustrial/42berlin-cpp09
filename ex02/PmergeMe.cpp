/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ole <ole@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:33:02 by ole               #+#    #+#             */
/*   Updated: 2024/08/20 11:33:04 by ole              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

// Orthodox canonical form --------------------------------------------------------------------------------
PmergeMe::PmergeMe() {}
PmergeMe::~PmergeMe() {}
PmergeMe::PmergeMe(PmergeMe const & copy) {*this = copy;}
PmergeMe & PmergeMe::operator= (PmergeMe const & copy)
{
	this->_unsortedList = copy._unsortedList;
	this->_unsortedVect = copy._unsortedVect;
	this->_isOdd = copy._isOdd;
	this->_lastOdd = copy._lastOdd;
	return (*this);
}
// --------------------------------------------------------------------------------------------------------

// START THE PROGRAMM -------------------------------------------------------------------------------------
void PmergeMe::sort(int ac, char **av)
{
	// Parse / check the input:
	if (this->checkInput(ac, av))
		return ;
	if (this->convertNumbers(ac, av))
		return ;

	//Execute and sort:
	std::clock_t	start;
	double			timeList;
	double			timeVect;

	start = std::clock();
	this->sortList();
	timeList = ( std::clock() - start ) * 1000 / (double) CLOCKS_PER_SEC;

	timeVect = std::clock();
	this->sortVector();
	timeVect = ( std::clock() - start ) * 1000 / (double) CLOCKS_PER_SEC;

	//Print the result:
	std::cout << GRN << "\nRESULT-------------------------------------------------------------------------" << RES << std::endl;
	std::cout << "Before:       ";
	this->printNumbers(this->_unsortedList);
	std::cout << "After / LIST: ";
	this->printNumbers(this->_sortedList);
	std::cout << "After / VECT: ";
	this->printNumbers(this->_sortedVect);
	std::cout << "Time / LIST:  " << GRN << timeList << " ms" << RES << std::endl;
	std::cout << "Time / VECT:  " << GRN << timeVect << " ms" << RES << std::endl;
	std::cout << GRN << "END----------------------------------------------------------------------------\n" << RES << std::endl;
}

// PARSE / CHECK INPUT ------------------------------------------------------------------------------------
int PmergeMe::checkInput(int ac, char **av)
{
	for (int i = 0; i < ac; i++)
	{
		for (int j = 0; av[i][j] != '\0'; j++)
		{
			if (!(std::isdigit(av[i][j])) && av[i][j] != ' ' && av[i][j] != '-' && av[i][j] != '+')
			{
				error("invalid input. Not a digit.");
				return (1);
			}
		}
	}
	return (0);
}

int PmergeMe::convertNumbers(int ac, char **av)
{
	for (int i = 0; i < ac; i++)
	{
		int num = std::atoi(av[i]);
		if (num < 0)
		{
			error("invalid input. Can't sort a negative number.");
			return (1);
		}
		else if (std::find(_unsortedList.begin(), _unsortedList.end(), num) != _unsortedList.end())
		{
			error("invalid input. A dublicate found.");
			return (1);
		}
		else
		{
			_unsortedList.push_back(num);
			_unsortedVect.push_back(num);
		}
	}
	return (0);
}
// --------------------------------------------------------------------------------------------------------

// LIST SORT ----------------------------------------------------------------------------------------------

void PmergeMe::sortList()
{
	if (_unsortedList.size() == 1)
	{
		_sortedList = _unsortedList;
		return;
	}

	std::list<std::pair<int, int> > pairList;
	std::list<int> mainChainList;
	std::list<int> pendList;
	std::list<int> jacobsthalSequenceList;
	std::list<int> sortSequenceList;

	this->_isOdd = false;
	if (_unsortedList.size() % 2 != 0)
	{
		_lastOdd = _unsortedList.back();
		_unsortedList.pop_back();
		this->_isOdd = true;
	}

	std::cout << BLU << "\nLIST INFO----------------------------------------------------------------------" << RES << std::endl;

	//Create a new list of pairs:
	pairList = this->createPairsList();
	std::cout << BLU << "Unsorted pairs:          " << RES;
	this->printPairs(pairList);

	//Sort numbers in pairs:
	this->sortNumPairsList(pairList);
	std::cout << BLU << "Sorted numbers in pairs: " << RES;
	this->printPairs(pairList);

	//Sort pairs by first number in pair:
	this->recursiveMergeSortList(pairList, 0, pairList.size() - 1);
	std::cout << BLU << "Sorted pairs:            " << RES;
	this->printPairs(pairList);

	//Create main list:
	this->mainChainList(mainChainList, pairList);
	std::cout << BLU << "\nMain List:                " << RES;
	this->printNumbers(mainChainList);

	// If there is only 2 numbers:
	if (_unsortedList.size() == 2 && _isOdd == false)
	{
		_sortedList = mainChainList;
		return;
	}

	//Create pending list:
	this->pendList(pendList, pairList);
	std::cout << BLU << "Pend List:                " << RES;
	this->printNumbers(pendList);

	//Insert pend list into main list:
	this->generateJacobsthalList(jacobsthalSequenceList, pendList);
	std::cout << BLU << "Jacobsthal Sequence:      " << RES;
	this->printNumbers(jacobsthalSequenceList);

	this->createSortSequenceList(sortSequenceList, jacobsthalSequenceList, pendList);
	std::cout << BLU << "Sort Sequence:            " << RES;
	this->printNumbers(sortSequenceList);

	this->insertPendList(mainChainList, pendList, sortSequenceList);

	if (_isOdd == true)
		std::cout << BLU << "Last odd number:          " << RES << _lastOdd << std::endl;

	if (this->_isOdd == true)
		_unsortedList.push_back(_lastOdd);

	std::cout << BLU << "-------------------------------------------------------------------------------" << RES << std::endl;
}

std::list< std::pair<int, int> > PmergeMe::createPairsList(void)
{
	std::list< std::pair<int, int> > pairList;
	std::pair<int, int> newPair;
	std::list<int>::iterator it = _unsortedList.begin();
	std::list<int>::iterator ite = _unsortedList.end();

	while(it != ite)
	{
		newPair.first = *it;
		newPair.second = *(++it);
		pairList.push_back(newPair);
		++it;
	}

	return (pairList);
}

void PmergeMe::sortNumPairsList(std::list <std::pair<int, int> > &pairList)
{
	std::list< std::pair<int, int> >::iterator it = pairList.begin();
	std::list< std::pair<int, int> >::iterator ite = pairList.end();

	while(it != ite)
	{
		if ((*it).first < (*it).second)
		{
			std::pair<int, int> newPair;
			newPair.first = (*it).second;
			newPair.second = (*it).first;
			std::swap (*it, newPair);
		}
		it++;
	}
}

void PmergeMe::recursiveMergeSortList(std::list <std::pair<int, int> > &pairList, int begin, int end)
{
	if (begin >= end)
		return ;

	int middle = begin + (end - begin) / 2;
	this->recursiveMergeSortList(pairList, begin, middle);
	this->recursiveMergeSortList(pairList, middle + 1, end);

	this->mergeList(pairList, begin, middle, end);
}

void PmergeMe::mergeList(std::list <std::pair<int, int> > &pairList, int begin, int middle, int end)
{
	//std:: cout << "Left: " << left << ", Middle: " << middle << ", Right: " << right << std::endl;
	std::list< std::pair<int, int> >::iterator l_start = pairList.begin();
	std::advance(l_start, begin);
	std::list< std::pair<int, int> >::iterator l_end = pairList.begin();
	std::advance(l_end, middle + 1);
	std::list< std::pair<int, int> >::iterator r_start = pairList.begin();
	std::advance(r_start, middle + 1);
	std::list< std::pair<int, int> >::iterator r_end = pairList.end();
	std::advance(r_end, end + 2);

	std::list <std::pair<int, int> > leftList;
	std::list <std::pair<int, int> > rightList;

	leftList.insert(leftList.begin(), l_start, l_end);
	rightList.insert(rightList.begin(), r_start, r_end);

// Print pair sorting process:
	std:: cout << "leftList: ";
	this->printPairs(leftList);
	std:: cout << "rightList: ";
	this->printPairs(rightList);

	std::list< std::pair<int, int> >::iterator p = pairList.begin();
	std::advance(p, begin);
	std::list< std::pair<int, int> >::iterator l = leftList.begin();
	std::list< std::pair<int, int> >::iterator r = rightList.begin();
	while (l != leftList.end() && r != rightList.end())
	{
		if((*l).first < (*r).first)
			this->swapPairs(*l++, *p);
		else
			this->swapPairs(*r++, *p);
		p++;
	}

	while (l != leftList.end())
		this->swapPairs(*l++, *p++);

	while (r != rightList.end())
		this->swapPairs(*r++, *p++);
}

void PmergeMe::mainChainList(std::list<int> &mainChainList, std::list<std::pair<int, int> > &pairList)
{
	std::list<std::pair<int, int> >::iterator it = pairList.begin();

	mainChainList.push_back((*it).second);
	while (it != pairList.end())
		mainChainList.push_back((*it++).first);
}

void PmergeMe::pendList(std::list<int> &pendList, std::list<std::pair<int, int> > &pairList)
{
	std::list<std::pair<int, int> >::iterator it = pairList.begin();

	while (it != pairList.end())
		pendList.push_back((*it++).second);
}

void PmergeMe::generateJacobsthalList(std::list<int> &jacobsthalSequenceList, std::list<int> &pendList)
{
	int jsNum;
	int pos = 3;
	int size = pendList.size();

	if (size < 3)
	{
		jacobsthalSequenceList.push_back(2);
		return ;
	}

	while ((jsNum = this->jacobsthal(pos)) <= size)
	{
		jacobsthalSequenceList.push_back(jsNum);
		pos++;
	}
}

void PmergeMe::createSortSequenceList(std::list<int> &sortSequenceList, std::list<int> &jacobsthalSequenceList, std::list<int> &pendList)
{
	int num;
	int prev_num = 1;
	int size = pendList.size();

	std::list<int>::iterator i = jacobsthalSequenceList.begin();

	while (i != jacobsthalSequenceList.end())
	{
		num = *i;
		while (num > prev_num)
		{
			sortSequenceList.push_back(num);
			num--;
		}
		prev_num = *i;
		i++;
	}
	num = jacobsthalSequenceList.back();
	num++;
	while (num <= size)
	{
		sortSequenceList.push_back(num);
		num++;
	}
}

void PmergeMe::insertPendList(std::list<int> &mainChainList, std::list<int> &pendList, std::list<int> &sortSequenceList)
{
	std::list<int>::iterator s = sortSequenceList.begin();
	std::list<int>::iterator p;
	std::list<int>::iterator m;
	int insert_num;
	int pos;
	int end_pos;
	int i = 0;

	if (pendList.size() > 1)
	{
		while (s != sortSequenceList.end())
		{
			p = pendList.begin();
			std::advance(p, *s - 1);
			insert_num = *p;
			end_pos = *s + i;
			pos = this->findPosList(mainChainList, insert_num, 0, end_pos);
			m = mainChainList.begin();
			std::advance(m, pos);
			mainChainList.insert(m, insert_num);
			i++;
			s++;
		}
	}
	if (this->_isOdd == true)
	{
		pos = this->findPosList(mainChainList, _lastOdd, 0, mainChainList.size() - 1);
		m = mainChainList.begin();
		std::advance(m, pos);
		mainChainList.insert(m, _lastOdd);
	}
	_sortedList = mainChainList;
}

int PmergeMe::findPosList(std::list<int> &mainChainList, int insert_num, int begin, int end)
{
	int middle;
	std::list<int>::iterator m;

	while (begin <= end)
	{
		middle = begin + (end - begin) / 2;
		m = mainChainList.begin();
		std::advance(m, middle);
		if (insert_num > *m)
			begin = middle + 1;
		else
			end = middle - 1;
	}
	if (insert_num > *m)
		return (middle + 1);
	else
		return (middle);
}

// --------------------------------------------------------------------------------------------------------

// Vector sort --------------------------------------------------------------------------------------------

void PmergeMe::sortVector()
{
	if (_unsortedVect.size() == 1)
	{
		_sortedVect = _unsortedVect;
		return;
	}

	std::vector<std::pair<int, int> > pairVect;
	std::vector<int> mainChainVect;
	std::vector<int> pendVect;
	std::vector<int> jacobsthalSequenceVect;
	std::vector<int> sortSequenceVect;

	this->_isOdd = false;
	if (_unsortedVect.size() % 2 != 0)
	{
		_lastOdd = _unsortedVect.back();
		_unsortedVect.pop_back();
		this->_isOdd = true;
	}

	std::cout << YEL << "\nVECT INFO----------------------------------------------------------------------" << RES << std::endl;

	//Create a new list of pairs:
	pairVect = this->createPairsVect();
	std::cout << YEL << "Unsorted pairs:          " << RES;
	this->printPairs(pairVect);

	//Sort numbers in pairs:
	this->sortNumPairsVect(pairVect);
	std::cout << YEL << "Sorted numbers in pairs: " << RES;
	this->printPairs(pairVect);


	this->recursiveMergeSortVect(pairVect, 0, pairVect.size() - 1);
	std::cout << YEL << "Sorted pairs:            " << RES;
	this->printPairs(pairVect);


	this->mainChainVect(mainChainVect, pairVect);
	if (_unsortedVect.size() == 2 && _isOdd == false)
	{
		_sortedVect = mainChainVect;
		return;
	}

	std::cout << YEL << "\nMain Vect:                " << RES;
	this->printNumbers(mainChainVect);

	this->pendVect(pendVect, pairVect);
	std::cout << YEL << "Pend Vect:                " << RES;
	this->printNumbers(pendVect);

	this->generateJacobsthalVect(jacobsthalSequenceVect, pendVect);
	std::cout << YEL << "Jacobsthal Sequence:      " << RES;
	this->printNumbers(jacobsthalSequenceVect);

	this->createSortSequenceVect(sortSequenceVect, jacobsthalSequenceVect, pendVect);
	std::cout << YEL << "Sort Sequence:            " << RES;
	this->printNumbers(sortSequenceVect);

	this->insertPendVect(mainChainVect, pendVect, sortSequenceVect);

	if (_isOdd == true)
		std::cout << YEL << "Last odd number:          " << RES << _lastOdd << std::endl;

	std::cout << YEL << "-------------------------------------------------------------------------------" << RES << std::endl;
}


std::vector< std::pair<int, int> > PmergeMe::createPairsVect(void)
{
	std::vector< std::pair<int, int> > pairVect;
	std::pair<int, int> newPair;
	std::vector<int>::iterator it = _unsortedVect.begin();
	std::vector<int>::iterator ite = _unsortedVect.end();

	while(it != ite)
	{
		newPair.first = *it;
		newPair.second = *(++it);
		pairVect.push_back(newPair);
		++it;
	}

//	int size = _unsortedVect.size();
//	for (int i = 0; i < size; i++)
//	{
//		newPair.first = _unsortedVect[i];
//		newPair.second = _unsortedVect[i + 1];
//		pairVect.push_back(newPair);
//		i += 2;
//	}

	return (pairVect);
}

void PmergeMe::sortNumPairsVect(std::vector <std::pair<int, int> > &pairVect)
{
	std::vector< std::pair<int, int> >::iterator it = pairVect.begin();
	std::vector< std::pair<int, int> >::iterator ite = pairVect.end();

	while(it != ite)
	{
		if ((*it).first < (*it).second)
		{
			std::pair<int, int> newPair;
			newPair.first = (*it).second;
			newPair.second = (*it).first;
			std::swap (*it, newPair);
		}
		it++;
	}
}

void PmergeMe::recursiveMergeSortVect(std::vector <std::pair<int, int> > &pairVect, int begin, int end)
{
	if (begin >= end)
		return ;

	int middle = begin + (end - begin) / 2;
	this->recursiveMergeSortVect(pairVect, begin, middle);
	this->recursiveMergeSortVect(pairVect, middle + 1, end);

	this->mergeVect(pairVect, begin, middle, end);
}

void PmergeMe::mergeVect(std::vector <std::pair<int, int> > &pairVect, int begin, int middle, int end)
{
	std::vector <std::pair<int, int> > leftVect(pairVect.begin() + begin, pairVect.begin() + (middle + 1));
	std::vector <std::pair<int, int> > rightVect(pairVect.begin() + (middle + 1), pairVect.begin() + (end + 1));

// Print pair sorting process:
	std:: cout << "leftVect: ";
	this->printPairs(leftVect);
	std:: cout << "rightVect: ";
	this->printPairs(rightVect);

	std::vector< std::pair<int, int> >::iterator p = pairVect.begin() + begin;
	std::vector< std::pair<int, int> >::iterator l = leftVect.begin();
	std::vector< std::pair<int, int> >::iterator r = rightVect.begin();

	while (l != leftVect.end() && r != rightVect.end())
	{
		if((*l).first < (*r).first)
			this->swapPairs(*l++, *p);
		else
			this->swapPairs(*r++, *p);
		p++;
	}

	while (l != leftVect.end())
		this->swapPairs(*l++, *p++);

	while (r != rightVect.end())
		this->swapPairs(*r++, *p++);
}

void PmergeMe::mainChainVect(std::vector<int> &mainChainVect, std::vector<std::pair<int, int> > &pairVect)
{
	std::vector<std::pair<int, int> >::iterator it = pairVect.begin();

	mainChainVect.push_back((*it).second);
	while (it != pairVect.end())
		mainChainVect.push_back((*it++).first);
}

void PmergeMe::pendVect(std::vector<int> &pendVect, std::vector<std::pair<int, int> > &pairVect)
{
	std::vector<std::pair<int, int> >::iterator it = pairVect.begin();

	while (it != pairVect.end())
		pendVect.push_back((*it++).second);
}

void PmergeMe::generateJacobsthalVect(std::vector<int> &jacobsthalSequenceVect, std::vector<int> &pendVect)
{
	int jsNum;
	int pos = 3;
	int size = pendVect.size();

	if (size < 3)
	{
		jacobsthalSequenceVect.push_back(2);
		return ;
	}

	while ((jsNum = this->jacobsthal(pos)) <= size)
	{
		jacobsthalSequenceVect.push_back(jsNum);
		pos++;
	}
}

void PmergeMe::createSortSequenceVect(std::vector<int> &sortSequenceVect, std::vector<int> &jacobsthalSequenceVect, std::vector<int> &pendVect)
{
	int num;
	int prev_num = 1;
	int size = pendVect.size();

	std::vector<int>::iterator i = jacobsthalSequenceVect.begin();

	while (i != jacobsthalSequenceVect.end())
	{
		num = *i;
		while (num > prev_num)
		{
			sortSequenceVect.push_back(num);
			num--;
		}
		prev_num = *i;
		i++;
	}
	num = jacobsthalSequenceVect.back();
	num++;
	while (num <= size)
	{
		sortSequenceVect.push_back(num);
		num++;
	}
}

void PmergeMe::insertPendVect(std::vector<int> &mainChainVect, std::vector<int> &pendVect, std::vector<int> &sortSequenceVect)
{
	std::vector<int>::iterator s = sortSequenceVect.begin();
	int insert_num;
	int pos;
	int end_pos;
	int i = 0;

	if (pendVect.size() > 1)
	{
		while (s != sortSequenceVect.end())
		{
			insert_num = pendVect[*s - 1];
			end_pos = *s + i;
			pos = this->findPosVect(mainChainVect, insert_num, 0, end_pos);
			mainChainVect.insert(mainChainVect.begin() + pos, insert_num);
			i++;
			s++;
		}
	}

	if (this->_isOdd == true)
	{
		pos = this->findPosVect(mainChainVect, _lastOdd, 0, mainChainVect.size() - 1);
		mainChainVect.insert(mainChainVect.begin() + pos, _lastOdd);
	}
	_sortedVect = mainChainVect;
}

int PmergeMe::findPosVect(std::vector<int> &mainChainVect, int insert_num, int begin, int end)
{
	int middle;

	while (begin <= end)
	{
		middle = begin + (end - begin) / 2;

		if (insert_num > mainChainVect[middle])
			begin = middle + 1;
		else
			end = middle - 1;
	}
	if (insert_num > mainChainVect[middle])
		return (middle + 1);
	else
		return (middle);
}

// --------------------------------------------------------------------------------------------------------

// Helper functions: --------------------------------------------------------------------------------------

void PmergeMe::swapPairs(std::pair<int, int> &from, std::pair<int, int> &to)
{
	std::pair<int, int> newPair1;
	std::swap (newPair1, from);
	std::swap (to, newPair1);
}

int PmergeMe::jacobsthal(int n)
{
	if (n == 0)
		return (0);
	if (n == 1)
		return (1);
	return (jacobsthal(n - 1) + 2 * jacobsthal(n - 2));
}

// Send error message:
void PmergeMe::error(const std::string comment)
{
	std::cout << RED << "Error: " << comment << RES << std::endl;
}

// Only for printing and testing: -------------------------------------------------------------------------

// Print before / after:
template <typename T>
void PmergeMe::printNumbers(T &lst)
{
	for (typename T::iterator it = lst.begin(); it != lst.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

//Print pairs:
template <typename T>
void PmergeMe::printPairs(const T &pairList) const
{
	typename T::const_iterator it = pairList.begin();
	typename T::const_iterator ite = pairList.end();
	while(it != ite)
	{
		std::cout << "(" << (*it).first << " " << (*it).second << ")" << " ";
		it++;
	}
	std::cout << std::endl;
}
