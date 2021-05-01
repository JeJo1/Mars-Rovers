#pragma once
#include "Mission.h"

class MountainousMission : public Mission
{
private:
	static int Count;
	static int PromotedCount;
	static int AutoPromotion;

public:
	MountainousMission() 
	{
	};
	~MountainousMission()
	{
	};

};
