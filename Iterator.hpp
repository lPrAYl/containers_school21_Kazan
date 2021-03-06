#pragma once
#ifndef ITERATOR_HPP
#define ITERATOR_HPP

# include <cstddef>
# include "Utility.hpp"

namespace ft {
	template <class Iterator>
	struct IteratorTraits {
		typedef typename Iterator::value_type					value_type;
		typedef typename Iterator::difference_type				difference_type;
		typedef typename Iterator::pointer						pointer;
		typedef typename Iterator::const_pointer				const_pointer;
		typedef typename Iterator::reference					reference;
		typedef typename Iterator::const_reference				const_reference;
		typedef	typename Iterator::iterator_category			iterator_category;
	};

	template <typename T>
	struct IteratorTraits<T*> {
		typedef T												value_type;
		typedef T*												pointer;
		typedef const T*										const_pointer;
		typedef T&												reference;
		typedef const T&										const_reference;
		typedef ptrdiff_t										difference_type;
		typedef std::random_access_iterator_tag					iterator_category;
	};

	/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<< WRAP ITERATOR >>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
	template <class Iterator>
	class WrapIterator {
		Iterator	_wrap;
	public:
		typedef Iterator												iterator_type;
		typedef typename IteratorTraits<Iterator>::value_type			value_type;
		typedef typename IteratorTraits<Iterator>::pointer				pointer;
		typedef typename IteratorTraits<Iterator>::const_pointer		const_pointer;
		typedef typename IteratorTraits<Iterator>::reference			reference;
		typedef typename IteratorTraits<Iterator>::const_reference		const_reference;
		typedef typename IteratorTraits<Iterator>::difference_type		difference_type;
		typedef typename IteratorTraits<Iterator>::iterator_category	iterator_category;
		/**************************** Constructors ****************************/
		WrapIterator(Iterator wrap = NULL): _wrap(wrap) {}
		~WrapIterator() {}

		template <class W>
		WrapIterator(const WrapIterator<W>& other,
					typename ft::enable_if< std::is_convertible<W, iterator_type>::value>::type* = 0)
					: _wrap(other,base()) {}

		WrapIterator& operator=(const WrapIterator& other) {
			if (this == &other) return *this;
			_wrap = other.base();
			return *this;
		};
		Iterator	base() const { return _wrap; }

		/************************ Operator overloading ************************/
		WrapIterator& operator++()									{ ++_wrap; return *this; }
		WrapIterator operator++(int)								{ WrapIterator tmp(*this); ++(*this); return tmp; }
		WrapIterator& operator--()									{ --_wrap; return *this; }
		WrapIterator operator--(int)								{ WrapIterator tmp(*this); --(*this); return tmp; }
		difference_type operator+(WrapIterator const& other) const	{ return _wrap + other._wrap; }
		difference_type operator-(WrapIterator const& other) const	{ return _wrap - other._wrap; }
		WrapIterator operator+(difference_type n) const				{ return WrapIterator(_wrap + n); }
		WrapIterator operator-(difference_type n) const				{ return WrapIterator(_wrap - n); }
		WrapIterator& operator+=(difference_type n)					{ _wrap += n; return *this; }
		WrapIterator& operator-=(difference_type n)					{ _wrap += -n; return *this; }
		reference operator*() const									{ return *_wrap; }
		pointer operator->() const									{ return &(*_wrap); }
		reference operator[](difference_type n) const				{ return _wrap[n]; }
		bool operator==(WrapIterator const& other) const			{ return _wrap == other._wrap; }
		bool operator!=(WrapIterator const& other) const			{ return _wrap != other._wrap; }
		bool operator<(WrapIterator const& other) const				{ return _wrap < other._wrap; }
		bool operator>(WrapIterator const& other) const				{ return _wrap > other._wrap; }
		bool operator<=(WrapIterator const& other) const			{ return _wrap <= other._wrap; }
		bool operator>=(WrapIterator const& other) const			{ return _wrap >= other._wrap; }
	};

	/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< NODE ITERATOR >>>>>>>>>>>>>>>>>>>>>>>>>>>*/
	template <class Iterator, class Pair>
	class NodeIterator {
	private:
		Iterator	_node;
		/*********************** Next and Previous **********************/
		void	next() {
			if (_node->NIL && _node->begin != _node) {
				_node = _node->begin;
			} else if (!_node->right->NIL) {
				_node = _node->right;
				while (!_node->left->NIL)
					_node = _node->left;
			} else {
				Iterator tmp = _node;
				Iterator reverse = _node;
				if (!(_node->parent)) {
					_node = reverse->right;
					return ;
				}
				_node = _node->parent;
				while (_node->left != tmp) {
					if (!(_node->parent)) {
						_node = reverse->right;
						break ;
					}
					tmp = _node;
					_node = _node->parent;
				}
			}
		}

