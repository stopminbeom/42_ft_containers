#include <iostream>
#if TYPE == 2
	#ifndef TESTED_NAMESPACE
	#define TESTED_NAMESPACE ft
	#endif
	#include "../vector.hpp"
#elif TYPE == 1
	#ifndef TESTED_NAMESPACE
	#define TESTED_NAMESPACE std
	#endif
	#include <vector>
#endif

template <typename T>
void	printvector(TESTED_NAMESPACE::vector<T>& vec, bool is_const = false, bool is_rev = false) {
	std::cout << "size : " << vec.size() << std::endl;
	std::cout << "capacity : " << vec.capacity() << std::endl;
	std::cout << "max_size : " << vec.max_size() << std::endl;

	if (is_const == false && is_rev == false) {
		typename	TESTED_NAMESPACE::vector<T>::iterator it = vec.begin();
		typename	TESTED_NAMESPACE::vector<T>::iterator ite = vec.end();
		std::cout << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << *it << " , ";
		std::cout << " //end\n";
		std::cout << "###############################################\n" << std::endl;
	}
	else if (is_const == false && is_rev == true) {
		typename	TESTED_NAMESPACE::vector<T>::reverse_iterator it = vec.rbegin();
		typename	TESTED_NAMESPACE::vector<T>::reverse_iterator ite = vec.rend();
		std::cout << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << *it << " , ";
		std::cout << " //end\n";
		std::cout << "###############################################\n" << std::endl;
	}
	else if (is_const == true && is_rev == false) {
		typename	TESTED_NAMESPACE::vector<T>::const_iterator it = vec.begin();
		typename	TESTED_NAMESPACE::vector<T>::const_iterator ite = vec.end();
		std::cout << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << *it << " , ";
		std::cout << " //end\n";
		std::cout << "###############################################\n" << std::endl;
	}
	else {
		typename	TESTED_NAMESPACE::vector<T>::const_reverse_iterator it = vec.rbegin();
		typename	TESTED_NAMESPACE::vector<T>::const_reverse_iterator ite = vec.rend();
		std::cout << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << *it << " , ";
		std::cout << " //end\n";
		std::cout << "###############################################\n" << std::endl;
	}
}

template <typename T>
void	is_empty(TESTED_NAMESPACE::vector<T>& vec) {
	if (vec.empty())
		std::cout << "This vector is empty" << std::endl;
	else
		std::cout << "This vector is not empty" << std::endl;
	std::cout << "-------------------" << std::endl;
}

void	vector_test() {
	TESTED_NAMESPACE::vector<int>	test;

	printvector(test);
	is_empty(test);

	for (int i = 0; i < 10; i++) {
		test.push_back(i);
	}
	printvector(test);

	std::cout << "Test vector empty" << std::endl;
	is_empty(test);

	std::cout << "Test vector reverse_iterator" << std::endl;
	printvector(test, false, true);

	std::cout << ">>>>>>>>>>>>> Copy test" << std::endl;
	TESTED_NAMESPACE::vector<int>	copy = test;
	std::cout << "copy vector print" << std::endl;
	printvector(copy);

	std::cout << ">>>>>>>>>>>>> change elements test" << std::endl;
	std::cout << "vector 2nd, 5th, 8th element is " << test[1] << ", " << test.at(4) << ", " << test[6] << std::endl;
	std::cout << "change vector's 5th element " << test[4] << " to 42" << std::endl;
	test[4] = 42;

	std::cout << ">>>>>>>>>>>>> check copy and origin" << std::endl;	
	printvector(test);
	std::cout << "-----------------------\n";
	printvector(copy);

	std::cout << ">>>>>>>>>>>>> test pop_back 3 time" << std::endl;
	for (int i = 0; i < 3; i++) {
		test.pop_back();
	}
	printvector(test);

	std::cout << ">>>>>>>>>>>>> swap origin and copy" << std::endl;
	test.swap(copy);
	printvector(test);
	printvector(copy);

	std::cout << ">>>>>>>>>>>>> test assign 1" << std::endl;
	test.assign(5, 3);
	printvector(test);

	std::cout << ">>>>>>>>>>>>> test assign 2" << std::endl;
	TESTED_NAMESPACE::vector<int>::iterator it = copy.begin();
	TESTED_NAMESPACE::vector<int>::iterator ite = copy.end();
	test.assign(it, ite);
	printvector(test);

	std::cout << ">>>>>>>>>>>>> test front and back" << std::endl;
	std::cout << ">>>>>>>>>>>>> vector front is " << test.front() << " and back is " << test.back() << std::endl;

	std::cout << ">>>>>>>>>>>>> test data" << std::endl;
	std::cout << *test.data() << std::endl;

	std::cout << ">>>>>>>>>>>>> test reserve error case" << std::endl;
	test.reserve(3); // error case
	printvector(test);
	std::cout << ">>>>>>>>>>>>> test reserve not error case" << std::endl;
	test.reserve(42); // not error case
	printvector(test);

	std::cout << ">>>>>>>>>>>>> test erase case 1" << std::endl;
	TESTED_NAMESPACE::vector<int>::iterator it2 = test.begin();
	it2++;
	test.erase(it2);
	printvector(test);

	std::cout << ">>>>>>>>>>>>> test erase case 2" << std::endl;
	TESTED_NAMESPACE::vector<int>::iterator it3 = test.begin();
	TESTED_NAMESPACE::vector<int>::iterator ite2 = test.end();
	for (int i = 0; i < 3; i++) {
		it3++;
	}
	test.erase(it3, ite2);
	printvector(test);

	std::cout << ">>>>>>>>>>>>> test insert case 1" << std::endl;
	TESTED_NAMESPACE::vector<int>::iterator it4 = test.begin();
	test.insert(it4, 300);
	printvector(test);

	std::cout << ">>>>>>>>>>>>> test insert case 2" << std::endl;
	TESTED_NAMESPACE::vector<int>::iterator it5 = test.begin();
	test.insert(it5, 3, 500);
	printvector(test);

	std::cout << ">>>>>>>>>>>>> test insert case 3" << std::endl;
	TESTED_NAMESPACE::vector<int>::iterator ite3 = test.end();
	TESTED_NAMESPACE::vector<int>::iterator ite4 = copy.end();
	TESTED_NAMESPACE::vector<int>::iterator it6 = copy.begin();
	test.insert(ite3, it6, ite4);
	printvector(copy);
	printvector(test);

	std::cout << ">>>>>>>>>>>>> test resize" << std::endl;
	test.resize(5);
	printvector(test);

	
	std::cout << "test relational operators" << std::endl;
	TESTED_NAMESPACE::vector<int>	copy2(test);
	std::cout << "origin";
	if (test == copy2)
		std::cout << " == " << std::endl;
	if (test < copy2)
		std::cout << " < " << std::endl;
	if (test > copy2)
		std::cout << " > " << std::endl;
	if (test >= copy2)
		std::cout << " >= " << std::endl;
	if (test <= copy2)
		std::cout << " <= " << std::endl;
	if (test != copy2)
		std::cout << " != " << std::endl;
	std::cout << "copy one" << std::endl;

	std::cout << ">>>>>>>>>>>>> test clear" << std::endl;
	test.clear();
	printvector(test);
	std::cout << "test end" << std::endl;
}