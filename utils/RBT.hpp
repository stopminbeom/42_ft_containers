#ifndef RBT_HPP
# define RBT_HPP

# include <memory>

namespace ft {
	enum RBcolor { RED = false, BLACK = true };

	template < typename T, typename Alloc = std::allocator<T> >
	struct RBTnode {
		public :
			typedef T			value_type;
			typedef	RBcolor		color_type;
			typedef	RBTnode*	node;

			value_type	value;
			color_type	color;
			node		parent;
			node		l_child;
			node		r_child;
			Alloc		alloc;
			
			RBTnode() : value(nullptr), color(RED), parent(nullptr), l_child(nullptr), r_child(nullptr), alloc(Alloc()) {}
			RBTnode(const T& val) : value(nullptr), color(RED), parent(nullptr), l_child(nullptr), r_child(nullptr), alloc(Alloc()) {
				value = alloc.allocate(1);
				alloc.construct(value, val);
			}
			RBTnode(const RBTnode& other) : value(other.value), color(other.color), parent(other.parent), l_child(other.l_child), r_child(other.r_child), alloc(other.alloc) {}
			~RBTnode() {
				if (value) {
					alloc.destroy(value);
					alloc.deallocate(value, 1);
				}
			}

			node operator= (const node& other) {
				if (*this = other)
					return *this;
				this->value = other.value;
				this->color = other.color;
				this->parent = other.parent;
				this->l_child = other.l_child;
				this->r_child = other.r_child;
				return *this;
			}

			bool operator== (const RTBnode& other) {
				if (this->value == other.value)
					return true;
				return false;
			}

			bool operator!= (const RBTnode& other) {
				if (this->value != other.value)
					return true;
				return false;
			}
	};

	template <class T1, class T2>
	bool operator== (const RBTnode<T1>& lhs, const RBTnode<T2>& rhs) {
		return lhs == rhs;
	}
	template <class T1, class T2>
	bool operator!= (const RBTnode<T1>& lhs, const RBTnode<T2>& rhs) {
		return lhs != rhs;
	}
}

#endif
