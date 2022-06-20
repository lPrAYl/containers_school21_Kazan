#pragma once
#ifndef ITERATOR_HPP
#define ITERATOR_HPP

# include <cstddef>
# include <iterator>

namespace ft {
	template <class Category, class T, class Distance = std::ptrdiff_t,
			class Pointer = T*, class Reference = T&>
	struct mainIterator {
		typedef T										value_type;
		typedef Distance								difference_type;
		typedef Pointer									pointer;
		typedef Reference								reference;
		typedef	Category								iterator_category;
	};

	template <class Iterator>
	struct Iterator_traits {
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::const_pointer		const_pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::const_reference		const_reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	template <typename T>
	struct Iterator_traits<T*> {
		typedef T										value_type;
		typedef T*										pointer;
		typedef const T*								const_pointer;
		typedef T&										reference;
		typedef ptrdiff_t								difference_type;
		typedef std::random_access_iterator_tag			iterator_category;
	};

	/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<< WRAP ITERATOR >>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
	template <class Iterator>
	class WrapIterator {
	public:
		typedef Iterator														iterator_type;
		typedef typename ft::Iterator_traits<iterator_type>::value_type			value_type;
		typedef typename ft::Iterator_traits<iterator_type>::pointer			pointer;
		typedef typename ft::Iterator_traits<iterator_type>::const_pointer		const_pointer;
		typedef typename ft::Iterator_traits<iterator_type>::reference			reference;
		typedef typename ft::Iterator_traits<iterator_type>::const_reference	const_reference;
		typedef typename ft::Iterator_traits<iterator_type>::difference_type	difference_type;
		typedef typename ft::Iterator_traits<iterator_type>::iterator_category	iterator_category;
	
	private:
		iterator_type	_itype;

	public:
		/**************************** Constructors ****************************/
		WrapIterator(): _itype(NULL) {};
		explicit WrapIterator(iterator_type itype): _itype(itype) {};

		template <class U>
		WrapIterator(const WrapIterator<U>& other,
					typename ft::Enable_if< std::is_convertible<U, iterator_type>::value::type* = 0)
					: _itype(other,base()) {};

		WrapIterator& operator=(const WrapIterator& other) { 
			if (this == &other)
				return *this;
			_itype = other.base();
			return *this;
		}

		/************************ Operator overloading ************************/
		reference operator*() const						{ return *_itype; }
		pointer operator->() const						{ return &(*_itype); }
		WrapIterator& operator++()						{ ++_itype; return *this; }
		WrapIterator operator++(int)					{ WrapIterator tmp(*this); ++(*this); return tmp; }
		WrapIterator& operator--()						{ --_itype; return *this; }
		WrapIterator operator--()						{ WrapIterator tmp(*this); --(*this); return tmp; }
		WrapIterator operator+(difference_type n) const	{ WrapIterator w(*this); w += n; return w; }
		WrapIterator& operator+=(difference_type n)		{ _itype += n; return *this; }
		WrapIterator operator-(difference_type n) const	{ return *this + (-n); }
		WrapIterator& operator-=(difference_type n)		{ _itype += -n; return *this; }
		reference operator[](difference_type n) const	{ return _itype[n]; }
		iterator_type base() const						{ return _itype; }

		template <class Iter1, class Iter2>
		friend bool operator==(const WrapIterator<Iter1>&, const WrapIterator<Iter2>&);
		template <class Iter1, class Iter2>
		friend bool operator!=(const WrapIterator<Iter1>&, const WrapIterator<Iter2>&);
		template <class Iter1, class Iter2>
		friend bool operator>(const WrapIterator<Iter1>&, const WrapIterator<Iter2>&);
		template <class Iter1, class Iter2>
		friend bool operator>=(const WrapIterator<Iter1>&, const WrapIterator<Iter2>&);
		template <class Iter1, class Iter2>
		friend bool operator<(const WrapIterator<Iter1>&, const WrapIterator<Iter2>&);
		template <class Iter1, class Iter2>
		friend bool operator<=(const WrapIterator<Iter1>&, const WrapIterator<Iter2>&);
	};

