#pragma once
#include "Event.h"
#include "MarsStation.h"

class CancelEvent : public Event
{
public:
	CancelEvent(int EventDay, int ID) :Event(EventDay, ID, m)
	{};

	~CancelEvent()
	{};

	void Excute()
	{	
		MountainousMission* ptr = m->getMMWL().remove(getID());
		if (ptr != NULL)
			delete ptr;
		else
			return;
	}
};