		void	prev() {
			if (_node->NIL) {
				_node = _node->parent;
			} else if (!_node->left->NIL) {
				_node = _node->left;
				while (!_node->right->NIL)
					_node = _node->right;
			} else {
				Iterator tmp = _node;
				_node = _node->parent;
				while (_node->right != tmp) {
					tmp = _node;
					if (!(_node->parent)) {
						_node = tmp->left - 1;
						break ;
					}
					_node = _node->parent;
				}
			}
		}
	public:
		typedef Iterator							iterator_type;
		typedef Pair								value_type;
		typedef ptrdiff_t							difference_type;
		typedef Pair&								reference;
		typedef const Pair&							const_reference;
		typedef Pair*								pointer;
		typedef const Pair*							const_pointer;
		typedef std::bidirectional_iterator_tag		iterator_category;

		iterator_type base() const					{ return _node; }
		/**************************** Constructors ****************************/
		NodeIterator(Iterator node = NULL): _node(node) {}
		~NodeIterator() {}

		template <class N, class Z>
		NodeIterator(NodeIterator<N, Z> const& other,
					typename ft::enable_if<std::is_convertible<N, Iterator>::value>::type* = 0): _node(other.base()) {}

		NodeIterator& operator=(const NodeIterator& other) {
			if (this == &other)
				return *this;
			_node = other.base();
			return *this;
		}

		/************************ Operator overloading ************************/
		NodeIterator	operator++(int)									{ NodeIterator tmp(*this); next(); return tmp; }
		NodeIterator	&operator++() 									{ next(); return *this; }
		NodeIterator	operator--(int)									{ NodeIterator tmp(*this); prev(); return tmp; }
		NodeIterator	&operator--() 									{ prev(); return *this; }
		reference 		operator*()		 								{ return *(_node->pair); }
		const_reference operator*() const								{ return *(_node->pair); }
		pointer 		operator->()									{ return _node->pair; }
		const_pointer 	operator->() const								{ return _node->pair; }
		bool			operator==(NodeIterator const &other) const 	{ return _node == other._node; }
		bool			operator!=(NodeIterator const &other) const 	{ return _node != other._node; }
		bool 			operator>(NodeIterator const &other) const 		{ return _node->pair > other._node->pair; }
		bool 			operator<(NodeIterator const &other) const 		{ return other._node->pair > _node->pair; }
		bool 			operator<=(NodeIterator const &other) const 	{ return _node->pair <= other._node->pair; }
		bool 			operator>=(NodeIterator const &other) const 	{ return _node->pair >= other._node->pair; }
	};
	
	/*<<<<<<<<<<<<<<<<<<<<<<<<<<<< REVERSE ITERATOR >>>>>>>>>>>>>>>>>>>>>>>>>>*/
	template <class Iterator>
	class ReverseIterator {
		Iterator	_reverse;

	public:
		typedef Iterator												iterator_type;
		typedef typename IteratorTraits<Iterator>::difference_type		difference_type;
		typedef typename IteratorTraits<Iterator>::value_type			value_type;
		typedef typename IteratorTraits<Iterator>::reference			reference;
		typedef typename IteratorTraits<Iterator>::const_reference		const_reference;
		typedef typename IteratorTraits<Iterator>::pointer				pointer;
		typedef typename IteratorTraits<Iterator>::const_pointer		const_pointer;
		typedef typename IteratorTraits<Iterator>::iterator_category	iterator_category;

		Iterator base() const { return _reverse; }
		/**************************** Constructors ****************************/
		ReverseIterator(Iterator reverse = NULL): _reverse(reverse) {}
		~ReverseIterator() {}

		template <class R> 
		ReverseIterator(const ReverseIterator<R>& other,
				typename ft::enable_if<std::is_convertible<R, Iterator>::value>::type* = 0): _reverse(other.base()) {}

		ReverseIterator& operator=(const ReverseIterator& other) {
			if (this == &other)
				return *this;
			_reverse = other.base();
			return *this;
		}

		/************************ Operator overloading ************************/
		reference			operator*()										{ return *_reverse; }
		pointer				operator->()									{ return &(operator*()); }
		ReverseIterator&	operator++()									{ --_reverse; return *this; }
		ReverseIterator		operator++(int)									{ ReverseIterator tmp(*this); _reverse--; return tmp; }
		ReverseIterator&	operator--()									{ ++_reverse; return *this; }
		ReverseIterator		operator--(int)									{ ReverseIterator tmp(*this); _reverse++; return tmp; }
		ReverseIterator		operator+(difference_type n) const				{ return ReverseIterator(_reverse - n); }
		ReverseIterator&	operator+=(difference_type n)					{ _reverse -= n; return *this; }
		ReverseIterator		operator-(difference_type n) const				{ return ReverseIterator(_reverse + n); }
		ReverseIterator&	operator-=(difference_type n)					{ _reverse += n; return *this; }
		reference			operator[](difference_type n) const				{ return *(*this + n); }
		bool				operator==(ReverseIterator const &obj) const	{ return _reverse == obj._reverse; };
		bool				operator!=(ReverseIterator const &obj) const	{ return _reverse != obj._reverse; };
		bool				operator<(ReverseIterator const &obj) const		{ return _reverse < obj._reverse; };
		bool				operator>(ReverseIterator const &obj) const		{ return _reverse > obj._reverse; };
		bool				operator<=(ReverseIterator const &obj) const	{ return _reverse <= obj._reverse; };
		bool				operator>=(ReverseIterator const &obj) const	{ return _reverse >= obj._reverse; };
	};
}

#endif
