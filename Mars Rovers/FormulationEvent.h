#pragma once
#include "Event.h"

class FormulationEvent : public Event
{
private:
	char Typ;    //The mission type
	int TLoc;    //The missionís target location (in kilometers from the base station)
	int MDut;    //Mission duration 
	int sig;     //The missionís significance
public:
	FormulationEvent(int EventDay, int ID, char Typ, int TLoc, int MDut, int sig)
		:Event(EventDay, ID), Typ(Typ), TLoc(TLoc), MDut(MDut), sig(sig)
	{
	};

	~FormulationEvent()
	{};

	void Excute()
	{

	}
};
