#pragma once
#include <vector>

template <typename T>
class Node {
private: 
	T pow;
	T koef;

public: 
	Node(T p1, T k1) {
		pow = p1; koef = k1;
	}
	~Node();

	T power();
	T koeficient();

	bool operator > (const Node p1, const Node p2);
	bool operator >= (const Node p1, const Node p2);
	bool operator < (const Node p1, const Node p2);
	bool operator <= (const Node p1, const Node p2);
	bool operator == (const Node p1, const Node p2);
	bool operator != (const Node p1, const Node p2);
};

template <typename T>
class Field {
private: 
	std::vector<Node<T>> poly;

public:
	Field();
	~Field();

	Node<T> operator [] (int i);
};

template <typename T>
T Node<T>::power() {
	return pow;
}

template <typename T>
T Node<T>::koeficient() {
	return koef;
}

template <typename T>
bool Node<T>::operator > (const Node<T> p1, const Node<T> p2) {
	if (p1.pow > p2.pow) return true;
	else
		return false;
}

template <typename T>
bool Node<T>::operator >= (const Node<T> p1, const Node<T> p2) {
	if (p1.pow >= p2.pow) return true;
	else
		return false;
}


template <typename T>
bool Node<T>::operator < (const Node<T> p1, const Node<T> p2) {
	if (p1.pow < p2.pow) return true;
	else
		return false;
}



template <typename T>
bool Node<T>::operator <= (const Node<T> p1, const Node<T> p2) {
	if (p1.pow <= p2.pow) return true;
	else
		return false;
}

template <typename T>
bool Node<T>::operator == (const Node<T> p1, const Node<T> p2) {
	if (p1.pow == p2.pow) return true;
	else
		return false;
}

template <typename T>
bool Node<T>::operator != (const Node<T> p1, const Node<T> p2) {
	if (p1.pow != p2.pow) return true;
	else
		return false;
}


template <typename T>
Node<T> Field<T>::operator [] (int i) {
	return poly[i];
}

