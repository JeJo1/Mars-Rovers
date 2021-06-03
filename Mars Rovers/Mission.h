#pragma once
#include <iostream>
class Rover;

class Mission
{
private:
	Rover* r;
	int Formulation_Day,
		ID,
		Target_Location,
		Mission_Duration,
		Significance,
		Waiting_Days,
		Execution_Days;
public:
	Mission(int Formulation_Day, int ID, int Target_Location, int Mission_Duration, int Significance)
		:Formulation_Day(Formulation_Day), ID(ID), Target_Location(Target_Location), Mission_Duration(Mission_Duration), Significance(Significance), r(NULL)
	{
		Waiting_Days = Execution_Days = 0;
	}

	virtual ~Mission() {}

	void assign(Rover* assigned_r)
	{
		r = assigned_r;
	}

	void setWD(int newWaiting_Days)
	{
		Waiting_Days = newWaiting_Days;
	}

	void setED(int newExecution_Days)
	{
		Execution_Days = newExecution_Days;
	}

	bool operator <= (const Mission& obj) const
	{
		if (Formulation_Day + Waiting_Days + Execution_Days < obj.Formulation_Day + obj.Waiting_Days + obj.Execution_Days)
			return true;
		if (Formulation_Day + Waiting_Days + Execution_Days > obj.Formulation_Day + obj.Waiting_Days + obj.Execution_Days)
			return false;
		return Formulation_Day <= obj.Formulation_Day;
	}

	bool operator == (int id) const
	{
		return ID == id;
	}

	bool operator == (const Mission& obj) const {
		return ID == obj.ID;
	}

	int getFD() const
	{
		return Formulation_Day;
	}

	int getID() const
	{
		return ID;
	}

	int getTLOC() const 
	{
		return Target_Location;
	}

	int getMDUR() const
	{
		return Mission_Duration;
	}

	int getSIG() const
	{
		return Significance;
	}

	int getWD() const
	{
		return Waiting_Days;
	}

	int getED() const
	{
		return Execution_Days;
	}

	int getCD() const {
		return Formulation_Day + Waiting_Days + Execution_Days;
	}
};