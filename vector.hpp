#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include "./utils/reverse_iterator.hpp"
# include "./utils/random_access_iterator.hpp"
# include "./utils/is_integral.hpp"
# include "./utils/enable_if.hpp"
# include "./utils/lexicographical_compare.hpp"

namespace ft {
	template< class T, class Allocator = std::allocator<T> >
	class vector {
		public :
			typedef	T										value_type;
			typedef	Allocator								allocator_type;
			typedef	size_t									size_type;
			typedef	ptrdiff_t								difference_type;
			typedef	T&										reference;
			typedef const T&								const_reference;
			typedef	typename	Allocator::pointer			pointer;
			typedef	typename	Allocator::const_pointer	const_pointer;
			typedef	ft::random_access_iterator<T>			iterator;
			typedef	ft::random_access_iterator<const T>		const_iterator;
			typedef	ft::reverse_iterator<T>					reverse_iterator;
			typedef	ft::reverse_iterator<const T>			const_reverse_iterator;

		private :
			value_type*		start; // 시작지점 = begin()
			value_type* 	fin; // 끝지점 = end()
			allocator_type	alloc; 
			size_type		cap; // capacity_전체 할당 공간
			size_type		len; // 배열이 차있는 공간

		public :
			explicit vector( const Allocator& _alloc = allocator_type() )
			: start(nullptr), fin(nullptr), cap(0), alloc(_alloc), len(0) {}
			explicit vector( size_type count, const T& value = T(), const Allocator& _alloc = Allocator())
			: alloc(_alloc), len(count), cap(1) {
				size_type	i = 1;
				while (i < len) {
					i = i*2;
				}
				cap = i;
				start = alloc.allocate(cap);
				fin = start;
				for (size_type i = 0; i < count; fin++)
					alloc.construct(fin, value);
			}
			template < class InputIt >
			vector( InputIt first, InputIt last, const Allocator& _alloc = Allocator(),  
					ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type )
			: alloc(_alloc) {
				difference_type	diff = ft::distance(first, last);
				len = static_cast<size_type>(diff);
				size_type	i = 1;
				while (i < len) {
					i = i*2;
				}
				cap = i;
				start = alloc.allocate(cap);
				fin = start;
				for (; first != last ; fin++, first++ ) {
					alloc.construct(fin, *first);
				}
			}
			vector( const vector& other ) {
				*this = other;
			}
			~vector() {
				clear();
				if (cap)
					alloc.deallocate(start, cap);
			}

			vector& operator=( const vector& other ) {
				alloc = other.alloc;
				cap = other.cap;
				len = other.len;
				start = alloc.allocate(cap);
				fin = start;
				pointer	tmp = other.start;
				for (; fin != other.fin; fin++, tmp++) {
					alloc.construct(fin, *tmp);
				}
				return *this;
			}

			void assign( size_type count, const T& value ) {
				clear();
				if (cap < count) {
					alloc.deallocate(start, cap);
					len = count;
					size_type	i = 1;
					while (i < len) {
						i = i*2;
					}
					cap = i;
					start = alloc.allocate(cap);
				}
				fin = start;
				for ( size_type i = 0; i < len ; i++, fin++) {
					alloc.construct(fin, *value);
				}
			}
			template< class InputIt >
			void assign( InputIt first, InputIt last, ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type ) {
				clear();
				difference_type	diff = ft::distance(first, last);
				if (diff > cap) {
					alloc.deallocate(start, cap);
					size_type	i = 1;
					while (i < len) {
						i = i*2;
					}
					cap = i;
					start = alloc.allocate(cap);
				}
				len = static_cast<size_type>(diff);
				fin = start;
				for ( ; fin != last; fin++, first++) {
					alloc.construct(fin, value_type(*first));
				}
			}

			allocator_type get_allocator() const {
				return alloc;
			}

