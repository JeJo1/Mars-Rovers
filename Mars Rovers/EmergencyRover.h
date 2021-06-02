#pragma once
#include "Rover.h"

class EmergencyRover :public Rover {
private:
	static int CE; 
	static int Count;
	static int SE;
	int ID;
public:

	EmergencyRover() 
	{
		ID=++Count;
	}

	static void setCE(int n)
	{
		CE = n;
	}

	static void setCount(int n)
	{
		Count = n;
	}

	static void setSE(int n)
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
		double days = 2.0 * (double)newm->getTLOC() / ((double)SE * 25.0);

		if (days - (int)days)
			days = days + 1.0;

		newm->setED(newm->getMDUR() + (int)days);
	}
	int getID()const
	{
		return ID;
	}
};