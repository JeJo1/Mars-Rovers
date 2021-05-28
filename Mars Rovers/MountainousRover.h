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

	static void setCM(int n)
	{
		CM = n;
	}

	static void setCount(int n)
	{
		Count = n;
	}

	static void setSM(int n)
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
		double days = 2.0 * (double)newm->getTLOC() / ((double) SM * 25.0);

		if (days - (int)days)
			days = days + 1.0;

		newm->setED(newm->getMDUR() + (int)days);
	}
};