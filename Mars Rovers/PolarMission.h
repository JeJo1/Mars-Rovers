#pragma once
#include "Mission.h"

class PolarMission : public Mission
{
private:
	static int Count;
public:
	PolarMission(int Formulation_Day, int ID, int Target_Location, int Mission_Duration, int Significance)
		:Mission(Formulation_Day, ID, Target_Location, Mission_Duration, Significance)
	{
		Count++;
	}
	~PolarMission()
	{
		Count--;
	};

	static int getCount() {
		return Count;
	}
};