#pragma once
#include "Rover.h"

class EmergencyRover :public Rover {
private:
	static int CE;
	static int Count;
	static int SE;
public:

	EmergencyRover() 
	{
		Count ++;
	}

	void setCE(int n)
	{
		CE = n;
	}

	void setCount(int n)
	{
		Count = n;
	}

	void setSE(int n)
	{
		SE = n;
	}

	static int getCE()
	{
		return CE;
	}

	static int getCount()
	{
		return Count;
	}

	static int getSE()
	{
		return SE;
	}

	void assign(Mission* newm)
	{
		Rover::assign(newm);
		newm->assign(this);
		double days = 2.0 * ((double)newm->getTLOC() * 25.0 / (double)SE);

		if (days - (int)days != 0)
			days = days + 1.0;

		newm->setED(newm->getMDUR() + days);
	}
};