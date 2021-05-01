#pragma once

#include "DataStructures\List.h"
#include "DataStructures\Queue.h"
#include "DataStructures\PriorityQueue.h"

//#include "Event.h"
#include "EmergencyMission.h"
#include "MountainousMission.h"
#include "PolarMission.h"
//#include "EmergencyRover.h"
//#include "MountainousRover.h"
//#include "PolarRover.h"


class Rover;//
class Event;//
class EmergencyRover;//
class MountainousRover;//
class PolarRover;//


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
	//List<Rover> RPL;						//Rovers in Progress List
	int currentDay;
public:
	MarsStation() 
	{
		currentDay = 0;
	}
};