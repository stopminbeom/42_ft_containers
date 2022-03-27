#ifndef TREE_ITERATOR_HPP
# define TREE_ITERATOR_HPP

# include "RBTnode.hpp"
# include "iterator_traits.hpp"
# include "pair.hpp"

namespace ft {
	template < typename Node, class Compare > // 말 그대로 노드 value_type으로 pair를 들고옴. 트리에서 사용되는 노드 그 자체
	class tree_iterator : public ft::iterator<ft::bidirectional_iterator_tag, Node> {
		public :
			typedef typename	Node::value_type															value_type; // pair
			typedef typename	ft::iterator<ft::bidirectional_iterator_tag, Node>::iterator_category		iterator_category;
			typedef typename	ft::iterator<ft::bidirectional_iterator_tag, Node>::difference_type			difference_type;
			typedef typename	ft::iterator<ft::bidirectional_iterator_tag, Node>::pointer					pointer; // pair의 포인터
			typedef typename	ft::iterator<ft::bidirectional_iterator_tag, Node>::reference				reference; // pair의 참조자

		protected :
			Node*	node_pointer; // 랜덤의 current와 유사
			Node*	last_node;
			Compare	_comp;

		public :
			tree_iterator(const Compare& comp = Compare()) : node_pointer(), last_node(), _comp(comp) {}
			tree_iterator( Node* node_ptr, Node* last, const Compare& comp = Compare() ) : node_pointer(node_ptr), last_node(last), _comp(comp) {}
			tree_iterator( const tree_iterator& other ) : node_pointer(other.base()), last_node(other.last_node), _comp() {}
			virtual	~tree_iterator() {}

			tree_iterator & operator= ( const tree_iterator& other ) {
				if (*this == other)
					return *this;
				node_pointer = other.node_pointer;
				last_node = other.last_node;
				_comp = other._comp;
				return *this;
			}

			node_type	base() const {
				return node_pointer;
			}

			reference	operator*() const {
				return node_pointer->value;
			}

			pointer		operator->() const {
				return &(node_pointer->value);
			}

			tree_iterator&	operator++() {
				Node* tmp = nullptr;
				if (node_pointer->r_child->value != nullptr) {
					tmp = node_pointer->r_child;
					while (tmp->l_child->value != nullptr)
						tmp = tmp->l_child;
				}
				else {
					tmp = node_pointer->parent
					if (tmp->r_child == this->node_pointer) {
						while (tmp->parent->r_child == tmp)
							tmp = tmp->parent;
						tmp = tmp->parent;
					}
				}
				node_pointer = tmp;
				return *this;
			}
			tree_iterator&	operator++(int) { tree_iterator tmp = *this; ++(*this); return tmp; }

			tree_iterator&	operator--() {
				Node* tmp = nullptr;
				if (node_pointer->value == nullptr)
					tmp = node_pointer->parent;
				else if (node_pointer->l_child->value != nullptr)
					tmp = node_pointer->l_child;
					while (tmp->r_child->value != nullptr)
						tmp = tmp->r_chlid;
				else {
					tmp = node_pointer->parent;
					if (tmp->l_child == this->node_pointer);
						while (tmp->parent->l_child == tmp)
							tmp = tmp->parent;
						tmp = tmp->parent;
				}
				node_pointer = tmp;
				return *this;
			}
			tree_iterator&	operator--(int) { tree_iterator tmp = *this; --(*this); return tmp; }

			bool	operator==(const tree_iterator&	Iter) { return node_pointer == Iter.base() };
			bool	operator!=(const tree_iterator& Iter) { return node_pointer != Iter.base() };
	};
}

#endif
