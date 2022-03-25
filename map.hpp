#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include "utils/pair.hpp"
# include "utils/less.hpp"
# include "utils/reverse_iterator.hpp"
# include "utils/tree_iterator.hpp"

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
			typedef	ft::tree_iterator<T>					iterator;
			typedef	ft::tree_iterator<const T>				const_iterator;
			typedef	ft::reverse_iterator<T>					reverse_iterator;
			typedef	ft::reverse_iterator<const T>			const_reverse_iterator;

		class value_compare : ft::binary_function<value_type, value_type, bool> {
			protected :
				Compare comp;
				value_compare(Compare c) : comp(c) {}
			public :
				typedef	bool		result_type;
				typedef	value_type	first_argument_type;
				typedef	value_type	second_argument_type;
				bool operator()( const value_type& lhs, const value_type& rhs ) const { return comp(lhs.first, rhs.first); }
		};

		private :
			allocator_type	_alloc;
			key_compare		_comp;
			RBT				_tree;
		
		public :
			explicit map( const Compare& comp, const Allocator& alloc = Allocator() ) : _alloc(alloc), _comp(comp) {}
			template< class InputIt >
				map( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()
				typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0 ) : _alloc(alloc), _comp(comp) { insert(first, last); }
			map( const map& other ) : _alloc(other._alloc), _comp(other._comp) { 
				value_compare.comp()
			}
	};
}

#endif
