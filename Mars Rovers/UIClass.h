#pragma once
#include <iostream>
using namespace std;
#include<windows.h>
#include "MarsStation.h"
class UIClass {
private:
	int mode;
	MarsStation* MarsStationPtr;
public:
	UIClass(MarsStation* MarsStationPtr):MarsStationPtr(MarsStationPtr)
	{
		mode = 1;
	}
	int SelectMode()
	{
		cout << "Enter Mode: " << endl;
		cin >> mode;
		return mode;
	}
	void Ready()
	{
		if (mode == 1)
		{
			cin.ignore();
			return; 
		}
		else if (mode == 2)
		{
			Sleep(1000);
			return;
		}
		else if (mode == 3)
			return;
	}
	void Output()
	{
		Mission* mm;
		PriorityQueue<EmergencyMission> EMWL = MarsStationPtr->getEMWL();	//Emergency Missions Waiting List
		List<MountainousMission> MMWL = MarsStationPtr->getMMWL();			//Mountainous Missions Waiting List
		Queue<PolarMission> PMWL = MarsStationPtr->getPMWL();				//Polar Missions Waiting List
		List<Mission> MPL = MarsStationPtr->getMPL();						//Missions in Progress List
		Queue<Mission> CML = MarsStationPtr->getCML();						//Completed Missions List
		Queue<EmergencyRover> eRWL = MarsStationPtr->getERWL();				//Emergency Rovers Waiting List
		Queue<MountainousRover> mRWL = MarsStationPtr->getMRWL();			//Mountainous Rovers Waiting List
		Queue<PolarRover> pRWL = MarsStationPtr->getPRWL();					//Polar Rovers Waiting List
		Queue<EmergencyRover> eRCL = MarsStationPtr->getERCL();				//Emergency Rovers Checkup List
		Queue<MountainousRover> mRCL = MarsStationPtr->getMRCL();			//Mountainous Rovers Checkup List
		Queue<PolarRover> pRCL = MarsStationPtr->getPRCL();	             	//Polar Rovers Checkup List
		List<Rover> RPL = MarsStationPtr->getRPL();
		EmergencyMission* eM;
		MountainousMission* mM;
		PolarMission* pM;
		EmergencyRover* eR;
		MountainousRover* mR;
		PolarRover* pR;
		cout << "Current Day: " << MarsStationPtr->getCurrentday() << endl;
		int Mnum = MarsStationPtr->getMMWLnum(); int Enum = MarsStationPtr->getEMWLnum(); int Pnum = MarsStationPtr->getPMWLnum();
		int totalWaiting = Mnum + Enum + Pnum;
		cout << totalWaiting << " Waiting Missions: [";
		while (EMWL.dequeue(eM))
		{
			cout << eM->getID();
			if (EMWL.peek(eM))
				cout << ",";
		}
		cout << "] (";
		while (PMWL.dequeue(pM))
		{
			cout << pM->getID();
			if (PMWL.peek(pM))
				cout << ",";
		}
		cout << ") {";
		for (int i = 0; i < Mnum - 1; i++)
		{
			cout << MMWL.getItemAt(i)->getID() << ",";
		}
		if (Mnum != 0) {
			cout << MMWL.getItemAt(Mnum - 1)->getID();
		}
		cout << "}" << endl;
		cout << "-----------------------------------------------------------------------------------" << endl;
		int countMPL = MPL.getLength();
		cout << countMPL << " In-Excution Mission/Rover: [";
		countMPL--;
		for (int i = 0; i < countMPL; i++)
		{
			if (dynamic_cast<EmergencyMission*>(MPL.getItemAt(i)))
			{
				cout << MPL.getItemAt(i)->getID() << "/" << RPL.getItemAt(i)->getN() << ",";
			}
		}
		if (dynamic_cast<EmergencyMission*>(MPL.getItemAt(countMPL)))
			cout << MPL.getItemAt(countMPL)->getID() << "/" << RPL.getItemAt(countMPL)->getN();
		cout << "] (";

		for (int i = 0; i < countMPL; i++)
		{
			if (dynamic_cast<PolarMission*>(MPL.getItemAt(i)))
				cout << MPL.getItemAt(i)->getID() << "/" << RPL.getItemAt(i)->getN() << ",";
		}
		if (dynamic_cast<PolarMission*>(MPL.getItemAt(countMPL)))
			cout << MPL.getItemAt(countMPL)->getID() << "/" << RPL.getItemAt(countMPL)->getN();
		cout << ") {";
		for (int i = 0; i < countMPL; i++)
		{
			if (dynamic_cast<MountainousMission*>(MPL.getItemAt(i)))
				cout << MPL.getItemAt(i)->getID() << "/" << RPL.getItemAt(i)->getN() << ",";
		}
		if (dynamic_cast<MountainousMission*>(MPL.getItemAt(countMPL)))
			cout << MPL.getItemAt(countMPL)->getID() << "/" << RPL.getItemAt(countMPL)->getN();
		cout << "}" << endl;
		cout << "-----------------------------------------------------------------------------------" << endl;
		cout << eRWL.getLength() + pRWL.getLength() + mRCL.getLength() << " Available Rover: [";
		while (eRWL.dequeue(eR))
		{
			cout << eR->getID();
			if (eRWL.peek(eR))
				cout << ",";
		}
		cout << "] (";
		while (mRWL.dequeue(mR))
		{
			cout << mR->getID();
			if (mRWL.peek(mR))
				cout << ",";
		}
		cout << ") {";
		while (mRCL.dequeue(mR))
		{
			cout << eR->getID();
			if (mRCL.peek(mR))
				cout << ",";
		}
		cout << "}" << endl;
		cout << "-----------------------------------------------------------------------------------" << endl;
		cout << eRCL.getLength() + pRCL.getLength() + mRWL.getLength() << " In-Checkup Rover: [";
		while (eRCL.dequeue(eR))
		{
			cout << eR->getID();
			if (eRCL.peek(eR))
				cout << ",";
		}
		cout << "] (";
		while (pRCL.dequeue(pR))
		{
			cout << pR->getID();
			if (pRCL.peek(pR))
				cout << ",";
		}
		cout << ") {";
		while (mRCL.dequeue(mR))
		{
			cout << mR->getID();
			if (mRCL.peek(mR))
				cout << ",";
		}
		cout << "}" << endl;
		cout << "-----------------------------------------------------------------------------------" << endl;
		cout << CML.getLength() << " Completed Missions: [";
		while (CML.dequeue(mm))
		{
			if (dynamic_cast<EmergencyMission*>(mm))
				cout << mm->getID();
			if (CML.peek(mm) && dynamic_cast<EmergencyMission*>(mm))
				cout << ",";
		}
		cout << "] (";
		while (CML.dequeue(mm))
		{
			if (dynamic_cast<PolarMission*>(mm))
				cout << mm->getID();
			if (CML.peek(mm) && dynamic_cast<PolarMission*>(mm))
				cout << ",";
		}
		cout << ") {";
		while (CML.dequeue(mm))
		{
			if (dynamic_cast<MountainousMission*>(mm))
				cout << mm->getID();
			if (CML.peek(mm) && dynamic_cast<MountainousMission*>(mm))
				cout << ",";
		}
		cout << "}" << endl;
	}
	
};