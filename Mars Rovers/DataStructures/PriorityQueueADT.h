#pragma once
 
template <typename T>
class PriorityQueueADT {
public:
	virtual bool enqueue(T*, int) = 0;
	virtual bool dequeue(T*&) = 0;
	virtual bool peek(T*&) const = 0;
	virtual bool isEmpty() const = 0;
	virtual ~PriorityQueueADT() {};
};