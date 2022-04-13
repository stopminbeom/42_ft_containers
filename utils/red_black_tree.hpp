#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

# include <memory>
# include "tree_iterator.hpp"
# include "less.hpp"
# include "enable_if.hpp"

namespace ft {
	template < typename T, typename Compare = ft::less<T>, typename Alloc = std::allocator<T> > // T = pair
	class red_black_tree {
		public :
			typedef T											value_type;
			typedef	size_t										size_type;
			typedef	ft::RBTnode<T>								node_type;
			typedef	typename	Alloc::template rebind<node_type>::other	Node_Alloc;
			typedef typename	ft::tree_iterator<T, false>		iterator; // pair를 보내서 쓰는 iterator
			typedef typename	ft::tree_iterator<T, true>		const_iterator;

		private :
			node_type*		_root; // tree 의 root 노드 위치
			node_type*		_nil; // 모든 leaf node를 nil로 처리
			size_type		_size; // 현재 트리의 노드 갯수
			Compare			_comp; // compare
			Node_Alloc		_node_alloc; // 노드를 alloc하기 위함. 그냥 Alloc과는 조금 다름!
		
		public :
			red_black_tree() : _root(ft_nullptr), _nil(ft_nullptr), _size(0), _comp(Compare()), _node_alloc(Node_Alloc()) {
				_nil = make_nil();
				_root = _nil;
			}
			red_black_tree(const red_black_tree& other) : _root(ft_nullptr), _nil(ft_nullptr), _size(0), _comp(Compare()), _node_alloc(Node_Alloc()) {
				_nil = make_nil();
				copy(other);
				_nil->parent = get_max_value_node();
			}
			~red_black_tree () {
				clear();
				_node_alloc.destroy(_nil);
				_node_alloc.deallocate(_nil, 1);
			}

			void	copy(const red_black_tree& c) {
				clear();
				copy(c._root);
			}

			void	copy(node_type* node) {
				if (node->value == ft_nullptr)
					return;
				insert(*node->value);
				if (node->l_child->value != ft_nullptr)
					copy(node->l_child);
				if (node->r_child->value != ft_nullptr)
					copy(node->r_child);
			}

			node_type*	get_begin() const {
				node_type* tmp = _root;
				while (tmp->l_child->value != ft_nullptr)
					tmp = tmp->l_child;
				return tmp;
			}

			node_type*	get_end() const {
				return _nil;
			}

			bool	empty() const { return _size == 0; }
			size_type	size() const { return _size; }
			size_type	max_size() const { return _node_alloc.max_size(); }

