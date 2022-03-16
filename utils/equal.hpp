#ifndef EQUAL_HPP
# define EQUAL_HPP
/* 두 원소의 나열들이 같은 지 확인함. <algorithm>에 정의되어있음 */ 
namespace	ft {
	template<class InputIt1, class InputIt2>
	bool equal (InputIt1 first1, InputIt1 last1, 
				InputIt2 first2) {
		for (; first1 != last1; ++first1, ++first2) {
			if (!(*first1 == *first2)) { return false; }
		}
		return true;
	}

	template<class InputIt1, class InputIt2, class BinaryPredicate>
	bool equal (InputIt1 first1, InputIt1 last1, 
				InputIt2 first2, BinaryPredicate p) {
		for (; first1 != last1; ++first1, ++first2) {
			if (!p(*first1, *first2)) { return false; }
		}
		return true;
	}
}

#endif