			reference at( size_type pos ) {
				if (!(pos < size()))
					throw std::out_of_range("vector::at");
				return (*this)[pos];
			}
			const_reference at( size_type pos ) const {
				if (!(pos < size()))
					throw std::out_of_range("vector::at");
				return (*this)[pos];
			}

			reference operator[]( size_type pos ) {
				return (*this)[pos];
			}
			const_reference operator[]( size_type pos ) const {
				return (*this)[pos];
			}

			reference front() {
				return *start;
			}
			const_reference front() const {
				return *start;
			}

			reference back() {
				return *(fin - 1);
			}
			const_reference back() const {
				return *(fin - 1);
			}

			T* data() {
				return start;
			}
			const T* data() const {
				return start;
			}

			iterator begin() {
				return iterator(start);
			}
			const_iterator begin() const {
				return const_iterator(start);
			}

			iterator end() {
				return iterator(fin);
			}
			const_iterator end() const {
				return const_iterator(fin);
			}

			reverse_iterator rbegin() {
				return reverse_iterator(end());
			}
			const_reverse_iterator rbegin() const {
				return const_reverse_iterator(end());
			}

			reverse_iterator rend() {
				return reverse_iterator(begin());
			}
			const_reverse_iterator rend() const {
				return const_reverse_iterator(begin());
			}

			bool empty() const {
				if (len)
					return false;
				return true;
			}

			size_type size() const {
				return len;
			}

			size_type max_size() const {
				return alloc.maxsize();
			}

			void reserve( size_type new_cap ) {
				if (new_cap <= cap)
					return ;
				if (max_size() < new_cap)
					throw std::length_error("vector::reserve");
				value_type* prev_start = start;
				value_type* prev_fin = fin;
				size_type	prev_cap = cap;
				
				start = alloc.allocate(new_cap);
				fin = start;
				while (prev_start != prev_fin) {
					alloc.construct(fin, *prev_start);
					prev_start++;
					fin++;
				}
				alloc.deallocate(prev_start, prev_cap);
			}

			size_type capacity() const {
				return cap;
			}

			void	clear()
			{
				for (size_type i = 0; i < len; i++)
				{
					fin--;
					alloc.destroy(fin) ;
				}
				len = 0 ;
			}

			iterator insert( iterator pos, const T& value ) {
				if (len + 1 > cap) {
					size_type new_cap = cap * 2;
					this->reserve(new_cap);
				}
				if (pos >= end()) {
					alloc.construct(fin, value);
				}
				else {
					value_type* tmp = fin;
					for (size_type i = len; i < len + 1; i--) {
						alloc.construct(tmp, *(tmp - 1));
						tmp--;
						alloc.destroy(tmp);
						if (pos == &(*tmp))
							break;
					}
					alloc.construct(tmp, value);
				}
				len++;
				fin++;
				return pos ;
			}
			void insert( iterator pos, size_type count, const T& value ) {
				while (len + count > cap) {
					size_type new_cap = cap * 2;
					this->reserve(new_cap);
				}
				if (pos >= end())
					pos = fin;
				value_type* tmp = fin;
				for (size_type i = len; i < len + 1; i--) {
						alloc.construct(tmp, *(tmp - 1));
						tmp--;
						alloc.destroy(tmp);
						if (pos == &(*tmp))
							break;
				}
				for (size_type i = 0; i < count; i++) {
					alloc.construct(tmp + i, value);
				}
				len = len + count;
				fin = fin + count;
			}
			template< class InputIt >
			void insert( iterator pos, InputIt first, InputIt last ) {
				difference_type	diff = ft::distance<InputIt>(first, last);
				size_type	itlen = static_cast<size_type>(diff);
				while (len + itlen > cap) {
					size_type new_cap = cap * 2;
					this->reserve(new_cap);
				}
				if (pos >= end())
					pos = fin;
				value_type* tmp = fin;
				for (size_type i = len; i < len + 1; i--) {
						alloc.construct(tmp, *(tmp - 1));
						tmp--;
						alloc.destroy(tmp);
						if (pos == &(*tmp))
							break;
				}
				for (size_type i = 0; i < itlen; i++, first++) {
					alloc.construct(tmp + i, *first);
				}
				len = len + itlen;
				fin = fin + itlen;
			}