			ft::pair<node_type*, bool> insert(const value_type& val, node_type* hint = ft_nullptr) {
				node_type* new_node = make_node(val);
				node_type* position = _root;

				if (_size == 0) {
					_root = new_node;
					_root->l_child = _nil;
					_root->r_child = _nil;
					_root->color = BLACK;
					_root->parent = _nil;
					_nil->parent = _root;
					_size++;
					return ft::make_pair(_root, true);
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

			size_type	erase(node_type* node) {
				if (node->value == ft_nullptr)
					return 0;
				node_type* real = replace_erase_node(node);
				node_type* child;
				if (real->r_child->value == ft_nullptr)
					child = real->l_child;
				else
					child = real->r_child;
				replace_node(real, child);
				if (real->color == BLACK) {
					if (child->color == RED)
						child->color = BLACK;
					else
						delete_case1(child);
				}
				_size--;
				if (real->parent->value == ft_nullptr)
					_root = _nil;
				delete real;
				_nil->parent = get_max_value_node();
				return 1;
			}

			void	swap(red_black_tree& x) {
				swap(_root, x._root);
				swap(_nil, x._nil);
				swap(_comp, x._comp);
				swap(_size, x._size);
				swap(_node_alloc, x._node_alloc);
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
					_node_alloc.destroy(node);
					_node_alloc.deallocate(node, 1);
					_size--;
				}
			}

			node_type* find(value_type val) const {
				node_type* res = _root;
				if (_size == 0)
					return _nil;
				while (res->value != ft_nullptr && (_comp(val, *res->value) || _comp(*res->value, val))) {
					if (_comp(val, *res->value))
						res = res->l_child;
					else
						res = res->r_child;
				}
				return res;
			}

			node_type* lower_bound(const value_type& val) const {
				iterator it(get_begin());
				iterator ite(get_end());
				while (it != ite) {
					if (!_comp(*it, val))
						break;
					it++;
				}
				return it.base();
			}

			node_type* upper_bound(const value_type& val) const {
				iterator it(get_begin());
				iterator ite(get_end());
				while (it != ite) {
					if (_comp(val, *it))
						break;
					it++;
				}
				return it.base();
			}

		private :
			node_type*	make_nil() {
				node_type*	tmp = _node_alloc.allocate(1);
				_node_alloc.construct(tmp, node_type());
				tmp->color = BLACK;
				tmp->l_child = tmp;
				tmp->r_child = tmp;
				tmp->parent = tmp;
				tmp->value = ft_nullptr;
				return tmp;
			}

			node_type*	make_node(const value_type& val) {
				node_type* res = _node_alloc.allocate(1);
				_node_alloc.construct(res, node_type(val));
				return res;
			}

			node_type* get_grand(node_type* node) const {
				if (node != ft_nullptr && node->parent != ft_nullptr)
					return node->parent->parent;
				return ft_nullptr;
			}

			node_type* get_uncle(node_type* node) const {
				node_type* grand = get_grand(node);
				if (grand == ft_nullptr)
					return ft_nullptr;
				if (grand->l_child == node->parent)
					return grand->r_child;
				return grand->l_child;
			}

			node_type* get_sibling(node_type* node) const {
				if (node == node->parent->l_child)
					return node->parent->r_child;
				return node->parent->l_child;
			}

			node_type* get_max_value_node() const {
				node_type* tmp = _root;
				while (tmp->r_child->value != ft_nullptr)
					tmp = tmp->r_child;
				return tmp;
			}

			node_type*	check_hint(value_type val, node_type* hint) {
				if (_comp(*hint->value, *_root->value) && _comp(val, *hint->value))
					return hint;
				else if (_comp(*hint->value, *_root->value) && _comp(*hint->value, val))
					return _root;
				else if (_comp(*_root->value, *hint->value) && _comp(val, *hint->value))
					return _root;
				else if (_comp(*_root->value, *hint->value) && _comp(*hint->value, val))
					return hint;
				else
					return _root;
			}

			ft::pair<node_type*, bool>	get_position(node_type* position, node_type* node) {
				while (position->value != ft_nullptr) {
					if (_comp(*node->value, *position->value)) {
						if (position->l_child->value == ft_nullptr) {
							position->l_child = node;
							node->parent = position;
							node->l_child = _nil;
							node->r_child = _nil;
							node->color = RED;
							break;
						}
						else
							position = position->l_child;
					}
					else if (_comp(*position->value, *node->value)) {
						if (position->r_child->value == ft_nullptr) {
							position->r_child = node;
							node->parent = position;
							node->l_child = _nil;
							node->r_child = _nil;
							node->color = RED;
							break;
						}
						else
							position = position->r_child;
					}
					else
						return ft::make_pair(position, false);
				}
				return ft::make_pair(position, true);
			}

			void	insert_case1(node_type* node) {
				if (node->parent->value != ft_nullptr)
					insert_case2(node);
				else
					node->color = BLACK;
			}

			void	insert_case2(node_type* node) {
				if (node->parent->color == RED)
					insert_case3(node);
			}

			void	insert_case3(node_type* node) {
				node_type* u = get_uncle(node);
				node_type* g;
				if ((u != NULL) && (u->color == RED)) {
					node->parent->color = BLACK;
					u->color = BLACK;
					g = get_grand(node);
					g->color = RED;
					insert_case1(g);
				}
				else
					insert_case4(node);
			}

			void	insert_case4(node_type* node) {
				node_type* g = get_grand(node);
				if ((node == node->parent->r_child) && (node->parent == g->l_child)) {
					rotate_left(node->parent);
					node = node->l_child;
				}
				else if ((node == node->parent->l_child) && (node->parent == g->r_child)) {
					rotate_right(node->parent);
					node = node->r_child;
				}
				insert_case5(node);
			}

			void	insert_case5(node_type* node) {
				node_type* g = get_grand(node);
				node->parent->color = BLACK;
				g->color = RED;
				if (node == node->parent->l_child)
					rotate_right(g);
				else
					rotate_left(g);
			}

			void	rotate_left(node_type* node) {
				node_type* c = node->r_child;
				node_type* p = node->parent;

				if (c->l_child->value != ft_nullptr)
					c->l_child->parent = node;

				node->r_child = c->l_child;
				node->parent = c;
				c->l_child = node;
				c->parent = p;

				if (p->value != ft_nullptr) {
					if (p->l_child == node)
						p->l_child = c;
					else
						p->r_child = c;
				}
				else
					_root = c;
			}

			void	rotate_right(node_type* node) {
				node_type* c = node->l_child;
				node_type* p = node->parent;

				if (c->r_child->value != ft_nullptr)
					c->r_child->parent = node;

				node->l_child = c->r_child;
				node->parent = c;
				c->r_child = node;
				c->parent = p;

				if (p->value != ft_nullptr) {
					if (p->r_child == node)
						p->r_child = c;
					else
						p->l_child = c;
				}
				else
					_root = c;
			}

			node_type* replace_erase_node(node_type* node) {
				node_type* ret;
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

				node_type* tmp_parent = node->parent;
				node_type* tmp_left = node->l_child;
				node_type* tmp_right = node->r_child;
				RBcolor tmp_color = node->color;

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

			void	replace_node(node_type* node, node_type* child) {
				child->parent = node->parent;
				if (node->parent->l_child == node)
					node->parent->l_child = child;
				else
					node->parent->r_child = child;
			}

			void	delete_case1(node_type* node) {
				if (node->parent->value != ft_nullptr)
       				delete_case2(node);
			}

			void	delete_case2(node_type* node) {
				node_type* s = get_sibling(node);
				if (s->color == RED) {
					node->parent->color = RED;
					s->color = BLACK;
					if (node == node->parent->l_child)
						rotate_left(node->parent);
					else
						rotate_right(node->parent);
				}
				delete_case3(node);
			}

			void	delete_case3(node_type* node) {
				node_type* s = get_sibling(node);
				if ((node->parent->color == BLACK) &&
					(s->color == BLACK) &&
					(s->l_child->color == BLACK) &&
					(s->r_child->color == BLACK)) {
						s->color = RED;
						delete_case1(node->parent);
				}
				else
					delete_case4(node);
			}

			void	delete_case4(node_type* node) {
				node_type* s = get_sibling(node);
				if ((node->parent->color == RED) &&
					(s->color == BLACK) &&
					(s->l_child->color == BLACK) &&
					(s->r_child->color == BLACK)) {
						s->color = RED;
						node->parent->color = BLACK;
				}
				else
					delete_case5(node);
			}

			void	delete_case5(node_type* node) {
				node_type* s = get_sibling(node);
    			if  (s->color == BLACK) {
					if ((node == node->parent->l_child) &&
						(s->r_child->color == BLACK) &&
						(s->l_child->color == RED)) {
							s->color = RED;
							s->l_child->color = BLACK;
							rotate_right(s);
					}
					else if ((node == node->parent->r_child) &&
							(s->l_child->color == BLACK) &&
							(s->r_child->color == RED)) {
							s->color = RED;
							s->r_child->color = BLACK;
							rotate_left(s);
					}
				}
				delete_case6(node);
			}

			void	delete_case6(node_type* node) {
				node_type* s = get_sibling(node);
				s->color = node->parent->color;
				node->parent->color = BLACK;
				if (node == node->parent->l_child) {
					s->r_child->color = BLACK;
					rotate_left(node->parent);
				}
				else {
					s->l_child->color = BLACK;
					rotate_right(node->parent);
				}
			}

			template <typename _T>
			void	swap(_T& a, _T& b) {
				_T tmp(a);
				a = b;
				b = tmp;
			}
	};
}

#endif
