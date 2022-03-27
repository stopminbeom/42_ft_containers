#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include "iterator_traits.hpp"
# include "ft_nullptr.hpp"

namespace ft {
	template < typename T >
	class random_access_iterator : public ft::iterator<ft::random_access_iterator_tag, T> {
		public :
			typedef typename	ft::iterator<ft::random_access_iterator_tag, T>::iterator_category	iterator_category;
			typedef typename	ft::iterator<ft::random_access_iterator_tag, T>::value_type			value_type;
			typedef typename	ft::iterator<ft::random_access_iterator_tag, T>::difference_type	difference_type;
			typedef T*																				pointer;
			typedef T&																				reference;
			
		protected :
			pointer	current;
		
		public :
			random_access_iterator() : current(ft_nullptr) {}
			random_access_iterator( pointer t ) : current(t) {}
			random_access_iterator( const random_access_iterator& other ) { current = other.current; }
			~random_access_iterator() {};
			random_access_iterator & operator=( const random_access_iterator& other ) {
				current = other.current;
				return *this;
			}
			pointer base() const {
				return current;
			}
			reference	operator*() const {
				return *current;
			}
			pointer					operator->() const { return &(operator*()); }
			reference				operator[]( difference_type n ) const { return base()[-n-1]; }
			random_access_iterator & operator++() {
				++current;
				return *this;
			}
			random_access_iterator operator++(int) {
				random_access_iterator tmp(*this);
				++current;
				return tmp;
			}
			random_access_iterator & operator--() {
				--current;
				return *this;
			}
			random_access_iterator operator--(int) {
				random_access_iterator tmp(*this);
				--current;
				return tmp;
			}
			random_access_iterator operator+(difference_type n) const {
				return random_access_iterator( base() + n );
			}
			random_access_iterator operator-(difference_type n) const {
				return random_access_iterator( base() - n );
			}
			random_access_iterator & operator+=(difference_type n) {
				current += n;
				return *this;
			}
			random_access_iterator & operator-=(difference_type n) {
				current -= n;
				return *this;
			}
			reference	operator[]( difference_type n ) {
				return *(operator+(n));
			}
			operator	random_access_iterator<const T> () const {
				return	random_access_iterator<const T>(this->current);
			}
	};
	template < typename T >
	bool	operator== (const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs) {
		return lhs.base() == rhs.base();
	}
	template < typename T, typename T_const >
	bool	operator== (const random_access_iterator<T>& lhs, const random_access_iterator<T_const>& rhs) {
		return lhs.base() == rhs.base();
	}
	template < typename T >
	bool	operator!= (const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs) {
		return lhs.base() != rhs.base();
	}
	template < typename T, typename T_const >
	bool	operator!= (const random_access_iterator<T>& lhs, const random_access_iterator<T_const>& rhs) {
		return lhs.base() != rhs.base();
	}
	template < typename T >
	bool	operator< (const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs) {
		return lhs.base() < rhs.base();
	}
	template < typename T, typename T_const >
	bool	operator< (const random_access_iterator<T>& lhs, const random_access_iterator<T_const>& rhs) {
		return lhs.base() < rhs.base();
	}
	template < typename T >
	bool	operator> (const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs) {
		return lhs.base() > rhs.base();
	}
	template < typename T, typename T_const >
	bool	operator> (const random_access_iterator<T>& lhs, const random_access_iterator<T_const>& rhs) {
		return lhs.base() > rhs.base();
	}
	template < typename T >
	bool	operator<= (const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs) {
		return lhs.base() <= rhs.base();
	}
	template < typename T, typename T_const >
	bool	operator<= (const random_access_iterator<T>& lhs, const random_access_iterator<T_const>& rhs) {
		return lhs.base() <= rhs.base();
	}
	template < typename T >
	bool	operator>= (const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs) {
		return lhs.base() >= rhs.base();
	}
	template < typename T, typename T_const >
	bool	operator>= (const random_access_iterator<T>& lhs, const random_access_iterator<T_const>& rhs) {
		return lhs.base() >= rhs.base();
	}
	template< typename T >
		random_access_iterator<T> operator+( typename random_access_iterator<T>::difference_type n,
										const random_access_iterator<T>& it ) { return (it + n); }
	template< typename T >
		typename random_access_iterator<T>::difference_type operator- (
			const random_access_iterator<T>& lhs,
			const random_access_iterator<T>& rhs ) { return lhs.base() - rhs.base(); }
	template< typename T , typename T_const >
		typename random_access_iterator<T>::difference_type operator- (
			const random_access_iterator<T>& lhs,
			const random_access_iterator<T_const>& rhs ) { return lhs.base() - rhs.base(); }
}

#endif
