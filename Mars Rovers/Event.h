#pragma once
#include"MarsStation.h"

class Event
{
private:
	int EventDay;   //The event day
	int ID;        //The ID of the mission
	MarsStation* m;
public:
	Event(int EventDay, int ID) :EventDay(EventDay), ID(ID)
	{};

	int getED()
	{
		return EventDay;
	}

	virtual void Excute() = 0;
};