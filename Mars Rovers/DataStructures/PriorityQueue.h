#pragma once
#include "Node.h"
#include "PriorityQueueADT.h"

template <typename T>
class PriorityQueue : public PriorityQueueADT<T> {
private:
	Node<T>* head;
public:

	PriorityQueue() {
		head = NULL;
	}

	bool enqueue(T* itm, int priority) {
		if (!head) {
			head = new Node<T>;
			head->setData(itm);
			head->setPriority(priority);
			return true;
		}

		if (priority > head->getPriority()) {
			head = new Node<T>(head, itm);
			head->setPriority(priority);
			return true;
		}

		Node<T>* ptr = head;

		while (ptr->getNext() && ptr->getNext()->getPriority() >= priority)
			ptr = ptr->getNext();

		ptr->setNext(new Node<T>(ptr->getNext(), itm));
		ptr->getNext()->setPriority(priority);

		return true;
	}

	bool dequeue(T*& itm) {
		if (!head)
			return false;

		itm = head->getData();

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

	~PriorityQueue(){
		Node<T>* temp;
			while (head) {
				temp = head->getNext();
				delete head;
				head = temp;
			}
	}

};