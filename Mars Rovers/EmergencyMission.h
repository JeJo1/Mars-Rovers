#pragma once
#include "Mission.h"

class EmergencyMission : public Mission 
{
private:
	int priority;
	static int Count;

public:
	EmergencyMission(int Formulation_Day, int ID, int Target_Location, int Mission_Duration, int Significance)
		:Mission(Formulation_Day, ID, Target_Location, Mission_Duration, Significance)
	{
		Count++;
		//TODO: Construct a priority Eqn and set the priority
	};

	~EmergencyMission() 
	{
		Count--;
	};

	int getPriority() const
	{
		return priority;
	}

	void setCount(int n)
	{
		Count = n;
	}

	static int getCount() 
	{
		return Count;
	}
};