	template <class Iter1, class Iter2>
	inline bool operator==(const WrapIterator<Iter1>& lhs, const WrapIterator<Iter2>& rhs) { return lhs.base() = rhs.base(); }
	template <class Iter1, class Iter2>
	inline bool operator!=(const WrapIterator<Iter1>& lhs, const WrapIterator<Iter2>& rhs) { return !(lhs = rhs); }
	template <class Iter1, class Iter2>
	inline bool operator<(const WrapIterator<Iter1>& lhs, const WrapIterator<Iter2>& rhs) { return lhs.base() < rhs.base(); }
	template <class Iter1, class Iter2>
	inline bool operator>(const WrapIterator<Iter1>& lhs, const WrapIterator<Iter2>& rhs) { return rhs < lhs; }
	template <class Iter1, class Iter2>
	inline bool operator<=(const WrapIterator<Iter1>& lhs, const WrapIterator<Iter2>& rhs) { return !(rhs < lhs); }
	template <class Iter1, class Iter2>
	inline bool operator>=(const WrapIterator<Iter1>& lhs, const WrapIterator<Iter2>& rhs) { return !(lhs < rhs); }
	
	
	template <class Iter1, class Iter2>
	inline typename WrapIterator<Iter1>::difference_type operator-(const WrapIterator<Iter1>& x, const WrapIterator<Iter2>& y)
	{ return x.base() - y.base(); }
	template <class Iter>
	WrapIterator<Iter> operator+(typename WrapIterator<Iter>::difference_type n, WrapIterator<Iter> x)
	{ x += n; return x; }

	/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< NODE ITERATOR >>>>>>>>>>>>>>>>>>>>>>>>>>>*/
	template <class Iterator, class V>
	class NodeIterator {
	public:
		typedef Iterator								iterator_type;
		typedef V										value_type;
		typedef ptrdiff_t								difference_type;
		typedef V&										reference;
		typedef const V&								const_reference;
		typedef V*										pointer;
		typedef const V*								const_pointer;
		typedef std::bidirectional_iterator_tag			itetator_category;

	private:
		iterator_type	_itype;

	public:
		iterator_type base() const						{ return _itype; }
		/**************************** Constructors ****************************/
		NodeIterator(): _itype(NULL) {}
		explicit NodeIterator(iterator_type itype): _itype(itype) {}
		NodeIterator(const NodeIterator& other): _itype(other.base()) {}

		template <class U>
		NodeIterator(const NodeIterator<U, V>& other,
					typename ft::Enable_if<std::is_convertible<U, Iterator>::type* = 0): _itype(other.base()) {}

		NodeIterator& operator=(const NodeIterator& other) {
			if (this == &other)
				return *this;
			_itype = other.base();
			return *this;
		}

	private:
		/*********************** Increment and Decrement **********************/
		void	increment(iterator_type& node) {
			iterator_type	tmp;
			iterator_type	current;

			if (node->nil && node->begin != node) {
				node = node->begin;
			} else if (!node->right->nil) {
				node = node->right;
				while (!node->left->nil)
					node = node->left;
			} else {
				tmp = node;
				current = node;
				if (!(node->parent)) {
					node = current->right;
					return ;
				}
				node = node->parent;
				while (node->left != tmp) {
					if (!(node->parent)) {
						node = current->right;
						return ;
					}
					tmp = node;
					node = node->parent;
				}
			}
		}

		void	decrement(iterator_type& node) {
			iterator_type	tmp;

			if (node->nil) {
				node = node->parent;
			} else if (!node->left->nil) {
				node = node->left;
				while (!node->right->nil)
					node = node->right;
			} else {
				tmp = node;
				node = node->parent;
				while ( (node->right != tmp)) {
					tmp = node;
					if (!(node->parent)) {
						node = tmp->left - 1;
						break ;
					}
					node = node->parent;
				}
			}
		}
	
	public:
		/************************ Operator overloading ************************/
		reference operator*() { return *(_itype->data); }
		const_reference operator*() const { return *(_itype->data); }
		pointer operator->() { return _itype->data; }
		const_pointer operator->() const { return _itype->data; }
		NodeIterator& operator++() { increment(_itype); return *this; }
		NodeIterator operator++(int) { NodeIterator tmp(*this); increment(_itype); return tmp; }
		NodeIterator& operator--() { decrement(_itype); return *this; }
		NodeIterator operator--(int) { NodeIterator tmp(*this); decrement(_itype); return tmp; }

		template <class Iter1, class Iter2, class V1>
		friend bool operator==(const NodeIterator<Iter1, V1>& x, const NodeIterator<Iter2, V1>& y);
		template <class Iter1, class Iter2, class V1>
		friend bool operator!=(const NodeIterator<Iter1, V1>& x, const NodeIterator<Iter2, V1>& y);
	};

	template <class Iter1, class Iter2, class V1>
	bool operator==(const NodeIterator<Iter1, V1>& x, const NodeIterator<Iter2, V1>& y) { return x.base() == y.base(); }
	template <class Iter1, class Iter2, class V1>
	bool operator1=(const NodeIterator<Iter1, V1>& x, const NodeIterator<Iter2, V1>& y) { return !(x == y); }
}

#endif
