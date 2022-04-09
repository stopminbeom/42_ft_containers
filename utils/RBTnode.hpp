#ifndef RBTNODE_HPP
# define RBTNODE_HPP

# include <memory>
# include "ft_nullptr.hpp"

namespace ft {
	enum RBcolor { RED = false, BLACK = true };

	template < typename T, typename Alloc = std::allocator<T> >
	struct RBTnode {
		public :
			typedef T			value_type;	// pair
			typedef	RBcolor		color_type;

			value_type*	value; // pair <key, mapped_type>
			color_type	color;
			RBTnode*	parent;
			RBTnode*	l_child;
			RBTnode*	r_child;
			Alloc		alloc;
			
			RBTnode() : value(ft_nullptr), color(RED), parent(ft_nullptr), l_child(ft_nullptr), r_child(ft_nullptr) {}
			RBTnode(const T& val) : value(ft_nullptr), color(RED), parent(ft_nullptr), l_child(ft_nullptr), r_child(ft_nullptr) {
				value = alloc.allocate(1);
				alloc.construct(value, val);
			}
			RBTnode(const RBTnode& other) : value(ft_nullptr), color(RED), parent(ft_nullptr), l_child(ft_nullptr), r_child(ft_nullptr) {
				if (other.value != ft_nullptr) {
					value = alloc.allocate(1);
					alloc.construct(value, *other.value);
					color = other.color;
				}
			}
			~RBTnode() {
				if (value != ft_nullptr) {
					alloc.destroy(value);
					alloc.deallocate(value, 1);
				}
			}

			RBTnode& operator= (const RBTnode& other) {
				if (*this == other)
					return *this;
				if (value != ft_nullptr) {
					alloc.destroy(value);
				}
				alloc.construct(value, *other.value);
				this->color = other.color;
				this->parent = other.parent;
				this->l_child = other.l_child;
				this->r_child = other.r_child;
				return *this;
			}

			bool	operator== (const RBTnode& other) {
				return value == other.value;
			}

			bool	operator!= (const RBTnode& other) {
				return value != other.value;
			}
	};

	template <bool flag, class IsTrue, class IsFalse>
	struct choose;

	template <class IsTrue, class IsFalse>
	struct choose<true, IsTrue, IsFalse> {
		typedef IsTrue type;
	};

	template <class IsTrue, class IsFalse>
	struct choose<false, IsTrue, IsFalse> {
		typedef IsFalse type;
	};
}

#endif
