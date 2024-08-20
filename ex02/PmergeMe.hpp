/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ole <ole@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:32:54 by ole               #+#    #+#             */
/*   Updated: 2024/08/20 11:32:55 by ole              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <algorithm>
#include <string>
#include <list>
#include <vector>
#include <ctime>
#include <utility>
#include <iterator>

#define RED "\033[0;38;5;9m"
#define GRN "\033[0;38;5;2m"
#define BLU "\033[0;38;5;14m"
#define YEL "\033[0;38;5;11m"
#define RES "\e[0m"

class PmergeMe
{
private:
	std::list<int>		_unsortedList;
	std::list<int>		_sortedList;
	std::vector<int>	_unsortedVect;
	std::vector<int>	_sortedVect;
	bool				_isOdd;
	int 				_lastOdd;
public:
	PmergeMe();
	~PmergeMe();
	PmergeMe(PmergeMe const & copy);
	PmergeMe & operator= (PmergeMe const & copy);

	void sort(int ac, char **av);
	int	checkInput(int ac, char **av);
	int	convertNumbers(int ac, char **av);
	void error(const std::string comment);
	void swapPairs(std::pair<int, int> &from, std::pair<int, int> &to);
	int jacobsthal(int n);

	void sortList();
	std::list< std::pair<int, int> > createPairsList(void);
	void sortNumPairsList(std::list<std::pair<int, int> > &pairList);
	void recursiveMergeSortList(std::list<std::pair<int, int> > &pairList, int left, int right);
	void mergeList(std::list<std::pair<int, int> > &pairList, int left, int middle, int right);
	void mainChainList(std::list<int> &mainChainList, std::list<std::pair<int, int> > &pairList);
	void pendList(std::list<int> &pendList, std::list<std::pair<int, int> > &pairList);
	void generateJacobsthalList(std::list<int> &jacobsthalSequenceList, std::list<int> &pendList);
	void createSortSequenceList(std::list<int> &sortSequenceList, std::list<int> &jacobsthalSequenceList, std::list<int> &pendList);
	void insertPendList(std::list<int> &mainChainList, std::list<int> &pendList, std::list<int> &sortSequenceList);
	int  findPosList(std::list<int> &mainChainList, int insert_num, int begin, int end);

	void sortVector();
	std::vector< std::pair<int, int> > createPairsVect(void);
	void sortNumPairsVect(std::vector<std::pair<int, int> > &pairVect);
	void recursiveMergeSortVect(std::vector<std::pair<int, int> > &pairVect, int left, int right);
	void mergeVect(std::vector<std::pair<int, int> > &pairVect, int left, int middle, int right);
	void mainChainVect(std::vector<int> &mainChainVect, std::vector<std::pair<int, int> > &pairVect);
	void pendVect(std::vector<int> &pendVect, std::vector<std::pair<int, int> > &pairVect);
	void generateJacobsthalVect(std::vector<int> &jacobsthalSequenceVect, std::vector<int> &pendVect);
	void createSortSequenceVect(std::vector<int> &sortSequenceVect, std::vector<int> &jacobsthalSequenceVect, std::vector<int> &pendVect);
	void insertPendVect(std::vector<int> &mainChainVect, std::vector<int> &pendVect, std::vector<int> &sortSequenceVect);
	int  findPosVect(std::vector<int> &mainChainVect, int insert_num, int begin, int end);

	// Only for printing and testing:
	template <typename T>
	void printNumbers(T &lst);

	template <typename T>
	void printPairs(const T &pairList) const;
//	void printNumbers(std::list<int> &lst);
//	void printPairs(const std::list<std::pair<int, int> > &pairList) const;

};
