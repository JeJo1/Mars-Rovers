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

	static void setCP(int n)
	{
		CP = n;
	}

	static void setCount(int n)
	{
		Count = n;
	}

	static void setSP(int n)
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

		if (days - (int)days)
			days = days + 1.0;

		newm->setED(newm->getMDUR() + (int)days);
	}
};