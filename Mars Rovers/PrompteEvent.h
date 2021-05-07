#pragma once
#include"Event.h"

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