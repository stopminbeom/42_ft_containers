#ifndef TREE_ITERATOR_HPP
# define TREE_ITERATOR_HPP

# include "RBTnode.hpp"
# include "iterator_traits.hpp"
# include "pair.hpp"

namespace ft {
	template < typename T, class Compare > // 트리에서 사용되는 노드 그 자체를 들고 옴
	class tree_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T> {
		public :
			typedef T::value_type																		value_type; // Node의 value_type = pair
			typedef typename	ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category		iterator_category;
			typedef typename	ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type		difference_type;
			typedef typename	ft::iterator<ft::bidirectional_iterator_tag, T>::pointer				pointer; // pair의 포인터
			typedef typename	ft::iterator<ft::bidirectional_iterator_tag, T>::reference				reference; // pair의 참조자

		protected :
			T*		_node;
			T*		_last;
			Compare	_comp;

		public :
			tree_iterator( const Compare& comp = Compare() ) : _node(), _last(), _comp(comp) {}
			tree_iterator( T* node_ptr, T* last_ptr, const Compare& comp = Compare() ) : _node(node_ptr), _last(last_ptr), _comp(comp) {}
			tree_iterator( const tree_iterator& other ) : _node(other._node), _last(other._last), _comp(other._comp) {}
			virtual	~tree_iterator() {}

			tree_iterator & operator= ( const tree_iterator& other ) {
				if (*this != other)
					this->_node = other._node;
					this->_last = other._last;
					this->_comp = other._comp;
				return *this;
			}

			reference	operator*() const {
				return *_node->value;
			}

			pointer		operator->() const {
				return &_node->value;
			}

			tree_iterator&	operator++() {
				T* tmp = _node;
				if (_node->r_child == _last) {
					tmp = _node->parent;
					while (tmp != _last && _comp(tmp->value.first, _node->value.first))
						tmp = tmp->parent;
					_node = tmp;
				}
				else if (tmp == _last)
					_node = _last->r_child;
				else {
					tmp = _node->r_child;
					if (tmp == _last->parent && tmp->r_child == _last)
						_node = tmp;
					else {
						while (tmp->l_child != _last)
							tmp = tmp->l_child;
					}
					_node = tmp;
				}
				return *this;
			}
			tree_iterator&	operator++(int) { tree_iterator tmp = *this; ++(*this); return tmp; }

			tree_iterator&	operator--() {
				T* tmp = _node;
				if (_node->l_child == _last) {
					tmp = _node->parent;
					while (tmp != _last && _comp(tmp->value.first, _node->value.first))
						tmp = tmp->parent;
					_node = tmp;
				}
				else if (tmp == _last)
					_node = _last->r_child;
				else {
					tmp = _node->l_child;
					if (tmp == _last->parent && tmp->l_child == _last)
						_node = tmp;
					else {
						while (tmp->r_child != _last)
							tmp = tmp->r_child;
					}
					_node = tmp;
				}
				return *this;
			}
			tree_iterator&	operator--(int) { tree_iterator tmp = *this; --(*this); return tmp; }

			bool	operator==( const tree_iterator& Iter ) { return _node == Iter._node; };
			bool	operator!=( const tree_iterator& Iter ) { return _node != Iter._node; };
	};

	template < typename T, class Compare > // 트리에서 사용되는 노드 그 자체를 들고 옴
	class const_tree_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T> {
		public :
			typedef T::value_type																		value_type; // Node의 value_type = pair
			typedef typename	ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category		iterator_category;
			typedef typename	ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type		difference_type;
			typedef typename	ft::iterator<ft::bidirectional_iterator_tag, T>::pointer				pointer; // pair의 포인터
			typedef typename	ft::iterator<ft::bidirectional_iterator_tag, T>::reference				reference; // pair의 참조자

		protected :
			T*		_node;
			T*		_last;
			Compare	_comp;

		public :
			const_tree_iterator( const Compare& comp = Compare() ) : _node(), _last(), _comp(comp) {}
			const_tree_iterator( T* node_ptr, T* last_ptr, const Compare& comp = Compare() ) : _node(node_ptr), _last(last_ptr), _comp(comp) {}
			const_tree_iterator( const const_tree_iterator& other ) : _node(other._node), _last(other._last), _comp(other._comp) {}
			virtual	~const_tree_iterator() {}

			const_tree_iterator & operator= ( const const_tree_iterator& other ) {
				if (*this != other)
					this->_node = other._node;
					this->_last = other._last;
					this->_comp = other._comp;
				return *this;
			}

			reference	operator*() const {
				return *_node->value;
			}

			pointer		operator->() const {
				return &_node->value;
			}

			const_tree_iterator&	operator++() {
				T* tmp = _node;
				if (_node->r_child == _last) {
					tmp = _node->parent;
					while (tmp != _last && _comp(tmp->value.first, _node->value.first))
						tmp = tmp->parent;
					_node = tmp;
				}
				else if (tmp == _last)
					_node = _last->r_child;
				else {
					tmp = _node->r_child;
					if (tmp == _last->parent && tmp->r_child == _last)
						_node = tmp;
					else {
						while (tmp->l_child != _last)
							tmp = tmp->l_child;
					}
					_node = tmp;
				}
				return *this;
			}
			const_tree_iterator&	operator++(int) { const_tree_iterator tmp = *this; ++(*this); return tmp; }

			const_tree_iterator&	operator--() {
				T* tmp = _node;
				if (_node->l_child == _last) {
					tmp = _node->parent;
					while (tmp != _last && _comp(tmp->value.first, _node->value.first))
						tmp = tmp->parent;
					_node = tmp;
				}
				else if (tmp == _last)
					_node = _last->r_child;
				else {
					tmp = _node->l_child;
					if (tmp == _last->parent && tmp->l_child == _last)
						_node = tmp;
					else {
						while (tmp->r_child != _last)
							tmp = tmp->r_child;
					}
					_node = tmp;
				}
				return *this;
			}
			const_tree_iterator&	operator--(int) { const_tree_iterator tmp = *this; --(*this); return tmp; }

			bool	operator==( const const_tree_iterator& Iter ) { return _node == Iter._node; };
			bool	operator!=( const const_tree_iterator& Iter ) { return _node != Iter._node; };
	};
}

#endif
