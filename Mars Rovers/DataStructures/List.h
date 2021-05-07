#pragma once
#include "Node.h"
#include "ListAdt.h"


template <typename T>
class List: public ListADT<T> {
private:

	Node<T>* head;

	Node<T>* getNodeAt(int pos)const {
		if (pos < 0)
			return NULL;

		if (pos == 0||!head)
			return head;

		Node<T>* ptr = head->getNext();

		for (int i = 1; i < pos && ptr; i++, ptr = ptr->getNext()) {}

		return ptr;
	}

public:

	List() {
		head = NULL;
	}

	bool isEmpty() {
		return head == NULL;
	}

	int getLength() const {
		if (!head)
			return 0;

		int count = 1;

		Node<T>* ptr = head->getNext();

		while (ptr) {
			count++;
			ptr = ptr->getNext();
		}

		return count;
	}



	/*int getPositionOf(T* itm) const {
		if (!head)
			return -1;

		if (head->getData() == itm) 
			return 0;
		
		Node<T>* ptr = head->getNext();

		int count = 1;

		while (ptr) {
			if (ptr->getData() == itm)
				return count;
			count++;
			ptr = ptr->getNext();
		}

		return -1;
	}*/

	T* peekFirst() const {
		if (!head)
			return NULL;
		return head->getData();
	}

	T* removeFirst() {
		T* data = NULL;
		if (!head)
			return data;
		data = head->getData();
		Node<T>* temp = head->getNext();
		delete head;
		head = temp;
		return data;
	}

	T* getItemAt(int pos) const {
		Node<T>* ptr = getNodeAt(pos);

		if (!ptr)
			return NULL;

		return ptr->getData();
	}

	void insert(T* itm) {
		if (!head) {
			head = new Node<T>;
			head->setData(itm);
			return;
		}

		if (!(*head->getData() <= *itm)) {
			head = new Node<T>(head,itm);
			return;
		}

		Node<T>* ptr = head;

		while (ptr->getNext() && *ptr->getNext()->getData() <= *itm)
			ptr = ptr->getNext();

		ptr->setNext(new Node<T>(ptr->getNext(), itm));
	}

	void insertLast(T* itm) {
		if (!head) {
			head = new Node<T>;
			head->setData(itm);
			return;
		}
		
		Node<T>* ptr = head;
		while (ptr->getNext())
			ptr = ptr->getNext();

		ptr->setNext(new Node<T>(NULL, itm));
	}

	template <typename U>
	T* remove(const U& itm) {
		T* data = NULL;
		if (!head)
			return data;

		Node <T>* temp;

		if (*head->getData() == itm) {
			data = head->getData();
			temp = head->getNext();
			delete head;
			head = temp;
			return data;
		}

		Node<T>* ptr = head;

		while (ptr->getNext()) {
			if (*ptr->getNext()->getData() == itm) {
				data = ptr->getNext()->getData();
				temp = ptr->getNext();
				ptr->setNext(temp->getNext());
				delete temp;
				return data;
			}
			ptr = ptr->getNext();
		}

		return data;
	}

	/*bool removeAt(int pos) {
		if (!head)
			return false;

		Node<T>* temp;

		if (pos == 0) {
			temp = head->getNext();
			delete head;
			head = temp;
			return true;
		}

		Node<T>* ptr = getNodeAt(pos - 1);

		if (!ptr || !ptr->getNext())
			return false;

		temp = ptr->getNext();

		ptr->setNext(temp->getNext());

		delete temp;

		return true;
	}*/

	~List() {
		Node<T>* temp;
		while (head) {
			temp = head->getNext();
			delete head;
			head = temp;
		}

	}
};