#include <iostream>
#if TYPE == 2
	#ifndef TESTED_NAMESPACE
	#define TESTED_NAMESPACE ft
	#endif
	#include "stack.hpp"
#elif TYPE == 1
	#ifndef TESTED_NAMESPACE
	#define TESTED_NAMESPACE std
	#endif
	#include <stack>
#endif

void	stack_test() {
	std::string	test_arr[] = {
		"hello",
		"world",
		"42",
		"seoul"
	};

	TESTED_NAMESPACE::stack<std::string>	test;

	std::cout << "stack size is " << test.size() << std::endl;
	if (test.empty())
		std::cout << "stack is empty !" << std::endl;
	else
		std::cout << "stack is not empty !" << std::endl;
	
	std::cout << "stack push test" << std::endl;
	for (int i = 0; i < 4; i++) {
		test.push(test_arr[i]);
	}
	std::cout << "Now, stack size is " << test.size() << std::endl;
	std::cout << "stack top is " << test.top() << "\n" << std::endl;

	std::cout << "stack pop test" << std::endl;
	test.pop();
	std::cout << "Now, stack top is " << test.top() << std::endl;
	std::cout << "Now, stack size is " << test.size() << "\n" << std::endl;

	std::cout << "copy test" << std::endl;
	TESTED_NAMESPACE::stack<std::string>	copy(test);
	std::cout << "copy size is " << copy.size() << std::endl;
	std::cout << "copy top is " << copy.top() << std::endl;

	std::cout << "test relational operators" << std::endl;
	std::cout << "origin";
	if (test == copy)
		std::cout << " == " << std::endl;
	if (test < copy)
		std::cout << " < " << std::endl;
	if (test > copy)
		std::cout << " > " << std::endl;
	if (test >= copy)
		std::cout << " >= " << std::endl;
	if (test <= copy)
		std::cout << " <= " << std::endl;
	if (test != copy)
		std::cout << " != " << std::endl;
	std::cout << "copy one" << std::endl;
}