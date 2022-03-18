#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP

# include <stdint.h>

namespace ft {
	template <bool v, class T>
	struct integral_constant {
		static const bool value = v;
		typedef T value_type;
	};

	template <class T> struct is_integral_type : public ft::integral_constant<false, T> {};
	template <> struct is_integral_type <bool> : public ft::integral_constant<true, bool> {};
	template <> struct is_integral_type <char> : public ft::integral_constant<true, char> {};
	template <> struct is_integral_type <char16_t> : public ft::integral_constant<true, char16_t> {};
	template <> struct is_integral_type <char32_t> : public ft::integral_constant<true, char32_t> {};
	template <> struct is_integral_type <wchar_t> : public ft::integral_constant<true, wchar_t> {};
	template <> struct is_integral_type <short> : public ft::integral_constant<true, short> {};
	template <> struct is_integral_type <int> : public ft::integral_constant<true, int> {};
	template <> struct is_integral_type <long> : public ft::integral_constant<true, long> {};
	template <> struct is_integral_type <long long> : public ft::integral_constant<true, long long> {};
	template <> struct is_integral_type <unsigned char> : public ft::integral_constant<true, unsigned char> {};
	template <> struct is_integral_type <unsigned int> : public ft::integral_constant<true, unsigned int> {};
	template <> struct is_integral_type <unsigned short> : public ft::integral_constant<true, unsigned short> {};
	template <> struct is_integral_type <unsigned long> : public ft::integral_constant<true, unsigned long> {};
	template <> struct is_integral_type <unsigned long long> : public ft::integral_constant<true, unsigned long long> {};

	template <typename T>
		struct is_integral : public is_integral_type<T> {};	
}

#endif
