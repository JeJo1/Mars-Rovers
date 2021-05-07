#pragma once

#include "DataStructures\List.h"
#include "DataStructures\Queue.h"
#include "DataStructures\PriorityQueue.h"

#include "Event.h"
#include "EmergencyMission.h"
#include "MountainousMission.h"
#include "PolarMission.h"
#include "EmergencyRover.h"
#include "MountainousRover.h"
#include "PolarRover.h"


class Event;//


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
	int currentDay;
public:
	MarsStation() 
	{
		MountainousMission* m = new MountainousMission(1, 1, 1, 1, 1);
		MountainousMission* m2 = new MountainousMission(6, 3, 1, 1, 1);
		std::cout << mMWL.getLength() << std::endl;
		mMWL.insertLast(m);
		mMWL.insertLast(m2);
		std::cout << mMWL.getLength() << std::endl;
		mMWL.remove(2);
		std::cout << mMWL.getLength() << std::endl;
		mMWL.remove(3);
		std::cout << mMWL.getLength() << std::endl;
		MountainousMission* ptr = mMWL.remove(1);
		std::cout << m << std:: endl;
		std::cout << ptr << std::endl;
		std::cout << mMWL.getLength() << std::endl;


		Rover r1, r2;
		r1.assign(m);
		r2.assign(m2);

		std::cout << RPL.getLength() << std::endl;
		RPL.insert(&r1);
		RPL.insert(&r2);
		

		Rover* ptr1 = RPL.removeFirst();
		std::cout << RPL.getLength() << std::endl;
		std::cout << ptr1 << std::endl;
		std::cout << &r1 << std::endl;
		RPL.removeFirst();

		std::cout << RPL.getLength() << std::endl;//del


		currentDay = 0;

	}

	PriorityQueue<EmergencyMission>& getEMWL()
	{
		return eMWL;
	}

	List<MountainousMission>& getMMWL()
	{
		return mMWL;
	}

	Queue<PolarMission>& getPMWL()
	{
		return pMWL;
	}


};