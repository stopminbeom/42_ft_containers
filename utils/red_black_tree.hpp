#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

# include <memory>
# include "tree_iterator.hpp"
# include "reverse_iterator.hpp"
# include "less.hpp"
# include "ft_nullptr.hpp"

namespace ft {
	template < typename T, typename Compare = ft::less<T>, typename Alloc = std::allocator<T> >
	class red_black_tree {
		public :
			typedef	red_black_tree											rbt;
			typedef	T														value_type;
			typedef	T*														pointer;
			typedef const T*												const_pointer;
			typedef T&														reference;
			typedef const T&												const_reference;
			typedef Compare													value_comp;
			typedef	Alloc													allocator_type;
			typedef	size_t													size_type;
			typedef	ft::RBTnode<T>											node_type;
			typedef typename	ft::tree_iterator<T>						iterator;
			typedef typename	ft::tree_iterator<const T>					const_iterator;
			typedef typename	Alloc::template rebind<node_type>::other	node_allocator_type; 
			// T가 아닌 것을 할당하기 위해 사용함. rebind는 c++17에서는 사용중지 권고이며, 이후 버전에서는 정의하지 않아도 컴파일이 된다! (하지만 여기는 98이지)

			rbt() : _root(ft_nullptr), _nil(ft_nullptr), _size(0), _comp(value_comp()), _node_alloc(node_allocator_type()) {
				_nil = make_nil();
				_root = _nil;
			}

			rbt(const rbt& other) : _root(ft_nullptr), _nil(ft_nullptr), _size(0), _comp(value_comp()), _node_alloc(node_allocator_type()) {
				_nil = make_nil();
				copy(other);
				_nil->parent = get_max_value_node();
			}

			~rbt() {
				clear();
				_node_alloc.destroy(_nil);
				_node_alloc.deallocate(_nil, 1);
			}

			rbt&	operator==(const rbt* t) {
				if (this != &x)
					copy(t);
				return *this;
			}

			void	copy(node_type* node) {
				if (node->value == ft_nullptr)
					return ;
				insert(*node->value);
				if (node->l_child->value != ft_nullptr)
					copy(node->l_child);
				if (node->r_child->value != ft_nullptr)
					copy(node->r_child);
			}

			node_type*	get_begin() const {
				node_type*	tmp = _root;
				while (tmp->l_child->value != ft_nullptr)
					tmp = tmp->l_child;
				return tmp;
			}

			node_type*	get_end() const { return _nil; }

			bool		empty() const { return _size == 0; }
			size_type	size() const { return _size; }
			size_type	max_size() const { return _node_alloc.max_size(); }

			ft::pair<node_type*, bool> insert(const value_type& val, node_type* hint = ft_nullptr) {
				node_type*	new_node = make_node(val);
				node_type*	position = _root;

				if (_size == 0) {
					_root = new_node;
					_root->l_child = _nil;
					_root->r_child = _nil;
					_root->parent = _nil;
					_root->color = BLACK;
					_nil->parent = _root;
					_size++;
					return ft::make_pair<_root, true>;
				}
				if (hint != ft_nullptr && hint->value != ft_nullptr)
					position = check_hint(val, hint);
				ft::pair<node_type*, bool> is_valid = get_position(position, new_node);
				if (is_valid.second == false) {
					_node_alloc.destroy(new_node);
					_node_alloc.deallocate(new_node, 1);
					return is_valid;
				}
				insert_case1(new_node);
				_size++;
				_nil->parent = get_max_value_node();
				return ft::make_pair(new_node, true);
			}

			size_type	erase (node_type* node) {
				if (node->value == ft_nullptr)
					return 0;
				node_type* m = replace_delete_node(node); // 삭제할 노드에 대한 정보 리턴
				node_type* c; // 지워야할 노드의 자식

				if (m->r_child->value == ft_nullptr)
					c = m->l_child;
				else
					c = m->r_child;
				replace_node(m, c);
				if (m->color == BLACK) {
					if (c->color == RED)
						c->color = BLACK;
					else
						delete_case1(c);
				}
				_size--;
				if (m->parent->value == ft_nullptr)
					_root = _nil;
				delete m;
				_nil->parent = get_max_value_node();
				return 1;
			}

			void	swap(rbt& t) {
				swap(_root, t._root);
				swap(_nil, t._nil);
				swap(_comp, t._comp);
				swap(_size, t._size);
				swap(_node_alloc, t._node_alloc);
			}

