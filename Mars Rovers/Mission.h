#pragma once
class Mission
{
private:
	//rover* r = NULL;
	int Fomrulation_Day, ID, Mission_Duration, Waiting_Days, Target_Location, Significance, Execution_Days;
public:
	Mission() 
	{
	}
	~Mission()
	{
	}
	/*void assign(rover* assigned_r)
	{
	r = assigned_r;
	}*/
	void IncrementWaitingDays()
	{
	Waiting_Days++;
	}
};