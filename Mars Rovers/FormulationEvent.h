#pragma once
#include "Event.h"
#include "MarsStation.h"

class FormulationEvent : public Event
{
private:
	char Typ;    //The mission type
	int TLoc;    //The mission’s target location (in kilometers from the base station)
	int MDut;    //Mission duration 
	int sig;     //The mission’s significance
public:
	FormulationEvent(char Typ, int EventDay, int ID, int TLoc, int MDut, int sig)
		:Event(EventDay, ID), Typ(Typ), TLoc(TLoc), MDut(MDut), sig(sig)
	{};

	~FormulationEvent()
	{};

	void Execute()
	{
		if (Typ == 'M')
		{
			MountainousMission* mm = new MountainousMission(getED(), getID(), TLoc, MDut, sig);
			m->getMMWL().insertLast(mm);
		}
		else if (Typ == 'P')
		{
			PolarMission* pm = new PolarMission(getED(), getID(), TLoc, MDut, sig);
			m->getPMWL().enqueue(pm);
		}
		else if (Typ == 'E')
		{
			EmergencyMission* em = new EmergencyMission(getED(), getID(), TLoc, MDut, sig);
			m->getEMWL().enqueue(em,em->getPriority());
		}
	}
};