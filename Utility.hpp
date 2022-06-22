#pragma once
#ifndef UTILITY_HPP
#define UTILITY_HPP

namespace ft {
	template <class T, class A>
	class Vector;
	template <class Key, class T, class Compare, class A>
	class Map;

	template <class T, bool v>
	struct integral_constant {
		static const bool value = v;
		typedef T value_type;
		typedef integral_constant type;
		operator value_type() const { return value; }
	};

	template <class T> struct is_integral : public ft::integral_constant<T, false> {};
	template <> struct is_integral<bool> : public ft::integral_constant<bool, true> {};
	template <> struct is_integral<char> : public ft::integral_constant<bool, true> {};
	template <> struct is_integral<signed char> : public integral_constant<bool, true> {};
	template <> struct is_integral<unsigned char> : public integral_constant<bool, true> {};
	template <> struct is_integral<wchar_t> : public integral_constant<bool, true> {};
	template <> struct is_integral<char16_t> : public integral_constant<bool, true> {};
	template <> struct is_integral<short> : public integral_constant<bool, true> {};
	template <> struct is_integral<unsigned short> : public integral_constant<bool, true> {};
	template <> struct is_integral<int> : public integral_constant<bool, true> {};
	template <> struct is_integral<unsigned int> : public integral_constant<bool, true> {};
	template <> struct is_integral<long> : public integral_constant<bool, true> {};
	template <> struct is_integral<unsigned long> : public integral_constant<bool, true> {};
	template <> struct is_integral<long long> : public integral_constant<bool, true> {};
	template <> struct is_integral<unsigned long long> : public integral_constant<bool, true> {};

	template <bool B, class T = void> struct enable_if {};
	template <class T> struct enable_if<true, T> { typedef T type; };

	template <class Iterator1, class Iterator2>
	bool equal(Iterator1 left1, Iterator1 right1, Iterator2 left2) {
		for ( ; left1 != right1; ++left1, ++left2)
			if (!(*left1 == *left2))
				return false;
		return true;
	}

	template <class Iterator1, class Iterator2, class BindaryPredicate>
	bool equal(Iterator1 left1,  Iterator1 right1, Iterator2 left2, BindaryPredicate predicate) {
		for ( ; left1 != right1; ++left1, ++left2)
			if (!predicate(*left1, *left2))
				return false;
		return true;
	}

	template <class Iterator1, class Iterator2>
	bool lexicographical_compare(Iterator1 left1, Iterator1 right1, Iterator2 left2, Iterator2 right2) {
		for ( ; (left1 != right1) && (left2 != right2); ++left1, (void) ++left2) {
			if (*left1 < *left2) return true;
			if (*left2 < *left1) return false;
		}
		return left1 == right1 && left2 != right2;
	}

	template <class T1, typename T2>
	struct pair {
		typedef T1 first_type;
		typedef T2 second_type;
		T1 first;
		T2 second;
		pair(): first(), second() {}
		pair(T1 const& t1, T2 const& t2): first(t1), second(t2) {}

		template <class U1, class U2>
		pair(const pair<U1, U2>& p): first(p.first), second(p.second) {}

		pair& operator=(pair const& p) {
			first = p.first;
			second = p.second;
			return *this;
		}

		void swap(pair& p) {
			std::swap(first,  p.first);
			std::swap(second, p.second);
		}
	};

	template <class T1, class T2>
	inline bool operator==(const pair<T1, T2>& x, const pair<T1, T2>& y) {
		return x.first == y.first && x.second == y.second;
	}

	template <class T1, class T2>
	inline bool operator!=(const pair<T1, T2>& x, const pair<T1, T2>& y) {
		return !(x == y);
	}

	template <class T1, class T2>
	inline bool operator< (const pair<T1, T2>& x, const pair<T1, T2>& y) {
		return x.first < y.first || (!(y.first < x.first) && x.second < y.second);
	}

	template <class T1, class T2>
	inline bool operator> (const pair<T1, T2>& x, const pair<T1, T2>& y) {
		return y < x;
	}

	template <class T1, class T2>
	inline bool operator>=(const pair<T1, T2>& x, const pair<T1, T2>& y) {
		return !(x < y);
	}

	template <class T1, class T2>
	inline bool operator<=(const pair<T1, T2>& x, const pair<T1, T2>& y) {
		return !(y < x);
	}

	template <class T1, class T2>
	inline pair<T1, T2> make_pair(T1 x, T2 y) {
		return pair<T1, T2>(x, y);
	}
}

namespace std {
	template <class T, class A>
	void swap(ft::Vector<T, A> &v1, ft::Vector<T, A> &v2 ) {
		v1.swap(v2);
	}

	template <class Key, class T, class Compare, class A>
	void swap(ft::Map<Key, T, Compare, A> &m1, ft::Map<Key, T, Compare, A> &m2 ) {
		m1.swap(m2);
	}
}

#endif
