#pragma once
#include"Event.h"
#include "MarsStation.h"

class PrompteEvent :public Event
{
public:
	PrompteEvent(int EventDay, int ID) :Event(EventDay, ID)
	{};

	~PrompteEvent()
	{};

	void Excute()
	{

	}
};