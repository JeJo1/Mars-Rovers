#pragma once
#include <iostream>
template <typename T>
class Node {
private:

	Node<T>* next;
	T* data;
	int priority;

public:

	Node(Node<T>* newNext = NULL, T* newData = NULL) {
		next = newNext;
		data = newData;
		priority = 0;
	}

	Node<T>* getNext() const {
		return next;
	}

	void setNext(Node<T>* newNext) {
		next = newNext;
	}

	T* getData() const {
		return data;
	}

	void setData(T* newData) {
		data = newData;
	}

	int getPriority() const {
		return priority;
	}

	void setPriority(int newPriority) {
		priority = newPriority;
	}

};