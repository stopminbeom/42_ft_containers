#ifndef TREE_ITERATOR_HPP
# define TREE_ITERATOR_HPP

# include "RBTnode.hpp"
# include "iterator_traits.hpp"
# include "pair.hpp"

namespace ft {
	template < typename T, bool B > // 페어를 가지고 옴. 즉 트리의 노드를 탐색하지 않음.
	class tree_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T> {
		public :
			typedef const	T																			value_type; // Node의 value_type = pair
			typedef typename	ft::choose<B, const T*, T*>::type										pointer; // pair의 포인터
			typedef typename	ft::choose<B, const T&, T&>::type										reference; // pair의 참조자
			typedef typename	ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category		iterator_category;
			typedef typename	ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type		difference_type;
			typedef	ft::RBTnode<T>																		node_type;

		protected :
			node_type*	_node;

		public :
			tree_iterator( node_type* ptr = ft_nullptr ) : _node(ptr) {}
			tree_iterator( const tree_iterator<T, false>& other ) : _node(other.base()) {}
			virtual	~tree_iterator() {}

			tree_iterator & operator= ( const tree_iterator& other ) {
				if (this != &other)
					this->_node = other.base();
				return *this;
			}

			node_type*	base() const { return _node; }

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
					} // 가장 우측에서 ++ 을 할 경우, rbt에서 _nil에 만나 결국 while이 끝나게 된다. 즉 _node는 _nil을 가리키게 된다.
				}
				_node = tmp;
				return *this;
			}
			tree_iterator	operator++(int) { tree_iterator tmp = *this; ++(*this); return tmp; }

			tree_iterator&	operator--() {
				node_type* tmp = ft_nullptr;
				if (_node->value == ft_nullptr)
					tmp = _node->parent; // nil일 때 end - 1 로 가게 해줌
				else if (_node->l_child->value != ft_nullptr) {
					tmp = _node->l_child;
					while (tmp->r_child->value != ft_nullptr)
						tmp = tmp->r_child;
				}
				else {
					tmp = _node->parent;
					if (tmp->l_child == _node) {
						while (tmp->parent->l_child == tmp)
							tmp = tmp->parent;
						tmp = tmp->parent;
					} // 가장 좌측에서 -- 을 할 경우, rbt에서 _nil에 만나 결국 while이 끝나게 된다. 즉 _node는 _nil을 가리키게 된다.
				}
				_node = tmp;
				return *this;
			}
			tree_iterator	operator--(int) { tree_iterator tmp = *this; --(*this); return tmp; }

			bool	operator==( const tree_iterator& Iter ) { return _node == Iter._node; };
			bool	operator!=( const tree_iterator& Iter ) { return _node != Iter._node; };
	};
}

#endif
