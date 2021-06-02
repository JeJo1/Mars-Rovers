#pragma once

#include "Event.h"
#include "DataStructures\List.h"
#include "DataStructures\Queue.h"
#include "DataStructures\PriorityQueue.h"

#include "EmergencyMission.h"
#include "MountainousMission.h"
#include "PolarMission.h"
#include "EmergencyRover.h"
#include "MountainousRover.h"
#include "PolarRover.h"
class UIClass;

class MarsStation{
private:
	Queue<Event> Events;					//Events List
	PriorityQueue<EmergencyMission> eMWL;	//Emergency Missions Waiting List
	List<MountainousMission> mMWL;			//Mountainous Missions Waiting List
	Queue<PolarMission> pMWL;				//Polar Missions Waiting List
	List<Mission> MPL;						//Missions in Progress List
	Queue<Mission> CML;						//Completed Missions List
	Queue<EmergencyRover> eRWL;				//Emergency Rovers Waiting List
	Queue<MountainousRover> mRWL;			//Mountainous Rovers Waiting List
	Queue<PolarRover> pRWL;					//Polar Rovers Waiting List
	Queue<EmergencyRover> eRCL;				//Emergency Rovers Checkup List
	Queue<MountainousRover> mRCL;			//Mountainous Rovers Checkup List
	Queue<PolarRover> pRCL;					//Polar Rovers Checkup List
	List<Rover> RPL;						//Rovers in Progress List

	UIClass *UI;
	int currentDay;

	void readFile();
	void writeFile();

	void Return_From_Checkup();
	void Return_From_Missions();
	void Execute_Events();
	void Auto_Promote();
	void Assign_Missions();
	
public:
	MarsStation();

	~MarsStation();

	void mainfunc();
	bool isDone();

	PriorityQueue<EmergencyMission>& getEMWL();
	List<MountainousMission>& getMMWL();
	Queue<PolarMission>& getPMWL();
	List<Mission>& getMPL();
	List<Rover>& getRPL();
	Queue<Mission>& getCML();
	Queue<EmergencyRover>& getERWL();				//Emergency Rovers Waiting List
	Queue<MountainousRover>& getMRWL();
	Queue<PolarRover>& getPRWL();					
	Queue<EmergencyRover>& getERCL();				
	Queue<MountainousRover>& getMRCL();	
	Queue<PolarRover> & getPRCL();
	int getCurrentday();
	int getMMWLnum();
	int getPMWLnum();
	int getEMWLnum();
};