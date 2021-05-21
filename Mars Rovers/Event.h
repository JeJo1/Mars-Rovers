#pragma once
#include"DataStructures/List.h"
#include"DataStructures/Queue.h"
#include"DataStructures/PriorityQueue.h"
class MarsStation;

class Event
{
private:
	int EventDay;   //The event day
	int ID;        //The ID of the mission
protected:
	static MarsStation* m;
public:
	Event(int EventDay, int ID) :EventDay(EventDay), ID(ID)
	{}

	static void setStation(MarsStation* ptr) 
	{
		m = ptr;
	}

	int getED()
	{
		return EventDay;
	}

	int getID()
	{
		return ID;
	}

	virtual void Execute() = 0;
	virtual ~Event() {};
};