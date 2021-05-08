#pragma once
#include "Event.h"
#include "MarsStation.h"

class FormulationEvent : public Event
{
private:
	char Typ;    //The mission type
	int TLoc;    //The missionís target location (in kilometers from the base station)
	int MDut;    //Mission duration 
	int sig;     //The missionís significance
public:
	FormulationEvent(int EventDay, int ID, char Typ, int TLoc, int MDut, int sig)
		:Event(EventDay, ID ,m), Typ(Typ), TLoc(TLoc), MDut(MDut), sig(sig)
	{};

	~FormulationEvent()
	{};

	void Excute()
	{
		if (Typ == 'M')
		{
			MountainousMission* mm = new MountainousMission(getED(),getID(),TLoc,MDut,sig);
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
