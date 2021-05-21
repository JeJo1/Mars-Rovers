#pragma once
#include "Node.h"
#include "QueueADT.h"

template <typename T>
class Queue : public QueueADT<T> {
private:
	Node<T>* head;
	Node<T>* tail;
public:

	Queue() {
		head = NULL;
		tail = NULL;
	}

	Queue(const Queue& rhs) {
		if (!rhs.head) {
			tail = head = NULL;
			return;
		}

		head = new Node<T>(NULL, rhs.head->getData());

		Node<T>* ptr1 = head, * ptr2 = rhs.head;

		while (ptr2 = ptr2->getNext()) {
			ptr1->setNext(new Node<T>(NULL, ptr2->getData()));
			ptr1 = ptr1->getNext();
		}

		tail = ptr1;
	}

	bool enqueue(T* itm) {
		if (!tail) {
			tail = head = new Node<T>;
			tail->setData(itm);
			return true;
		}

		tail->setNext(new Node<T>(NULL, itm));
		tail = tail->getNext();

		return true;  //today on the topic of things that are useless but we do them anyways
	}

	bool dequeue(T*& itm) {
		if (!head)
			return false;

		itm = head->getData();

		if (head == tail)
			tail = NULL;

		Node<T>* temp = head->getNext();
		delete head;
		head = temp;
		return true;

	}

	bool peek(T*& itm) const {
		if (!head)
			return false;

		itm = head->getData();
		return true;
	}

	bool isEmpty() const {
		return head == NULL;
	}

	~Queue() {
		Node<T>* temp;
		while (head) {
			temp = head->getNext();
			delete head;
			head = temp;
		}
	}

};
