#ifndef TREE_ITERATOR_HPP
# define TREE_ITERATOR_HPP

# include "RBTnode.hpp"
# include "iterator_traits.hpp"
# include "pair.hpp"

namespace ft {
	template < typename Node, bool B > // 말 그대로 노드 value_type으로 pair를 들고옴. 트리에서 사용되는 노드 그 자체
	class tree_iterator : public ft::iterator<ft::bidirectional_iterator_tag, Node> {
		public :
			typedef Node																					value_type; // pair
			typedef typename	ft::iterator<ft::bidirectional_iterator_tag, Node>::iterator_category		iterator_category;
			typedef typename	ft::iterator<ft::bidirectional_iterator_tag, Node>::difference_type			difference_type;
			typedef typename	ft::iterator<ft::bidirectional_iterator_tag, Node>::pointer					pointer; // pair의 포인터
			typedef typename	ft::iterator<ft::bidirectional_iterator_tag, Node>::reference				reference; // pair의 참조자
			typedef	ft::RBTnode<Node>																		node_type;

		protected :
			node_type*	_node;

		public :
			tree_iterator() : _node() {}
			tree_iterator( node_type* node_ptr = ft_nullptr ) : _node(node_ptr) {}
			virtual	~tree_iterator() {}

			tree_iterator & operator= ( const tree_iterator& other ) {
				if (*this != other)
					this->_node = other.base();
				return *this;
			}

			node_type*	base() const {
				return _node;
			}

			reference	operator*() const {
				return *_node->value;
			}

			pointer		operator->() const {
				return _node->value;
			}

			tree_iterator&	operator++() {
				node_type* tmp = ft_nullptr;
				if (_node->r_child->value != ft_nullptr) {
					tmp = _node->r_child;
					while (tmp->l_child->value != ft_nullptr)
						tmp = tmp->l_child;
				}
				else {
					tmp = _node->parent;
					if (tmp->r_child == _node) {
						while (tmp->parent->r_child == tmp)
							tmp = tmp->parent;
						tmp = tmp->parent;
					}
				}
				_node = tmp;
				return *this;
			}
			tree_iterator&	operator++(int) { tree_iterator tmp = *this; ++(*this); return tmp; }

			tree_iterator&	operator--() {
				node_type* tmp = ft_nullptr;
				if (_node->value == ft_nullptr)
					tmp = _node->parent;
				else if (_node->l_child->value != ft_nullptr) {
					tmp = _node->l_child;
					while (tmp->r_child->value != ft_nullptr)
						tmp = tmp->r_chlid;
				}
				else {
					tmp = _node->parent;
					if (tmp->l_child == this->_node)
						while (tmp->parent->l_child == tmp)
							tmp = tmp->parent;
						tmp = tmp->parent;
				}
				_node = tmp;
				return *this;
			}
			tree_iterator&	operator--(int) { tree_iterator tmp = *this; --(*this); return tmp; }

			bool	operator==(const tree_iterator&	Iter) { return _node == Iter.base(); };
			bool	operator!=(const tree_iterator& Iter) { return _node != Iter.base(); };
	};
}

#endif
