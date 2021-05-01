#pragma once
#include <iostream>
class Rover;//

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
		//r->assign(this);
	}

	void setWaitingDays(int newWaiting_Days)
	{
		Waiting_Days = newWaiting_Days;
	}

	void setExecutionDays(int newExecution_Days)
	{
		Execution_Days = newExecution_Days;
	}

	bool operator <= (Mission obj) 
	{
		return Formulation_Day + Waiting_Days + Execution_Days <= obj.Formulation_Day + obj.Waiting_Days + obj.Execution_Days;
	}

	bool operator == (int id) {
		return ID == id;
	}

	//TODO: Getter funcions for all data memebers
};