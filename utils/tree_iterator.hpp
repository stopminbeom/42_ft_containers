#ifndef TREE_ITERATOR_HPP
# define TREE_ITERATOR_HPP

# include "RBT.hpp"
# include "iterator_traits.hpp"

namespace ft {
	template < typename Node > // 말 그대로 노드 value_type으로 pair를 들고옴. 트리에서 사용되는 노드 그 자체
	class tree_iterator : public ft::iterator<ft::bidirectional_iterator_tag, Node> {
		public :
			typedef Node::value_type;					value_type; // pair
			typedef bidirectional_iterator_tag			iterator_category;
			typedef ptr_diff_t							difference_type;
			typedef value_type*							pointer; // pair의 포인터
			typedef value_type&							reference; // pair의 참조자

		private :
			Node*	node_pointer; // 랜덤의 current와 유사
			Node*	end_ptr;

		public :
			tree_iterator() : node_pointer(nullptr), end_ptr(nullptr) {}
			tree_iterator( Node* node_ptr, Node* endP = nullptr ) : node_pointer(node_ptr), end_ptr(endP) {}
			tree_iterator( const tree_iterator& other ) { *this = other; }
			~tree_iterator() {};
			tree_iterator & operator= ( const tree_iterator& other ) {
				node_pointer = other.node_pointer;
				return *this;
			}

			Node*	base() const {
				return node_pointer;
			}

			reference	operator*() const {
				return node_pointer->value;
			}

			pointer		operator->() const {
				return &(node_pointer->value);
			}

	};
}

#endif
