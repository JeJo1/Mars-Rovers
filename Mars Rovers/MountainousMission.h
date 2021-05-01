#pragma once
#include "Mission.h"

class MountainousMission : public Mission
{
private:
	static int Count;
	static int PromotedCount;
	static int AutoPromotion;

public:
	MountainousMission(int Formulation_Day, int ID, int Target_Location, int Mission_Duration, int Significance)
		:Mission(Formulation_Day, ID, Target_Location, Mission_Duration, Significance)
	{
		Count++;
	};

	~MountainousMission()
	{
		Count--;
	};

	void Promote() {
		PromotedCount++;
	}

	static int getCount() {
		return Count;
	}
	
	// TODO: Getter for rest of data members;

};
