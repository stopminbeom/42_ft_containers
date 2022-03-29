#ifndef FT_NULLPTR_HPP
# define FT_NULLPTR_HPP

namespace	ft {
	const class nullptr_t {
		public :
			template <class T>
			operator T*() const { return 0; }

			template <class C, class T>
			operator T C::*() const { return 0; }
    } ft_nullptr = {};
} // nullptr이 c++11 에서 생성되었기 때문에 새로 98 기준으로 핸들링하기 위한 용도

#endif