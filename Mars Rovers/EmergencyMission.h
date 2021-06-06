#pragma once
#include "Mission.h"

class EmergencyMission : public Mission 
{
private:
	double priority;
	static int Count;

public:
	EmergencyMission(int Formulation_Day, int ID, int Target_Location, int Mission_Duration, int Significance)
		:Mission(Formulation_Day, ID, Target_Location, Mission_Duration, Significance)
	{
		Count++;
		priority = (Significance * (1 / Formulation_Day) * (Mission_Duration * Target_Location));
		priority = priority / 1000;
		//TODO: Construct a priority Eqn and set the priority
		//priority = -1;
	};

	~EmergencyMission() 
	{
		Count--;
	};

	double getPriority() const
	{
		return priority;
	}

	static void setCount(int n)
	{
		Count = n;
	}

	static int getCount() 
	{
		return Count;
	}
};