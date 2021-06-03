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

	static void Promote() 
	{
		PromotedCount++;
	}

	static void setCount(int n)
	{
		Count = n;
	}

	static void setPromotedCount(int n)
	{
		PromotedCount = n;
	}

	static void setAutoP(int n)
	{
		AutoPromotion = n;
	}

	static int getCount()
	{
		return Count;
	}
	
	static int getPromotedCount() 
	{
		return PromotedCount;
	}

	static int getAutoP()
	{
		return AutoPromotion;
	}
};