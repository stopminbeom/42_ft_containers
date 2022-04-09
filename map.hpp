#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include "./utils/red_black_tree.hpp"
# include "./utils/enable_if.hpp"
# include "./utils/equal.hpp"
# include "./utils/lexicographical_compare.hpp"
# include "./utils/is_integral.hpp"
# include "./utils/reverse_iterator.hpp"

namespace ft {
	template< class Key, class T, class Compare = ft::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map {
		public :
			typedef	Key													key_type;
			typedef	T													mapped_type;
			typedef	ft::pair<const Key, T>								value_type;
			typedef	size_t												size_type;
			typedef	ptrdiff_t											difference_type;
			typedef	Compare												key_compare;
			typedef	Allocator											allocator_type;
			typedef	value_type&											reference;
			typedef	const value_type&									const_reference;
			typedef typename	Allocator::pointer						pointer;
			typedef typename	Allocator::const_pointer				const_painter;
			typedef	typename	ft::tree_iterator<value_type, false>	iterator;
			typedef	typename	ft::tree_iterator<value_type, true>		const_iterator;
			typedef	typename	ft::reverse_iterator<iterator>			reverse_iterator;
			typedef	typename	ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			typedef typename	ft::red_black_tree<value_type>			rbt;
			typedef typename	ft::RBTnode<value_type>					node_type;

		class value_compare : ft::binary_function<value_type, value_type, bool> {
			protected :
				Compare comp;
				value_compare(Compare c) : comp(c) {}
			public :
				typedef	bool		result_type;
				typedef	value_type	first_argument_type;
				typedef	value_type	second_argument_type;
				value_compare() : comp() {}
				bool operator()( const value_type& lhs, const value_type& rhs ) const { return comp(lhs.first, rhs.first); }
		};

		private :
			allocator_type	_alloc;
			key_compare		_comp;
			rbt				_tree;
		
		public :
			explicit map( const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type() ) : _alloc(alloc), _comp(comp), _tree() {}
			template< class InputIt >
			map( InputIt first, InputIt last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0 )
			: _alloc(alloc), _comp(comp), _tree() { insert(first, last); }
			map( const map& other ) : _alloc(other._alloc), _comp(other._comp), _tree() { *this = other; }
			~map() {}

			map& operator= (const map& x) {
				if (*this != x)
					_tree.copy(x._tree);
				return *this;
			}

			iterator begin() { return iterator(_tree.get_begin()); }
			const_iterator begin() const { return const_iterator(_tree.get_begin()); }
			iterator end() { return iterator(_tree.get_end()); }
			const_iterator end() const { return const_iterator(_tree.get_end()); }
			reverse_iterator rbegin() { return reverse_iterator(_tree.get_end()); }
			const_reverse_iterator rbegin() const { return const_reverse_iterator(_tree.get_end()); }
			reverse_iterator rend() { return reverse_iterator(_tree.get_begin()); }
			const_reverse_iterator rend() const { return const_reverse_iterator(_tree.get_begin()); }

			bool empty() const { return _tree.empty(); }
			size_type size() const { return _tree.size(); }
			size_type max_size() const { return _tree.max_size(); }

			mapped_type& operator[] (const key_type& k) {
				return (*(_tree.insert(ft::make_pair(k, mapped_type())).first)).value->second;
			}
			
			pair<iterator, bool> insert (const value_type& val) {
				ft::pair<node_type* , bool> ret = _tree.insert(val);
				return ft::make_pair(iterator(ret.first), ret.second);
			}
			iterator insert (iterator position, const value_type& val) {
				return iterator(_tree.insert(val, position.base()).first);
			}
			template <class InputIt>
			void insert (InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0) {
				while (first != last)
					_tree.insert(*first++);
			}
			void erase (iterator position) {
				_tree.erase(position.base());
			}
			size_type erase (const key_type& k) {
				return _tree.erase(_tree.find(value_type(k, mapped_type())));
			}
    		void erase (iterator first, iterator last) {
				while (first != last)
					erase(first++);
			}
			void swap (map& x) {
				_tree.swap(x._tree);
			}
			void clear() {
				_tree.clear();
			}

			key_compare key_comp() const { return key_compare(); }
			value_compare value_comp() const { return value_compare(); }

			iterator find (const key_type& k) { return iterator(_tree.find(value_type(k, mapped_type()))); }
			const_iterator find (const key_type& k) const { return const_iterator(_tree.find(value_type(k, mapped_type()))); }
			size_type count (const key_type& k) const {
				if (_tree.find(value_type(k, mapped_type()))->value != ft_nullptr)
					return 1;
				return 0;
			}
			iterator lower_bound (const key_type& k) { return _tree.lower_bound(value_type(k, mapped_type())); }
			const_iterator lower_bound (const key_type& k) const { return _tree.lower_bound(value_type(k, mapped_type())); }
			iterator upper_bound (const key_type& k) { return _tree.upper_bound(value_type(k, mapped_type())); }
			const_iterator upper_bound (const key_type& k) const { return _tree.upper_bound(value_type(k, mapped_type())); }
			pair<iterator,iterator>             equal_range (const key_type& k) { return ft::make_pair(lower_bound(k), upper_bound(k)); }
			pair<const_iterator,const_iterator> equal_range (const key_type& k) const { return ft::make_pair(lower_bound(k), upper_bound(k)); }

			allocator_type	get_allocator() const { return _alloc; }
	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator== (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!= (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
		return !(lhs == rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator< (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<= (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
		return !(rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator> (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
		return rhs < lhs;
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>= (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
		return !(lhs < rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	void swap (map<Key, T, Compare, Alloc>& x, map<Key, T, Compare, Alloc>& y) { x.swap(y); }
}

#endif