			void	clear(node_type* node = ft_nullptr) {
				if (node == ft_nullptr)
					node = _root;
				if (node->l_child->value != ft_nullptr) {
					clear(node->l_child);
					node->l_child = _nil;
				}
				if (node->r_child->value != ft_nullptr) {
					clear(node->r_child);
					node->r_child = _nil;
				}
				if (node->value != ft_nullptr) {
					if (node == _root)
						_root = _nil;
					_node_alloc.destory(node);
					_node_alloc.deallocate(node, 1);
					_size--;
				}
			}

			node_type*	find(value_type val) const {
				node_type*	ret = _root;
				if (_size == 0)
					return _nil;
				while (ret->value != ft_nullptr && (_comp(val, *ret->value) || _comp(*ret->value, val))) {
					if (_comp(val, *ret->value))
						ret = ret->l_child;
					else
						ret = ret->r_child;
				}
				return ret;
			}

		private :
			node_type*			_root;
			node_type*			_nil;
			size_type			_size;
			value_comp			_comp;
			node_allocator_type	_node_alloc;

			node_type*	make_nil() {
				node_type*	ret = _node_alloc.allocate(1);
				_node_alloc.construct(ret, node_type());
				ret->color = BLACK;
				ret->l_child = ret;
				ret->r_child = ret;
				ret->parent = ret;
				ret->value = ft_nullptr;
				return ret;
			}

			node_type*	make_node(const value_type& val) {
				node_type*	ret = _node_alloc.allocate(1);
				_node_alloc.construct(ret, node_type(val));
				return ret;
			}

			node_type*	check_hint(value_type val, node_type* hint) {
				if (_comp(*hint->value, *_root->value) && _comp(val, *hint->value))
					return hint;
				else if (_comp(*hint->value, *_root->value) && _comp(*hint->value, val))
					return _root;
				else if (_comp(*root->value, *hint->value) && _comp(val, *hint->value))
					return _root;
				else if (_comp(*root->value, *hint->value) && _comp(*hint->value, val))
					return hint;
				return _root;
			}

			node_type*	get_max_value_node() const {
				node_type*	tmp = _root;
				while (tmp->r_child->value != ft_nullptr)
					tmp = tmp->r_child;
				return tmp;
			}

			node_type*	sibling(node_type* node) {
				if (node == node->parent->l_child)
					return node->parent->r_child;
				return node->parent->r_child;
			}

			node_type*	replace_delete_node(node_type* node) {
				// 삭제할 노드에 대한 위치 전달
				// node의 child 유무를 확인하고 각각의 상황에 맞게 정리한다.
				// l_child가 있다면, 왼쪽 서브트리의 최댓값
				// r_child가 있다면, 오른쪽 서브트리의 최솟값을 찾는다
				// 찾은 값의 value를 node에 옮겨주고, 찾은 최소/최댓값 노드를 삭제하기 위해 리턴해준다.
				node_type*	ret;
				if (node->l_child->value != ft_nullptr) {
					ret = node->l_child;
					while (ret->r_child->value != ft_nullptr)
						ret = ret->r_child;
				}
				else if (node->r_child->value != ft_nullptr) {
					ret = node->r_child;
					while (ret->l_child->value != ft_nullptr)
						ret = ret->l_child;
				}
				else
					return node;

				node_type*	tmp_parent = node->parent;
				node_type*	tmp_left = node->l_child;
				node_type*	tmp_right = node->r_child;
				RBcolor		tmp_color = node->color;

				node->l_child = ret->l_child;
				if (ret->l_child->value != ft_nullptr)
					ret->l_child->parent = node;
				node->r_child = ret->r_child;
				if (ret->r_child->value != ft_nullptr)
					ret->r_child->parent = node;

				if (tmp_parent->l_child == node)
					tmp_parent->l_child = ret;
				else if (tmp_parent->r_child == node)
					tmp_parent->r_child = ret;

				if (ret == tmp_left) {
					tmp_right->parent = ret;
					ret->r_child = tmp_right;
					node->parent = ret;
					ret->l_child = node;
				}
				else if (ret == tmp_right) {
					tmp_left->parent = ret;
					ret->l_child = tmp_left;
					node->parent = ret;
					ret->r_child = node;
				}
				else {
					tmp_left->parent = ret;
					ret->l_child = tmp_left;
					tmp_right->parent = ret;
					ret->r_child = tmp_right;
					node->parent = ret->parent;
					ret->parent->r_child = node;
				}

				ret->parent = tmp_parent;

				if (ret->parent->value == ft_nullptr)
					_root = ret;
				node->color = ret->color;
				ret->color = tmp_color;

				return node;
			}

			node_type*	replace_node(node_type*	m, node_type* c) {
				c->parent = m->parent;
				if (m->parent->l_child == m)
					m->parent->l_child = c;
				else
					m->parent->r_child = c;
			}




	};
}

#endif
