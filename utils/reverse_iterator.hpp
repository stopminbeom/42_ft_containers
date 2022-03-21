#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "./iterator_traits.hpp"

namespace ft {
	template < class Iter >
	class reverse_iterator {
		public:
			typedef Iter													iterator_type;
			typedef typename ft::iterator_traits<Iter>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iter>::value_type			value_type;
			typedef typename ft::iterator_traits<Iter>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iter>::pointer				pointer;
			typedef typename ft::iterator_traits<Iter>::reference			reference;
		
		protected:
			iterator_type	current;

		public:
			reverse_iterator() : current() {}
			explicit reverse_iterator( iterator_type x ) : current(x) {}
			template< class U >
			reverse_iterator( const reverse_iterator<U>& other ) : current(other.base()){}
			~reverse_iterator() {};
			template< class U >
			reverse_iterator& operator=( const reverse_iterator<U>& other ) {
				current = other.base();
				return *this;
			}
			iterator_type base() const {
				return current;
			}
			reference operator*() const {
				Iter	tmp = current;
				return *--tmp;
			}
			pointer operator->() const {
				return &(operator*());
			}
			reference operator[]( difference_type n ) const {
				return base()[-n-1];
			}
			reverse_iterator& operator++() {
				--current;
				return *this;
			}
			reverse_iterator& operator--() {
				++current;
				return *this;
			}
			reverse_iterator operator++( int ) {
				reverse_iterator tmp = *this;
				++(*this);
				return tmp;
			}
			reverse_iterator operator--( int ) {
				reverse_iterator tmp = *this;
				--(*this);
				return tmp;
			}
			reverse_iterator operator+( difference_type n ) const {
				return reverse_iterator(base() - n);
			}
			reverse_iterator operator-( difference_type n ) const {
				return reverse_iterator(base() + n);
			}
			reverse_iterator& operator+=( difference_type n ){
				current -=n;
				return *this;
			}
			reverse_iterator& operator-=( difference_type n ){
				current +=n;
				return *this;
			}
	};

	template < typename Iter >
	bool operator==( const reverse_iterator<Iter>& lhs,
					const reverse_iterator<Iter>& rhs )
					{ return lhs.base() == rhs.base(); }
	template < typename Iter, typename I_const >
	bool operator==( const reverse_iterator<Iter>& lhs,
					const reverse_iterator<I_const>& rhs )
					{ return lhs.base() == rhs.base(); }
	template < typename Iter >
	bool operator!=( const reverse_iterator<Iter>& lhs,
					  const reverse_iterator<Iter>& rhs )
					{ return lhs.base() != rhs.base(); }
	template < typename Iter, typename I_const >
	bool operator!=( const reverse_iterator<Iter>& lhs,
					const reverse_iterator<I_const>& rhs )
					{ return lhs.base() != rhs.base(); }
	template < typename Iter >
	bool operator<( const reverse_iterator<Iter>& lhs,
					const reverse_iterator<Iter>& rhs )
					{ return lhs.base() > rhs.base(); }
	template < typename Iter, typename I_const >
	bool operator<( const reverse_iterator<Iter>& lhs,
					const reverse_iterator<I_const>& rhs )
					{ return lhs.base() > rhs.base(); }
	template < typename Iter >
	bool operator<=( const reverse_iterator<Iter>& lhs,
					  const reverse_iterator<Iter>& rhs )
					{ return lhs.base() >= rhs.base(); }
	template < typename Iter, typename I_const >
	bool operator<=( const reverse_iterator<Iter>& lhs,
					const reverse_iterator<I_const>& rhs )
					{ return lhs.base() >= rhs.base(); }
	template < typename Iter >
	bool operator>( const reverse_iterator<Iter>& lhs,
					const reverse_iterator<Iter>& rhs )
					{ return lhs.base() < rhs.base(); }
	template < typename Iter, typename I_const >
	bool operator>( const reverse_iterator<Iter>& lhs,
					const reverse_iterator<I_const>& rhs )
					{ return lhs.base() < rhs.base(); }
	template < typename Iter >
	bool operator>=( const reverse_iterator<Iter>& lhs,
					  const reverse_iterator<Iter>& rhs )
					{ return lhs.base() <= rhs.base(); }
	template < typename Iter, typename I_const >
	bool operator>=( const reverse_iterator<Iter>& lhs,
					const reverse_iterator<I_const>& rhs )
					{ return lhs.base() <= rhs.base(); }
	template< class Iter >
	reverse_iterator<Iter> operator+( typename reverse_iterator<Iter>::difference_type n,
									  const reverse_iterator<Iter>& it ) { return (it + n); }
	template< class Iter >
	typename reverse_iterator<Iter>::difference_type operator- 
		( const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs ) { return rhs.base() - lhs.base(); }
	template< class Iter, class I_const >
	typename reverse_iterator<Iter>::difference_type operator- 
		( const reverse_iterator<Iter>& lhs, const reverse_iterator<I_const>& rhs ) { return rhs.base() - lhs.base(); }
}

#endif
