#pragma once
#include <list>
#include <iostream>

template <typename T>
class Node {
private:
	size_t pow;
	T koef;

public:
	Node() {
		pow = 0;
		koef = 0;
	}
	Node(T p1, T k1) {
		pow = p1; koef = k1;
	}
	~Node() {}

	size_t power();
	T koeficient();

	bool operator>(const Node &p2) {
		return pow > p2.pow;
	}

	bool operator>=(const Node p2) {
		return pow >= p2.pow;
	}

	bool operator < (const Node p2) {
		return pow < p2.pow;
	}

	bool operator <= (const Node p2) {
		return pow <= p2.pow;
	}

	bool operator == (const Node p2) {
		return pow == p2.pow;
	}

	bool operator != (const Node p2) {
		return pow != p2.pow;
	}

	Node operator + (const Node p2) {
			if (pow != p2.pow)
				throw std::logic_error("Can't add monominals with different powers");
			else {
				Node res(pow, koef + p2.koef);
				return res;
			}
	}

	Node operator - (const Node p2) {
			if (pow != p2.pow)
				throw std::logic_error("Can't substract monominals with different powers");
			else {
				Node res(pow, koef - p2.koef);
				return res;
			}
		}

	void operator = (const Node &p2) {
		pow = p2.pow;
		koef = p2.koef;
	}
};

template <typename T>
class Field {
private:
	std::list<Node<T>> poly;

public:
	Field() {}
	~Field() {}

	void addNode(Node<T>);

	Node<T> operator [] (const int i) {

			if (i < 0 || i >= poly.size())
				throw std::out_of_range("Index out of range");

			int j = 0;
			for (auto it = poly.begin(); it != poly.end(); ++it)
			{
				if (i == j)
					return *it;
				j++;
			}	
	}
};

template <typename T>
size_t Node<T>::power() {
	return pow;
}

template <typename T>
T Node<T>::koeficient() {
	return koef;
}

template <typename T>
void Field<T>::addNode(Node<T> p) {
	poly.push_back(p);
}

template <typename T>
std::ostream& operator<<(std::ostream& os, Node<T>& p) {
	return os << '{' << p.power() << ", " << p.koeficient() << '}';
}