			iterator erase( iterator pos ) {
				if (fin < pos)
					return pos;
				value_type* tmp = &(*pos);
				for (; tmp < fin; tmp++) {
					alloc.destroy(tmp);
					alloc.construct(tmp, *(tmp + 1));
				}
				alloc.destroy(tmp);
				len--;
				fin--;
				return pos;
			}
			iterator erase( iterator first, iterator last ) {
				if (fin < first)
					return last;
				if (fin < last)
					last = fin;
				difference_type	diff = ft::distance<iterator>(first, last);
				len = len - diff;
				diff = ft::distance<iterator>(start, first);
				size_type	itpos = static_cast<size_type>(diff);
				for (; first != last; first++)
					alloc.distroy(first);
				for (; last < fin; last++, itpos++) {
					if (this->start + itpos)
						alloc.destroy(start + itpos);
					alloc.construct(start + itpos, *last);
				}
				return iterator(start + diff);
			}

			void push_back( const T& value ) {
				if (len + 1 > cap) {
					size_type new_cap = cap * 2;
					this->reserve(new_cap);
				}
				this->insert(end(), value);
			}

			void pop_back() {
				if (len == 0)
					return ;
				this->erase(end() - 1);
			}

			void resize( size_type count, T value = T() ) {
				if (size() > count) {
					while (size() != count)
						pop_back();
				}
				else if (size() < count) {
					while (size() != count)
						push_back(value);
				} 
			}

			void swap( vector& other ) {
				value_type*		t_start = other.start;
				value_type* 	t_fin = other.fin;
				allocator_type	t_alloc = other.alloc;
				size_type		t_cap = other.cap;
				size_type		t_len = other.len;

				other.alloc = this->alloc;
				other.start = this->start;
				other.fin = this->fin;
				other.cap = this->cap;
				other.len = this->len;

				this->alloc = t_alloc;
				this->start = t_start;
				this->fin = t_fin;
				this->cap = t_cap;
				this->len = t_len;
			}
	};

	template< class T, class Alloc >
	bool operator==( const std::vector<T,Alloc>& lhs, const std::vector<T,Alloc>& rhs ) {
		if (lhs.size() != rhs.size())
			return false;
		typedef	ft::vector<T>::iterator	first1 = lhs.begin();
		typedef	ft::vector<T>::iterator	first2 = rhs.begin();
		for (; first1 != lhs.end(); first1++, first2++) {
			if (first1 != first2)
				return false;
		}
		return true;
	}
	template< class T, class Alloc >
	bool operator!=( const std::vector<T,Alloc>& lhs, const std::vector<T,Alloc>& rhs ) {
		return !(lhs == rhs);
	}
	template< class T, class Alloc >
	bool operator<( const std::vector<T,Alloc>& lhs, const std::vector<T,Alloc>& rhs ) {
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	template< class T, class Alloc >
	bool operator<=( const std::vector<T,Alloc>& lhs, const std::vector<T,Alloc>& rhs ) {
		return (!lhs > rhs);
	}
	template< class T, class Alloc >
	bool operator>( const std::vector<T,Alloc>& lhs, const std::vector<T,Alloc>& rhs ) {
		return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
	}
	template< class T, class Alloc >
	bool operator>=( const std::vector<T,Alloc>& lhs, const std::vector<T,Alloc>& rhs ) {
		return (!lhs < rhs);
	}
	template< class T, class Alloc >
	void swap( vector<T,Alloc>& lhs, vector<T,Alloc>& rhs ) {
		vector<T, Alloc>	tmp(rhs);
		tmp.swap(lhs);
		tmp.swap(rhs);
	}
}

#endif
