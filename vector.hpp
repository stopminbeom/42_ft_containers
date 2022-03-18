#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include "./utils/reverse_iterator.hpp"
# include "./utils/random_access_iterator.hpp"
# include "./utils/is_integral.hpp"
# include "./utils/enable_if.hpp"

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
			pointer			start;
			pointer 		end;
			allocator_type	alloc;
			size_type		capacity;
			size_type		size;

		public :
			explicit vector( const Allocator& _alloc = allocator_type() )
			: start(nullptr), end(nullptr), capacity(0), alloc(_alloc), size(0) {}
			explicit vector( size_type count, const T& value = T(), const Allocator& _alloc = Allocator())
			: alloc(_alloc), size(count), capacity(1) {
				size_type	i = 1;
				while (i < size) {
					i = i*2;
				}
				capacity = i;
				start = alloc.allocate(capacity);
				end = start;
				for (size_type i = 0; i < count; end++)
					alloc.construct(end, value);
			}
			template < class InputIt >
			vector( InputIt first, InputIt last, const Allocator& _alloc = Allocator() ) 
					// ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type = 0)
			: alloc(_alloc) {
				
				size_type	i = 1;
				while (i < size) {
					i = i*2;
				}
				capacity = i;
			}
			vector( const vector& other );
	};
}

#endif
