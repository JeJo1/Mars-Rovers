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

	PriorityQueue(const PriorityQueue& rhs) {
		if (!rhs.head) {
			head = NULL;
			return;
		}

		head = new Node<T>(NULL, rhs.head->getData());
		head->setPriority(rhs.head->getPriority());

		Node<T>* ptr1 = head, * ptr2 = rhs.head;

		while (ptr2 = ptr2->getNext()) {
			ptr1->setNext(new Node<T>(NULL, ptr2->getData()));
			ptr1 = ptr1->getNext();
			ptr1->setPriority(ptr2->getPriority());
		}
	}

	const PriorityQueue<T>& operator = (const PriorityQueue<T>& rhs) {
		if (this == &rhs)
			return rhs;

		~PriorityQueue();

		if (!rhs.head) {
			head = NULL;
			return rhs;
		}

		head = new Node<T>(NULL, rhs.head->getData());
		head->setPriority(rhs.head->getPriority());

		Node<T>* ptr1 = head, * ptr2 = rhs.head;

		while (ptr2 = ptr2->getNext()) {
			ptr1->setNext(new Node<T>(NULL, ptr2->getData()));
			ptr1 = ptr1->getNext();
			ptr1->setPriority(ptr2->getPriority());
		}
	}

	bool enqueue(T* itm, double priority) {
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
};