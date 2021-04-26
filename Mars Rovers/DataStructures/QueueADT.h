#pragma once

template <typename T>
class QueueADT {
public:
	virtual bool enqueue(T*) = 0;
	virtual bool dequeue(T*&) = 0;
	virtual bool peek(T*&) const = 0;
	virtual bool isEmpty() const = 0;
	virtual ~QueueADT() {};
};