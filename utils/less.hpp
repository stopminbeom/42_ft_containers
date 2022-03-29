#ifndef LESS_HPP
# define LESS_HPP

namespace ft {
	template < class Arg1, class Arg2, class Result>
	struct binary_function {
		typedef	Arg1	first_argument_type;
		typedef	Arg2	second_argument_type;
		typedef	Result	result_type;
	};
	
	template< class T >
	struct less : binary_function <T, T, bool> {
		public :
			bool operator()( const T& lhs, const T& rhs ) const { return lhs < rhs; }
	};
}

#endif
