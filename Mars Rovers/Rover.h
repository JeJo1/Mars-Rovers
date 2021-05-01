#pragma once
#include "Mission.h"

class Rover {
private:
	Mission* m;
	static int N; //number of missions the rover completes before performing a checkup
	int Mission_Count,
	Checkup_Start_Day;
public:
	Rover() 
	{
		m = NULL;
		Mission_Count = 0;
		Checkup_Start_Day = -1;
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

	bool operator <= (Rover obj) 
	{
		return *m <= *obj.m;
	}

	virtual ~Rover(){}
};