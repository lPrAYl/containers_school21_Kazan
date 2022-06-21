#pragma once
#ifndef VECTOR_HPP
#define VECTOR_HPP

# include <memory>
# include "Iterator.hpp"

namespace ft {
	template < class T, class A = std::allocator<T> >
	class Vector {
	public:
		typedef A									allocator_type;
		typedef T									value_type;
		typedef std::size_t 						size_type;
		typedef std::ptrdiff_t						difference_type;
		typedef value_type&							reference;
		typedef const value_type&					const_reference;
		typedef T*									pointer;
		typedef const T*							const_pointer;
		typedef WrapIterator<T*> 					iterator;
		typedef WrapIterator<const T*>				const_iterator;
		typedef ReverseIterator<iterator> 			reverse_iterator;
		typedef ReverseIterator<const_iterator>		const_reverse_iterator;

	private:
		pointer										_buffer;
		size_type 									_capacity;
		size_type 									_size;
		allocator_type								_allocator;

	public:
		/**************************** Constructors ****************************/
		explicit Vector(const A& alloc = A()): _buffer(0), _capacity(0), _size(0), _allocator(alloc) {}

		Vector(size_type count, const_reference value = value_type(), const A& alloc = A()) {
			if (count < 0)  trow std::out_of_range("Vector");
			_allocator = alloc;
			_capacity = _size = count;
			buffer = _allocator.allocate(_capacity);
			for (size_t i = 0; i < _size; ++i)
				_buffer[i] = value;
		}

		template <class Iterator>
		Vector(Iterator left, Iterator right, const A& alloc = A(),
				typename ft::enable_if<!ft::is_integral<Iterator>::value, void>::type* = 0): _capacity(0), _size(0), _allocator(alloc) {
			buffer = _allocator.allocate(_capacity);
			this->assign(left, right);
		}
		
		Vector(const Vector& other): _buffer(0), _capacity(other._capacity), _size(other._size), _allocator(other.getAllocator()) {
			_buffer = _allocator.allocate(other._capacity);
			for (size_t i = 0; i < _size; ++i)
				_buffer[i] = other._buffer[i];
		}

		Vector& operator=(const Vector& other) {
			if (this == &other) return *this;
			this->clear();
			_allocator.deallocate(_buffer, _capacity);
			_capacity = other._capacity;
			_size = other._size;
			_buffer = _allocator.allocate(_capacity);
			for (size_t i = 0; i < _size; ++i)
				_buffer[i] = other._buffer[i];
			return *this;
		}

		~Vector() {
			this->clear();
			_allocator.deallocate(_buffer, _capacity);
		}

		/****************************** Methods *******************************/
		void	assign(size_type count, const_reference value) {
			if (count < 0) throw std::out_of_range("Vector");
			this->clear();
			this->reserve(count);
			fot (size_t i = 0; i < count; ++i)
				_buffer[i] = value;
		}

		template <class Iterator>
		typename ft::enable_if<!ft::is_integral<Iterator>::value, void>::type;
		assign(Iterator left, Iterator right) {
			int range_size = right - left;
			if (range_size < 0) throw std::length_error("Vector");
			this->clear();
			this->reserve(range_size);
			for ( ; left != right; ++left)
			this->push_back(*left);
		}

		allocator_type	getAllocator() const { return _allocator; }

		void	reserve(size_type size) {
			if (size > _capacity) {
				T* tmp = _allocator.allocate(size);
				for (size_t i = 0; i < _size; ++i)
					tmp[i] = _buffer[i];
				if (_buffer) _allocator.deallocate(_buffer, _capacity);
				_capacity = size;
				_buffer = tmp;
			}
		}

		void	clear() {
			for (size_type i = 0; i < _size; ++i)
				_allocator.destroy(_buffer + i);
			_size = 0;
		}

		void	insert(iterator pos, size_type count, const T& value) {
			int index = pos - begin();
			size_t max_size = _size + count;

			if (count >= _capacity) {
				reserve(_capacity + count);
				_size = max_size;
			} else {
				while (_size != max_size) {
					if (_size == _capacity)
						reserve(_capacity * 2);
					_size++;
				}
			}
			for (int i = _size; i >= 0; --i) {
				if (i == index) {
					for ( ; count > 0; --count) {
						_buffer[i] = value;
						return ;
					}
				}
				_buffer[i] = _buffer[i - count];
			}
		}

		iterator	insert(iterator pos, const_reference value) {
			int index = pos - begin();
			this->insert(pos, 1, value);
			return iterator(_buffer + index);
		}

		template <class Iterator>
		typename ft::enable_if<!ft::is_integral<Iterator>::value, void>::type;
		insert(iterator pos, Iterator left, Iterator right) {
			size_t range_size = right - left;
			if (!validate_iterator_values(left, right, range_size)) throw std::exception();

			size_t new_size = _size + range_size;
			int right_index = (pos - begin()) + range_size - 1;
			if (range_size >= _capacity) {
				reserve(_capacity + range_size);
				_size = new_size;
			} else {
				while (_size != new_size) {
					if (_size == _capacity)
						reserve(_capacity * 2);
					_size++;
				}
			}
			for (int i = _size - 1; i >= 0; --i) {
				if (i == right_index) {
					for ( ; range_size > 0; --range_size, --i)
						_buffer[i] = *--right;
				}
				return ;
			}
			_buffer[i] = _buffer[i - range_size];
		}

