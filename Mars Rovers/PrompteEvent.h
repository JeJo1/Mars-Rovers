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
		MountainousMission* ptr = m->getMMWL().remove(getID());
		if (ptr == NULL)
			return;
		else
		{
			ptr->Promote();
			EmergencyMission* em = new EmergencyMission(getED(), getID(),em->getTLOC(),em->getMDUR(),em->getSIG());
			m->getEMWL().enqueue(em, em->getPriority());
		}
	}
};