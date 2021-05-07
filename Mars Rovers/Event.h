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
	MarsStation* m;
public:
	Event(int EventDay, int ID) :EventDay(EventDay), ID(ID)
	{
	};

	int getED()
	{
		return EventDay;
	}

	int getID()
	{
		return ID;
	}
	virtual void Excute() = 0;
};