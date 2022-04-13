#include <iostream>
#if TYPE == 2
	#ifndef TESTED_NAMESPACE
	#define TESTED_NAMESPACE ft
	#endif
	#include "map.hpp"
#elif TYPE == 1
	#ifndef TESTED_NAMESPACE
	#define TESTED_NAMESPACE std
	#endif
	#include <map>
#endif

template <typename T1, typename T2>
void	printmap(TESTED_NAMESPACE::map<T1, T2>& map, bool is_const = false, bool is_rev = false) {
	std::cout << "size : " << map.size() << std::endl;
	std::cout << "max_size : " << map.max_size() << std::endl;

	if (is_const == false && is_rev == false) {
		typename	TESTED_NAMESPACE::map<T1, T2>::iterator it = map.begin();
		typename	TESTED_NAMESPACE::map<T1, T2>::iterator ite = map.end();
		if (map.empty())
			std::cout << "This map is empty" << std::endl;
		else {
			std::cout << "Content is:" << std::endl;
			for (; it != ite; ++it)
				std::cout << it->first << " , ";
			std::cout << " //end\n";
			std::cout << "###############################################\n" << std::endl;
		}
	}
	else if (is_const == false && is_rev == true) {
		typename	TESTED_NAMESPACE::map<T1, T2>::reverse_iterator it = map.rbegin();
		typename	TESTED_NAMESPACE::map<T1, T2>::reverse_iterator ite = map.rend();
		if (map.empty())
			std::cout << "This map is empty" << std::endl;
		else {
			std::cout << "Content is:" << std::endl;
			for (; it != ite; ++it)
				std::cout << it->first << " , ";
			std::cout << " //end\n";
			std::cout << "###############################################\n" << std::endl;
		}
	}
	else if (is_const == true && is_rev == false) {
		typename	TESTED_NAMESPACE::map<T1, T2>::const_iterator it = map.begin();
		typename	TESTED_NAMESPACE::map<T1, T2>::const_iterator ite = map.end();
		if (map.empty())
			std::cout << "This map is empty" << std::endl;
		else {
			std::cout << "Content is:" << std::endl;
			for (; it != ite; ++it)
				std::cout << it->first << " , ";
			std::cout << " //end\n";
			std::cout << "###############################################\n" << std::endl;
		}
	}
	else {
		typename	TESTED_NAMESPACE::map<T1, T2>::const_reverse_iterator it = map.rbegin();
		typename	TESTED_NAMESPACE::map<T1, T2>::const_reverse_iterator ite = map.rend();
		if (map.empty())
			std::cout << "This map is empty" << std::endl;
		else {
			std::cout << "Content is:" << std::endl;
			for (; it != ite; ++it)
				std::cout << it->first << " , ";
			std::cout << " //end\n";
			std::cout << "###############################################\n" << std::endl;
		}
	}
}

void	map_test() {
	std::cout << ">>>>>> start test" << std::endl;
	TESTED_NAMESPACE::map<int, std::string>	test;
	printmap(test);
	
	// std::string	test_arr[] = {
	// 	"hello",
	// 	"world",
	// 	"42",
	// 	"test",
	// 	"container",
	// 	"vector",
	// 	"stack",
	// 	"map",
	// 	"set",
	// 	"end"
	// };

	// for (int i = 1; i < 11; i++)
	// 	test.insert(TESTED_NAMESPACE::pair<int, std::string>(i, test_arr[i - 1]));
	// printmap(test);

	// std::cout << ">>>>>> iterator test" <<std::endl;
	// std::cout << "iterator" <<std::endl;
	// printmap(test, false, false);
	// std::cout << "const iterator" <<std::endl;
	// printmap(test, true, false);
	// std::cout << "reverse iterator" <<std::endl;
	// printmap(test, false, true);
	// std::cout << "const reverse iterator" <<std::endl;
	// printmap(test, true, true);

	// std::cout << ">>>>> constructor test case 1" <<std::endl;
	// TESTED_NAMESPACE::map<int, std::string>	case1(test.begin(), test.end());
	// printmap(case1);
	// std::cout << ">>>>> constructor test case 2" <<std::endl;
	// TESTED_NAMESPACE::map<int, std::string>	case2(test);
	// printmap(case2);
	// std::cout << ">>>>> operator '=' test" <<std::endl;
	// TESTED_NAMESPACE::map<int, std::string>	case3 = test;
	// printmap(case3);
	// std::cout << std::endl;
	
	// std::cout << ">>>>> Find elements to at" << std::endl;
	// std::cout << "key = 3, value is " << test.at(3) << std::endl;
	// std::cout << ">>>>> Find elements to operator []" << std::endl;
	// std::cout << "key = 3, value is " << test[3] << std::endl;
	// std::cout << std::endl;

	// std::cout << ">>>>> erase test" << std::endl;
	// TESTED_NAMESPACE::map<int, std::string>::iterator it = test.begin();
	// test.erase(it);
	// std::cout << ">>>>> check deep copy" << std::endl;
	// printmap(test);
	// printmap(case1);
	// printmap(case2);
	// printmap(case3);

	// std::cout << ">>>>> erase test case 2" << std::endl;
	// TESTED_NAMESPACE::map<int, std::string>::iterator it1 = test.begin();
	// TESTED_NAMESPACE::map<int, std::string>::iterator ite1 = test.end();
	// for (int i = 0; i < 6; i++)
	// 	it1++;
	// test.erase(it1, ite1);
	// printmap(test);

	// std::cout << ">>>>> swap test" << std::endl;
	// test.swap(case1);
	// std::cout << ">>>>> test print" << std::endl;
	// printmap(test);
	// std::cout << ">>>>> case1 print" << std::endl;
	// printmap(case1);

	// std::cout << ">>>>> test lower_bound, upper_bound, equal_range" << std::endl;
	// std::cout << "lower_bound : " << test.lower_bound(5)->first << std::endl;
	// std::cout << "upper_bound : " << test.upper_bound(5)->first << std::endl;
	// std::cout << "equal_range : " << test.equal_range(5).first->first << std::endl;

	// std::cout << ">>>>> test count" << std::endl;
	// if (test.count(3))
	// 	std::cout << "I have this key" << std::endl;
	// else
	// 	std::cout << "I don't have this key" << std::endl;
	// std::cout << ">>>>> test error count" << std::endl;
	// if (test.count(99))
	// 	std::cout << "I have this key" << std::endl;
	// else
	// 	std::cout << "I don't have this key" << std::endl;
	// std::cout << std::endl;
	
	// std::cout << ">>>>> test find" << std::endl;
	// std::cout << "This map's 5th element key is " << test.find(4)->first << ", end value is " << test.find(4)->second << std::endl;

	// std::cout << ">>>>> test find error case" << std::endl;
	// if (test.find(99) == test.end())
	// 	std::cout << "Test success" << std::endl;
	// else
	// 	std::cout << "Error !" << std::endl;
	// std::cout << std::endl;

	// std::cout << "test relational operators" << std::endl;
	// std::cout << "origin";
	// if (test == case2)
	// 	std::cout << " == " << std::endl;
	// if (test < case2)
	// 	std::cout << " < " << std::endl;
	// if (test > case2)
	// 	std::cout << " > " << std::endl;
	// if (test >= case2)
	// 	std::cout << " >= " << std::endl;
	// if (test <= case2)
	// 	std::cout << " <= " << std::endl;
	// if (test != case2)
	// 	std::cout << " != " << std::endl;
	// std::cout << "case2 one" << std::endl;
}