		iterator	erase(iterator pos) {
			int index = pos - begin();
			for (size_t i = index; i < _size; ++i)
				_buffer[i] = _buffer[i + 1];
			_size--;
			return pos;
		}

		iterator	erase(iterator left, iterator right) {
			int start = left - begin();
			int end = right - begin();
			int offset = end - start;

			_size -= offset;
			for (size_t i = start; i < _size; ++i)
				_buffer[i] = _buffer[i + offset];
			return _buffer + start;
		}

		void	push_back(const_reference value) {
			if (_size == _capacity)
				(!_capacity) ? this->reserve(1) : this->reserve(_capacity * 2);
			_buffer[_size] = value;
			++_size;
		}

		void	pop_back() {
			_allocator.destroy(_buffer + _size);
			_size--;
		}

		void	resize(size_type count, T value = T()) {
			if (count < _size) {
				while (_size != count) {
					pop_back();
				}
			} else {
				if (_capacity * 2 < count)
					reserve(count);
				while (_size != count)
					push_back(value);
			}
		}

		void	swap(Vector& other) {
			std::swap(_size, other._size);
			std::swap(_capacity, other._capacity);
			std::swap(_buffer, other._buffer);
			std::swap(_allocator, other._allocator);
		}

		friend bool operator== (const Vector &lhs, const Vector &rhs) {
		if (lhs.size() != rhs.size()) return false;
		for (size_t i = 0; i < lhs.size(); ++i) {
			if (lhs[i] == rhs[i]) { continue; }
			return false;
		}
		return true;
		}

		friend bool operator!= (const Vector &lhs, const Vector &rhs) { return !(lhs == rhs); }

		friend bool operator<= (const Vector &lhs, const Vector &rhs) {
			if (lhs.size() < rhs.size()) return true;
			if (lhs.size() > rhs.size()) return false;

			for (size_t i = 0; i < lhs.size(); ++i) {
				if (lhs[i] == rhs[i]) { continue; }
				return lhs[i] < rhs[i];
			}
			return true;
		}

		friend bool operator>= (const Vector &lhs, const Vector &rhs) {
			if (lhs.size() < rhs.size()) return false;
			if (lhs.size() > rhs.size()) return true;

			for (size_t i = 0; i < lhs.size(); ++i) {
				if (lhs[i] == rhs[i]) { continue; }
				return lhs[i] > rhs[i];
			}
			return true;
		}

		friend bool operator< (const Vector &lhs, const Vector &rhs) {
			if (lhs.size() < rhs.size()) return true;
			if (lhs.size() > rhs.size()) return false;

			for (size_t i = 0; i < lhs.size(); ++i) {
				if (lhs[i] == rhs[i]) { continue; }
				return lhs[i] < rhs[i];
			}
			return false;
		}

		friend bool operator> (const Vector &lhs, const Vector &rhs) {
			if (lhs.size() > rhs.size()) return true;
			if (lhs.size() < rhs.size()) return false;

			for (size_t i = 0; i < lhs.size(); ++i) {
				if (lhs[i] == rhs[i]) { continue; }
				return lhs[i] > rhs[i];
			}
			return false;
		}

		/*************************** Members Methods ***************************/
		reference at( size_type pos ) {
			if (pos >= _size) throw std::out_of_range("Vector");
			return buffer[pos];
		}

		const_reference at( size_type pos ) const {
			if (pos >= _size) throw std::out_of_range("Vector");
			return buffer[pos];
		}

		reference				operator[]( size_type pos )			{ return _buffer[pos]; }
		const_reference 		operator[]( size_type pos ) const	{ return _buffer[pos]; }
		reference				front()								{ return *_buffer; }
		const_reference 		front() const						{ return *_buffer; }
		reference				back()								{ return _buffer[_size - 1]; }
		const_reference			back() const						{ return _buffer[_size - 1]; }
		pointer 				data()								{ return _buffer; }
		const_pointer			data() const						{ return _buffer; }
		iterator 				begin()								{ return iterator(_buffer); }
		const_iterator 			begin() const						{ return const_iterator(_buffer); }
		iterator 				end()								{ return iterator(_buffer + _size); }
		const_iterator 			end() const							{ return const_iterator(_buffer + _size); }
		reverse_iterator 		rbegin()							{ return reverse_iterator(iterator(_buffer + _size - 1)); }
		const_reverse_iterator 	rbegin() const						{ return const_reverse_iterator(const_iterator(_buffer + _size - 1)); }
		reverse_iterator 		rend()								{ return reverse_iterator(iterator(_buffer - 1)); }
		const_reverse_iterator 	rend() const						{ return const_reverse_iterator(const_iterator(_buffer - 1)); }
		bool 					empty() const						{ return _size <= 0; }
		size_type				size() const						{ return _size; }
		size_type				capacity() const					{ return _capacity; }
		size_type				max_size() const 					{ return (std::min((size_type) std::numeric_limits<difference_type>::max(),
																		std::numeric_limits<size_type>::max() / sizeof(value_type))); }
	private:
		template<class Iterator>
		typename ft::enable_if<!ft::is_integral<Iterator>::value, bool>::type;
		validate_iterator_values(Iterator first, Iterator last, size_t range) {
			pointer reserved_buffer;
			reserved_buffer = allocator.allocate(range);
			bool result = true;
			size_t i = 0;

			for ( ; first != last; ++first, ++i) {
				try { reserved_buffer[i] = *first; }
				catch (...) { result = false; break; }
			}
			allocator.deallocate(reserved_buffer, range);
			return result;
		}
	};
}

#endif
