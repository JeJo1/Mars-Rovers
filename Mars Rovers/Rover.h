#pragma once
#include "Mission.h"

class Rover {
private:
	Mission* m;
	static int N; //number of missions the rover completes before performing a checkup
	int Mission_Count,
	Checkup_Start_Day;
	static int Count;
	int ID;
public:
	Rover() 
	{
		ID = ++Count;
		m = NULL;
		Mission_Count = 0;
		Checkup_Start_Day = -1;
	}

	static int getCount() {
		return Count;
	}

	void IncrementMissionCount() 
	{
		Mission_Count++;
	}

	void ResetMissionCount() 
	{
		Mission_Count = 0;
	}

	void assign(Mission* newm) 
	{
		m = newm;
	}

	static void setN(int n) {
		N = n;
	}

	static int getN() 
	{
		return N;
	}

	void setCheckupStartDay(int n) 
	{
		Checkup_Start_Day = n;
	}

	int getCheckupStartDay() const 
	{
		return Checkup_Start_Day;
	}

	Mission* getMission() const 
	{
		return m;
	}

	int getMissionCount() const {
		return Mission_Count;
	}

	bool operator <= (const Rover& obj) const
	{
		return *m <= *obj.m;
	}

	int getID() {
		return ID;
	}

	virtual ~Rover(){}
};