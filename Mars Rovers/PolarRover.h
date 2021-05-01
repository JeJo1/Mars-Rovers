#pragma once
#include "Rover.h"

class PolarRover :public Rover {
private:
	static int CP;
	static int Count;
	static int SP;
public:

	PolarRover()
	{
		Count++;
	}

	void setCP(int n)
	{
		CP = n;
	}

	void setCount(int n)
	{
		Count = n;
	}

	void setSP(int n)
	{
		SP = n;
	}

	static int getCP()
	{
		return CP;
	}

	static int getCount()
	{
		return Count;
	}

	static int getSP()
	{
		return SP;
	}

	void assign(Mission* newm)
	{
		Rover::assign(newm);
		newm->assign(this);
		double days = 2.0 * ((double)newm->getTLOC() * 25.0 / (double)SP);

		if (days - (int)days != 0)
			days = days + 1.0;

		newm->setED(newm->getMDUR() + days);
	}
};