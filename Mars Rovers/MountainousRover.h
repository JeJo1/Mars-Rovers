#pragma once
#include "Rover.h"

class MountainousRover :public Rover {
private:
	static int CM;
	static int Count;
	static int SM;
public:

	MountainousRover()
	{
		Count++;
	}

	void setCM(int n)
	{
		CM = n;
	}

	void setCount(int n)
	{
		Count = n;
	}

	void setSM(int n)
	{
		SM = n;
	}

	static int getCM()
	{
		return CM;
	}

	static int getCount()
	{
		return Count;
	}

	static int getSM()
	{
		return SM;
	}

	void assign(Mission* newm)
	{
		Rover::assign(newm);
		newm->assign(this);
		double days = 2.0 * ((double)newm->getTLOC() * 25.0 / (double)SM);

		if (days - (int)days != 0)
			days = days + 1.0;

		newm->setED(newm->getMDUR() + days);
	}
};