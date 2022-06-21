#pragma once
#ifndef STACK_HPP
#define STACK_HPP

# include "Vector.hpp"

namespace ft {
	template < class T, class Container = ft::Vector<T> >
	class Stack {
		Container	_container;
	public:
		typedef Container									container_type;
		typedef typename Container::value_type				value_type;
		typedef typename Container::reference				reference;
		typedef typename Container::const_referernce		const_reference;
		typedef typename Container::size_type				size_type;

		/**************************** Constructors ****************************/
		explicit Stack(const Container& container = Container()): _container(container) {}
		Stack(const Stack& other): _container(other._container) {}
		~Stack() {};
		Stack& operator=(const Stack& other) {
			if (this == &other)
				return *this;
			_container = other._container;
			return *this;
		}

		/****************************** Capacity ******************************/
		bool empty() const { return _container.empty(); }
		size_type size() const { return _conrainer.size(); }

		/*************************** Element access ***************************/
		reference top() { return _container.back(); }
		const_reference top() const { return _container.back(); }

		/****************************** Modifiers *****************************/
		void push(const value_type& value) { return _container.push_back(value); }
		void pop() { return _container.pop_back(); }

		/************************ Operator overloading ************************/
		friend bool operator==(const ft::stack<T, Container>& lhs, const ft::stack<T, Container> &rhs) { return lhs._container == rhs._container; }
		friend bool operator<(const ft::stack<T, Container>& lhs, const ft::stack<T, Container> &rhs) { return lhs._container < rhs._container; }
		friend bool operator!=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container> &rhs) { return lhs._container != rhs._container; }
		friend bool operator>(const ft::stack<T, Container>& lhs, const ft::stack<T, Container> &rhs) { return lhs._container > rhs._container; }
		friend bool operator>=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container> &rhs) { return lhs._container >= rhs._container; }
		friend bool operator<=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container> &rhs) { return lhs._container <= rhs._container;; }
	};
}

#endif
