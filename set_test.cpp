#include <iostream>
#if TYPE == 2
	#ifndef TESTED_NAMESPACE
	#define TESTED_NAMESPACE ft
	#endif
	#include "set.hpp"
#elif TYPE == 1
	#ifndef TESTED_NAMESPACE
	#define TESTED_NAMESPACE std
	#endif
	#include <set>
#endif

template <typename T>
void	printset(TESTED_NAMESPACE::set<T>& set, bool is_const = false, bool is_rev = false) {
	std::cout << "size : " << set.size() << std::endl;
	std::cout << "max_size : " << set.max_size() << std::endl;

	if (is_const == false && is_rev == false) {
		typename	TESTED_NAMESPACE::set<T>::iterator it = set.begin();
		typename	TESTED_NAMESPACE::set<T>::iterator ite = set.end();
		if (set.empty())
			std::cout << "This set is empty" << std::endl;
		else {
			std::cout << "Content is:" << std::endl;
			for (; it != ite; ++it)
				std::cout << *it << " , ";
			std::cout << " //end\n";
			std::cout << "###############################################\n" << std::endl;
		}
	}
	else if (is_const == false && is_rev == true) {
		typename	TESTED_NAMESPACE::set<T>::reverse_iterator it = set.rbegin();
		typename	TESTED_NAMESPACE::set<T>::reverse_iterator ite = set.rend();
		if (set.empty())
			std::cout << "This set is empty" << std::endl;
		else {
			std::cout << "Content is:" << std::endl;
			for (; it != ite; ++it)
				std::cout << *it << " , ";
			std::cout << " //end\n";
			std::cout << "###############################################\n" << std::endl;
		}
	}
	else if (is_const == true && is_rev == false) {
		typename	TESTED_NAMESPACE::set<T>::const_iterator it = set.begin();
		typename	TESTED_NAMESPACE::set<T>::const_iterator ite = set.end();
		if (set.empty())
			std::cout << "This set is empty" << std::endl;
		else {
			std::cout << "Content is:" << std::endl;
			for (; it != ite; ++it)
				std::cout << *it << " , ";
			std::cout << " //end\n";
			std::cout << "###############################################\n" << std::endl;
		}
	}
	else {
		typename	TESTED_NAMESPACE::set<T>::const_reverse_iterator it = set.rbegin();
		typename	TESTED_NAMESPACE::set<T>::const_reverse_iterator ite = set.rend();
		if (set.empty())
			std::cout << "This set is empty" << std::endl;
		else {
			std::cout << "Content is:" << std::endl;
			for (; it != ite; ++it)
				std::cout << *it << " , ";
			std::cout << " //end\n";
			std::cout << "###############################################\n" << std::endl;
		}
	}
}

void	set_test() {
	TESTED_NAMESPACE::set<int>	test;
	printset(test);

	std::cout << "insert test case 1" << std::endl;
	for (int i = 0; i < 10; i++) {
		test.insert(i);
	}
	printset(test);

	std::cout << ">>>>>> iterator test" <<std::endl;
	std::cout << "iterator" <<std::endl;
	printset(test, false, false);
	std::cout << "const iterator" <<std::endl;
	printset(test, true, false);
	std::cout << "reverse iterator" <<std::endl;
	printset(test, false, true);
	std::cout << "const reverse iterator" <<std::endl;
	printset(test, true, true);

	TESTED_NAMESPACE::set<int>	test2;
	std::cout << "insert test case 2" << std::endl;
	TESTED_NAMESPACE::set<int>::iterator it = test.begin();
	TESTED_NAMESPACE::set<int>::iterator ite = test.end();
	for (int i = 0; i < 5; i++)
		it++;
	for (int i = 0; i < 10; i++) {
		test2.insert(it, ite);
	}
	printset(test2);

	std::cout << "erase test case 1" << std::endl;
	TESTED_NAMESPACE::set<int>::iterator it1 = test.begin();
	test.erase(it1);
	printset(test);

	std::cout << "erase test case 2" << std::endl;
	TESTED_NAMESPACE::set<int>::iterator it2 = test.begin();
	TESTED_NAMESPACE::set<int>::iterator ite2 = test.end();
	for (int i = 0; i < 2; i++)
		it2++;
	test.erase(it2, ite2);
	printset(test);

	std::cout << "erase test case 3" << std::endl;
	test.erase(7);
	printset(test);

	std::cout << "erase test case 4 (error case)" << std::endl;
	test.erase(7);
	printset(test);

	std::cout << "swap test" << std::endl;
	test.swap(test2);
	std::cout << "print origin" << std::endl;
	printset(test);
	std::cout << "print swap" << std::endl;
	printset(test2);

	std::cout << "clear test" << std::endl;
	test2.clear();
	printset(test2);

	std::cout << "test operator '='" << std::endl;
	TESTED_NAMESPACE::set<int>	test3 = test;
	printset(test3);

	std::cout << ">>>>> test lower_bound, upper_bound, equal_range" << std::endl;
	std::cout << "lower_bound : " << *test.lower_bound(7) << std::endl;
	std::cout << "upper_bound : " << *test.upper_bound(7) << std::endl;
	std::cout << "equal_range : " << *test.equal_range(7).first << std::endl;

	std::cout << ">>>>> test find" << std::endl;
	if (*(test.find(7)))
		std::cout << "This element is here" << std::endl;
	else
		std::cout << "Error!" << std::endl;
	std::cout << std::endl;

	std::cout << "test relational operators" << std::endl;
	std::cout << "origin";
	if (test == test3)
		std::cout << " == " << std::endl;
	if (test < test3)
		std::cout << " < " << std::endl;
	if (test > test3)
		std::cout << " > " << std::endl;
	if (test >= test3)
		std::cout << " >= " << std::endl;
	if (test <= test3)
		std::cout << " <= " << std::endl;
	if (test != test3)
		std::cout << " != " << std::endl;
	std::cout << "copy one" << std::endl;
}