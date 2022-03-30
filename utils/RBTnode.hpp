#ifndef RBTNODE_HPP
# define RBTNODE_HPP

# include <memory>
# include "ft_nullptr.hpp"

namespace ft {
	enum RBcolor { RED = false, BLACK = true };

	template < typename T >
	struct RBTnode {
		public :
			typedef T			value_type;	// pair
			typedef	RBcolor		color_type;

			value_type	value; // pair <key, mapped_type>
			color_type	color;
			RBTnode*	parent;
			RBTnode*	l_child;
			RBTnode*	r_child;
			
			RBTnode() : value(ft_nullptr), color(RED), parent(ft_nullptr), l_child(ft_nullptr), r_child(ft_nullptr) {}
			RBTnode(const T& val) : value(val), color(RED), parent(ft_nullptr), l_child(ft_nullptr), r_child(ft_nullptr) {}
			RBTnode(const RBTnode& other) : value(other.value), color(other.color), parent(other.parent), l_child(other.l_child), r_child(other.r_child) {}
			~RBTnode() {}

			RBTnode operator= (const RBTnode& other) {
				if (*this == other)
					return *this;
				this->value = other.value;
				this->color = other.color;
				this->parent = other.parent;
				this->l_child = other.l_child;
				this->r_child = other.r_child;
				return *this;
			}

			bool operator== (const RBTnode& other) {
				if (this->value == other->value)
					return true;
				return false;
			}

			bool operator!= (const RBTnode& other) {
				if (this->value != other->value)
					return true;
				return false;
			}
	};
}

#endif
