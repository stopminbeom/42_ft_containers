#ifndef SET_HPP
# define SET_HPP

# include "utils/tree_iterator.hpp"
# include "utils/reverse_iterator.hpp"
# include "utils/red_black_tree.hpp"
# include "utils/is_integral.hpp"
# include "utils/equal.hpp"
# include "utils/lexicographical_compare.hpp"
# include <memory>

namespace ft {
	template < class Key, class Compare = ft::less<Key>, class Allocator = std::allocator<Key> >
	class set {
	public :
		typedef	Key															key_type;
		typedef	Key															value_type;
		typedef	size_t														size_type;
		typedef	ptrdiff_t													difference_type;
		typedef	Compare														key_compare;
		typedef	Compare														value_compare;
		typedef	Allocator													allocator_type;
		typedef	value_type&													reference;
		typedef	const value_type&											const_reference;
		typedef typename	Allocator::pointer								pointer;
		typedef typename	Allocator::const_pointer						const_painter;
		typedef	typename	ft::tree_iterator<value_type, true>				iterator;
		typedef	typename	ft::tree_iterator<value_type, true>				const_iterator;
		typedef	typename	ft::reverse_iterator<iterator>					reverse_iterator;
		typedef	typename	ft::reverse_iterator<const_iterator>			const_reverse_iterator;
		typedef	typename	ft::red_black_tree<value_type, value_compare>			rbt;
		typedef typename	ft::RBTnode<value_type>							node_type;

	private :
		allocator_type	_alloc;
		value_compare	_comp;
		rbt				_tree;

	public :
		explicit set (const Compare& comp = Compare(), const Allocator& alloc = Allocator()) : _alloc(alloc), _comp(comp), _tree() {};
		template <class InputIt>
		set (InputIt first, InputIt last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0)
			: _alloc(alloc), _comp(comp), _tree() { insert(first, last); }
		set (const set& x) : _alloc(x._alloc), _comp(x._comp), _tree() { *this = x; }

		set& operator= (const set& x) {
			if (this != &x)
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

		bool	empty() const { return _tree.empty(); }
		size_type size() const { return _tree.size(); }
		size_type max_size() const { return _tree.max_size(); }

		pair<iterator,bool> insert (const value_type& val) {
			ft::pair<node_type*, bool> res = _tree.insert(val);
			return ft::make_pair(iterator(res.first), res.second);
		}
		iterator insert (iterator position, const value_type& val) {
			return iterator(_tree.insert(val, position.base()).first);
		}
		template <class InputIt>
		void insert (InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0) {
			while (first != last)
				_tree.insert(*first++);
		}
		void erase (iterator position) { _tree.erase(position.base()); }
		size_type erase (const value_type& val) { return _tree.erase(_tree.find(val)); }
    	void erase (iterator first, iterator last) {
			while (first != last)
				erase(*first++);
		}
		void swap (set& x) { _tree.swap(x._tree); }
		void clear() { _tree.clear(); }

		key_compare key_comp() const { return key_compare(); }
		value_compare value_comp() const { return value_compare(); }

		iterator find (const value_type& val) const { return iterator(_tree.find(val)); }
		size_type count (const value_type& val) const {
			if (_tree.find(val)->value != ft_nullptr)
				return 1;
			return 0;
		}
		iterator lower_bound (const value_type& val) const { return iterator(_tree.lower_bound(val)); }
		iterator upper_bound (const value_type& val) const { return iterator(_tree.upper_bound(val)); }
		pair<iterator,iterator> equal_range (const value_type& val) const { return ft::make_pair(lower_bound(val), upper_bound(val)); }

		allocator_type get_allocator() const { return allocator_type(); }
	};

	template< class Key, class Compare, class Alloc >
	bool operator==( const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs ) {
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}
	template< class Key, class Compare, class Alloc >
	bool operator!=( const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs ) {
		return !(lhs == rhs);
	}
	template< class Key, class Compare, class Alloc >
	bool operator<( const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs ) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	template< class Key, class Compare, class Alloc >
	bool operator<=( const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs ) {
		return !(lhs > rhs);
	}
	template< class Key, class Compare, class Alloc >
	bool operator>( const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs ) {
		return rhs < lhs;
	}
	template< class Key, class Compare, class Alloc >
	bool operator>=( const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs ) {
		return !(lhs < rhs);
	}

	template< class Key, class Compare, class Alloc >
	void swap( ft::set<Key,Compare,Alloc>& lhs, ft::set<Key,Compare,Alloc>& rhs ) { lhs.swap(rhs); }
}

#endif
