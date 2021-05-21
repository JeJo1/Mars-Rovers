#pragma once
#include "Event.h"
#include "MarsStation.h"

class CancelationEvent : public Event
{
public:
	CancelationEvent(int EventDay, int ID) :Event(EventDay, ID)
	{};

	~CancelationEvent()
	{};

	void Execute()
	{	
		MountainousMission* ptr = m->getMMWL().remove(getID());
		if (ptr != NULL)
			delete ptr;
		else
			return;
	}
};