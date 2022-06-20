#pragma once
#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>

namespace ft {
	template < class T, class A = std::allocator<T> >
	class Vector {
	public:
		typedef A											allocator_type;
		typedef std::allocator_traits<allocator_type>		allocator_traits;

		typedef T											value_type;
		typedef value_type&									reference;
		typedef const value_type&							const_reference;
		typedef typename allocator_traits::size_type		size_type;
		typedef typename allocator_traits::pointer			pointer;
		typedef typename allocator_traits::const_pointer	const_pointer;
		typedef typename allocator_traits::difference_type	difference_type;
		typedef ft::wrap_iter<pointer>						iterator;
		typedef ft::wrap_iter<const_pointer>				const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

	private:
		pointer			_begin;
		pointer			_end;
		pointer			_end_capacity;
		pointer			_container;
		size_type		_size;
		size_type		_capacity;
		allocator_type	_allocator;

	public:
		/ *************************** Constructors *************************** /
		
	};
}

#endif