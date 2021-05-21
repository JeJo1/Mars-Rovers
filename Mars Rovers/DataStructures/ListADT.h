#pragma once

 template<typename T>
class ListADT {
public:
	virtual bool isEmpty() = 0;
	virtual int getLength() const = 0;
	//virtual int getPositionOf(T*) const = 0;
	virtual T* peekFirst() const = 0;
	virtual T* removeFirst() = 0;
	virtual T* getItemAt(int) const = 0;
	virtual void insert(T*) = 0;
	virtual void insertLast(T*) = 0;
	virtual bool removeAt(int) = 0;
	virtual ~ListADT() {};
};