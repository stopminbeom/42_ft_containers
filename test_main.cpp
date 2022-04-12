#include <iostream>
#include <chrono>
#include "test_funcs.hpp"
#ifndef TYPE
#define TYPE    2
#endif
#if TYPE == 2
#define TYPE_NAMESPACE ft
#elif TYPE == 1
#define TYPE_NAMESPACE std
#endif

int main(void)
{
    std::chrono::system_clock::time_point	start = std::chrono::system_clock::now();
    #if TYPE == 1
        std::cout << ">>this test is STL<<\n\n";
    #elif TYPE == 2
        std::cout << ">>this test is my containers<<\n\n";
    #endif
    std::cout << "===== test vector =====\n\n";
    vector_test();
    std::cout << "\n\n===== test stack =====\n\n";
    stack_test();
    std::cout << "\n\n===== test map =====\n\n";
    map_test();
	std::cout << "\n\n===== test set =====\n\n";
    set_test();
    std::cout << "\n!!! test end\n";
    std::chrono::system_clock::time_point	end = std::chrono::system_clock::now();
	std::chrono::duration<double> diff = end - start ;
	std::cout << "duration time : " << diff.count() << std::endl;
    return (0);
}