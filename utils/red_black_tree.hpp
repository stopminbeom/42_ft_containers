#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

# include "tree_iterator.hpp"
# include "reverse_iterator.hpp"
# include "less.hpp"
# include <memory>

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

			rbt() : _root(nullptr), _nil(nullptr), _size(0), _comp(value_comp()), _node_alloc(node_allocator_type()) {
				_nil = make_nil();
				_root = _nil;
			}

			rbt(const rbt& other) : _root(nullptr), _nil(nullptr), _size(0), _comp(value_comp()), _node_alloc(node_allocator_type()) {
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
				if (node->value == nullptr)
					return ;
				insert(*node->value);
				if (node->l_child->value != nullptr)
					copy(node->l_child);
				if (node->r_child->value != nullptr)
					copy(node->r_child);
			}

			node_type*	get_begin() const {
				node_type*	tmp = _root;
				while (tmp->l_child->value != nullptr)
					tmp = tmp->l_child;
				return tmp;
			}

			node_type*	get_end() const { return _nil; }

			bool		empty() const { return _size == 0; }
			size_type	size() const { return _size; }
			size_type	max_size() const { return _node_alloc.max_size(); }

			ft::pair<node_type*, bool> insert(const value_type& val, node_type* hint = nullptr) {
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
				if (hint != nullptr && hint->value != nullptr)
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

			size_type	erase // 여기부터 작업해야함

			void	clear(node_type* node = nullptr) {
				if (node == nullptr)
					node = _root;
				if (node->l_child->value != nullptr) {
					clear(node->l_child);
					node->l_child = _nil;
				}
				if (node->r_child->value != nullptr) {
					clear(node->r_child);
					node->r_child = _nil;
				}
				if (node->value != nullptr) {
					if (node == _root)
						_root = _nil;
					_node_alloc.destory(node);
					_node_alloc.deallocate(node, 1);
					_size--;
				}
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
				ret->value = nullptr;
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
				while (tmp->r_child->value != nullptr)
					tmp = tmp->r_child;
				return tmp;
			}


	};
}

#endif
