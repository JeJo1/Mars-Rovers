#pragma once
#include <iostream>
#include<windows.h>
#include "MarsStation.h"

using namespace std;

class UIClass {
private:
	int mode;
	MarsStation* MarsStationPtr;
	bool once;
public:
	UIClass(MarsStation* MarsStationPtr) :MarsStationPtr(MarsStationPtr)
	{
		mode = 1;
		once = false;
	}
	void SelectMode()
	{
		cout << "Enter Mode: ";
		cin >> mode;
		cout << endl;
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
		if (mode == 1 || mode == 2)
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
			cout << totalWaiting << " Waiting Missions: ";
			if (!EMWL.isEmpty())
			{
				cout << "[";
				while (EMWL.dequeue(eM))
				{
					cout << eM->getID();
					if (EMWL.peek(eM))
						cout << ",";
				}
				cout << "] ";
			}
			if (!PMWL.isEmpty())
			{
				cout << "(";
				while (PMWL.dequeue(pM))
				{
					cout << pM->getID();
					if (PMWL.peek(pM))
						cout << ",";
				}
				cout << ") ";
			}
			if (!MMWL.isEmpty())
			{
				cout << "{";
				for (int i = 0; i < Mnum - 1; i++)
				{
					cout << MMWL.getItemAt(i)->getID() << ",";
				}
				if (Mnum != 0) {
					cout << MMWL.getItemAt(Mnum - 1)->getID();
				}
				cout << "}";
			}cout << endl;
			cout << "-----------------------------------------------------------------------------------" << endl;
			int countMPL = MPL.getLength();
			cout << countMPL << " In-Excution Mission/Rover: ";
			int ii = 0;
			while (ii < countMPL && !(dynamic_cast<EmergencyMission*>(MPL.getItemAt(ii))))
			{
				ii++;
			}
			if (ii != countMPL)
			{
				cout << "[" << MPL.getItemAt(ii)->getID() << "/" << RPL.getItemAt(ii)->getID();
				ii++;
				for (int i = ii; i < countMPL; i++)
				{
					if (dynamic_cast<EmergencyMission*>(MPL.getItemAt(i)))
						cout << "," << MPL.getItemAt(i)->getID() << "/" << RPL.getItemAt(i)->getID();
				}
				cout << "] ";
			}
			ii = 0;
			while (ii < countMPL && !(dynamic_cast<PolarMission*>(MPL.getItemAt(ii))))
			{
				ii++;
			}
			if (ii != countMPL)
			{
				cout << "(" << MPL.getItemAt(ii)->getID() << "/" << RPL.getItemAt(ii)->getID();
				ii++;
				for (int i = ii; i < countMPL; i++)
				{
					if (dynamic_cast<PolarMission*>(MPL.getItemAt(i)))
						cout << "," << MPL.getItemAt(i)->getID() << "/" << RPL.getItemAt(i)->getID();
				}
				cout << ") ";
			}
			ii = 0;
			while (ii < countMPL && !(dynamic_cast<MountainousMission*>(MPL.getItemAt(ii))))
			{
				ii++;
			}
			if (ii != countMPL)
			{
				cout << "{" << MPL.getItemAt(ii)->getID() << "/" << RPL.getItemAt(ii)->getID();
				ii++;
				for (int i = 0; i < countMPL; i++)
				{
					if (dynamic_cast<MountainousMission*>(MPL.getItemAt(i)))
						cout << "," << MPL.getItemAt(i)->getID() << "/" << RPL.getItemAt(i)->getID();
				}
				cout << "} ";
			}
			cout << endl;
			cout << "-----------------------------------------------------------------------------------" << endl;
			cout << eRWL.getLength() + pRWL.getLength() + mRCL.getLength() << " Available Rover: ";
			if (!eRWL.isEmpty())
			{
				cout << "[";
				while (eRWL.dequeue(eR))
				{
					cout << eR->getID();
					if (eRWL.peek(eR))
						cout << ",";
				}
				cout << "] ";
			}
			if (!pRWL.isEmpty())
			{
				cout << "(";
				while (pRWL.dequeue(pR))
				{
					cout << pR->getID();
					if (pRWL.peek(pR))
						cout << ",";
				}
				cout << ") ";
			}
			if (!mRWL.isEmpty())
			{
				cout << "{";
				while (mRWL.dequeue(mR))
				{
					cout << mR->getID();
					if (mRWL.peek(mR))
						cout << ",";
				}
				cout << "}";
			}
			cout << endl;
			cout << "-----------------------------------------------------------------------------------" << endl;
			cout << eRCL.getLength() + pRCL.getLength() + mRWL.getLength() << " In-Checkup Rover: ";
			if (!eRCL.isEmpty())
			{
				cout << "[";
				while (eRCL.dequeue(eR))
				{
					cout << eR->getID();
					if (eRCL.peek(eR))
						cout << ",";
				}
				cout << "] ";
			}
			if (!pRCL.isEmpty())
			{
				cout << "(";
				while (pRCL.dequeue(pR))
				{
					cout << pR->getID();
					if (pRCL.peek(pR))
						cout << ",";
				}
				cout << ") ";
			}
			if (!mRCL.isEmpty())
			{
				cout << "{";
				while (mRCL.dequeue(mR))
				{
					cout << mR->getID();
					if (mRCL.peek(mR))
						cout << ",";
				}
				cout << "}";
			}
			cout << endl;
			cout << "-----------------------------------------------------------------------------------" << endl;
			int countCML = CML.getLength();
			cout << countCML << " Completed Missions: ";
			for (int i = 0; i < countCML; i++)
			{
				CML.dequeue(mm);
				if (dynamic_cast<MountainousMission*>(mm))
				{
					cout << "{" << mm->getID() << "} ";
				}
				else if (dynamic_cast<PolarMission*>(mm))
				{
					cout << "(" << mm->getID() << ") ";
				}
				else if (dynamic_cast<EmergencyMission*>(mm))
				{
					cout << "[" << mm->getID() << "] ";
				}
			}
			cout << endl;
		}
		else if (mode == 3 && !once)
		{
			cout << "Silent Mode" << endl << "Simulation Starts..." << endl;
			once = true;
		}
		else if (mode == 3 && MarsStationPtr->isDone()) {
			cout << "Simulation ends, Output file created" << endl;
		}
	}
};