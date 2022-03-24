#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include "./utils/pair.hpp"
# include "./utils/less.hpp"
# include "./utils/random_access_iterator.hpp"
# include "./utils/reverse_iterator.hpp"

namespace ft {
	template< class Key, class T, class Compare = ft::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map {
		public :
			typedef	Key										key_type;
			typedef	T										mapped_type;
			typedef	ft::pair<const Key, T>					value_type;
			typedef	size_t									size_type;
			typedef	ptrdiff_t								difference_type;
			typedef	Compare									key_compare;
			typedef	Allocator								allocator_type;
			typedef	value_type&								reference;
			typedef	const value_type&						const_reference;
			typedef typename	Allocator::pointer			pointer;
			typedef typename	Allocator::const_painter	const_painter;
			typedef	ft::random_access_iterator<T>			iterator;
			typedef	ft::random_access_iterator<const T>		const_iterator;
			typedef	ft::reverse_iterator<T>					reverse_iterator;
			typedef	ft::reverse_iterator<const T>			const_reverse_iterator;

		private	:
			class value_compare : ft::binary_function<value_type, value_type, bool> {
				protected :
					Compare comp;
					value_compare(Compare c) : comp(c) {}
				public :
					value_compare() : comp() {}
					bool operator()( const value_type& lhs, const value_type& rhs ) const { return comp(lhs.first, rhs.first); }
			};
		
		public :
			explicit map( const Compare& comp, const Allocator& alloc = Allocator() ) : comp(comp) {}
			template< class InputIt >
				map( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() ) {

				}
	};
}

#endif
