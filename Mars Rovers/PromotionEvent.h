#pragma once
#include"Event.h"
#include "MarsStation.h"

class PromotionEvent :public Event
{
public:
	PromotionEvent(int EventDay, int ID) :Event(EventDay, ID)
	{};

	~PromotionEvent()
	{};

	void Execute()
	{
		MountainousMission* ptr = m->getMMWL().remove(getID());
		if (ptr)
		{
			EmergencyMission* em = new EmergencyMission(ptr->getFD(), getID(), ptr->getTLOC(), ptr->getMDUR(), ptr->getSIG());
			m->getEMWL().enqueue(em, em->getPriority());
			delete ptr;
		}
	}
};