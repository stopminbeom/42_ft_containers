#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP

namespace ft {
	template <class T, bool v>
	struct integral_constant {
		static const bool value = v;
		typedef T value_type;
	};

	template <class T> struct is_integral_type : public ft::integral_constant<T, false> {};
	template <> struct is_integral_type <bool> : public ft::integral_constant<bool, true> {};
	template <> struct is_integral_type <char> : public ft::integral_constant<char, true> {};
	template <> struct is_integral_type <char16_t> : public ft::integral_constant<char16_t, true> {};
	template <> struct is_integral_type <char32_t> : public ft::integral_constant<char32_t, true> {};
	template <> struct is_integral_type <wchar_t> : public ft::integral_constant<wchar_t, true> {};
	template <> struct is_integral_type <short> : public ft::integral_constant<short, true> {};
	template <> struct is_integral_type <int> : public ft::integral_constant<int, true> {};
	template <> struct is_integral_type <long> : public ft::integral_constant<long, true> {};
	template <> struct is_integral_type <long long> : public ft::integral_constant<long long, true> {};
	template <> struct is_integral_type <unsigned char> : public ft::integral_constant<unsigned char, true> {};
	template <> struct is_integral_type <unsigned int> : public ft::integral_constant<unsigned int, true> {};
	template <> struct is_integral_type <unsigned short> : public ft::integral_constant<unsigned short, true> {};
	template <> struct is_integral_type <unsigned long> : public ft::integral_constant<unsigned long, true> {};
	template <> struct is_integral_type <unsigned long long> : public ft::integral_constant<unsigned long long, true> {};

	template <typename T>
		struct is_integral : public is_integral_type<T> {};	
}

#endif
