#pragma once
#include "Event.h"

class CancelEvent : public Event
{
public:
	CancelEvent(int EventDay, int ID) :Event(EventDay, ID)
	{};

	~CancelEvent()
	{};

	void Excute()
	{	
		m->getMMWL().remove(getID());
	}
};