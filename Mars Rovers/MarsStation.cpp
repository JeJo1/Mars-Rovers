#include "MarsStation.h"
#include "FormulationEvent.h"
#include "CancelationEvent.h"
#include "PromotionEvent.h"
#include "fstream"
#include"iostream"
using namespace std;

int EmergencyMission::Count = 0;
int MountainousMission::Count = 0;
int MountainousMission::PromotedCount = 0;
int MountainousMission::AutoPromotion = 0;
int PolarMission::Count = 0;
int EmergencyRover::CE = 0;
int EmergencyRover::Count = 0;
int EmergencyRover::SE = 0;
int MountainousRover::CM = 0;
int MountainousRover::Count = 0;
int MountainousRover::SM = 0;
int PolarRover::CP = 0;
int PolarRover::Count = 0;
int PolarRover::SP = 0;
int Rover::N = 0;
int Rover::Count = 0;
MarsStation* Event::m = 0;

void MarsStation::readFile() {
	ifstream inputFile("InputSample.txt");

	int M,
		P,
		E,
		SM,          
		SP,          
		SE,        
		N,          
		CM,         
		CP,          
		CE,          
		AutoP,
		EventCnt,
		ED,
		ID,
		TLOC,
		MDUR,
		SIG;

	char typeE,          //Type of event(F, C or P)
		TYP;             //Type of mission(M,P or E)

	if (!inputFile.eof())
	{
		inputFile >> M;
		inputFile >> P;
		inputFile >> E;
		inputFile >> SM;
		inputFile >> SP;
		inputFile >> SE;
		inputFile >> N;
		inputFile >> CM;
		inputFile >> CP;
		inputFile >> CE;
		inputFile >> AutoP;
		inputFile >> EventCnt;

		for (int i = 0; i < EventCnt; i++)
		{
		    inputFile >> typeE;
			if (typeE == 'F')
			{
				inputFile >> TYP;
				inputFile >> ED;
				inputFile >> ID;
				inputFile >> TLOC;
				inputFile >> MDUR;
				inputFile >> SIG;
				FormulationEvent* f = new FormulationEvent(TYP, ED, ID, TLOC, MDUR, SIG);
				Events.enqueue(f);
			}
			else if (typeE == 'X')
			{
				inputFile >> ED;
				inputFile >> ID;
				CancelationEvent* c = new CancelationEvent(ED, ID);
				Events.enqueue(c);
			}
			else if (typeE == 'P')
			{
				inputFile >> ED;
				inputFile >> ID;
				PromotionEvent* p = new PromotionEvent(ED, ID);
				Events.enqueue(p);
			}
		}
	}

	EmergencyMission::setCount(0);
	MountainousMission::setCount(0);
	MountainousMission::setPromotedCount(0);
	MountainousMission::setAutoP(AutoP);
	PolarMission::setCount(0);
	Rover::setN(N);
	PolarRover::setCount(P);
	PolarRover::setSP(SP);
	PolarRover::setCP(CP);
	EmergencyRover::setCount(E);
	EmergencyRover::setSE(SE);
	EmergencyRover::setCE(CE);
	MountainousRover::setCount(M);
	MountainousRover::setSM(SM);
	MountainousRover::setCM(CM);
	Event::setStation(this);

	for (int i = 0; i < P; i++)
		pRWL.enqueue(new PolarRover);
	for (int i = 0; i < E; i++)
		eRWL.enqueue(new EmergencyRover);
	for (int i = 0; i < M; i++)
		mRWL.enqueue(new MountainousRover);

	inputFile.close();
}

void MarsStation::Return_From_Checkup() {
	EmergencyRover* eR;
	//While there is an Emergency rover who finishes checkup today
	while (eRCL.peek(eR) && eR->getCheckupStartDay() + EmergencyRover::getCE() == currentDay) {
		eRCL.dequeue(eR);
		eRWL.enqueue(eR);
		eR->ResetMissionCount();
	}

	MountainousRover* mR;
	//While there is a MountainousRover rover who finishes checkup today
	while (mRCL.peek(mR) && mR->getCheckupStartDay() + MountainousRover::getCM() == currentDay) {
		mRCL.dequeue(mR);
		mRWL.enqueue(mR);
		mR->ResetMissionCount();
	}

	PolarRover* pR;
	//While there is a Polar rover who finishes checkup today
	while (pRCL.peek(pR) && pR->getCheckupStartDay() + PolarRover::getCP() == currentDay) {
		pRCL.dequeue(pR);
		pRWL.enqueue(pR);
		pR->ResetMissionCount();
	}
}

void MarsStation::Return_From_Missions() {
	Rover* r;
	Mission* m;

	//While there is a mission that finishes today
	//This equivilantly implies that there exists a rover at the head of the RPL that is done with it's assigned mission
	while ((m = MPL.peekFirst()) && m->getCD() == currentDay) {
		MPL.removeFirst();

		CML.enqueue(m);

		r = RPL.removeFirst();
		r->IncrementMissionCount();
		//If the rover needs checkup enqueue in checkup list
		if (Rover::getN() == r->getMissionCount()) {
			r->setCheckupStartDay(currentDay);

			if (dynamic_cast<EmergencyRover*>(r))
				eRCL.enqueue((EmergencyRover*)r);
			else if (dynamic_cast<MountainousRover*>(r))
				mRCL.enqueue((MountainousRover*)r);
			else
				pRCL.enqueue((PolarRover*)r);
		}
		//Else the rover waits for a mission to be assigned to
		else {
			if (dynamic_cast<EmergencyRover*>(r))
				eRWL.enqueue((EmergencyRover*)r);
			else if (dynamic_cast<MountainousRover*>(r))
				mRWL.enqueue((MountainousRover*)r);
			else
				pRWL.enqueue((PolarRover*)r);
		}
	}
}

void MarsStation::Execute_Events() {
	Event* e;
	//While there is an event that is to be executed today
	while (Events.peek(e) && e->getED() == currentDay) {
		Events.dequeue(e);
		e->Execute();
		delete e;
	}
}

void MarsStation::Auto_Promote() {
	int i = 0;
	MountainousMission* m;
	while ((m = mMWL.getItemAt(i)) && currentDay - m->getFD() == MountainousMission::getAutoP()) {
		mMWL.removeAt(i++);
		m->Promote();
		EmergencyMission* em = new EmergencyMission(m->getFD(), m->getID(), m->getTLOC(), m->getMDUR(), m->getSIG());
		eMWL.enqueue(em, em->getPriority());
		delete m;
	}
}

void MarsStation::Assign_Missions() {
	EmergencyMission* eM;
	MountainousMission* mM;
	PolarMission* pM;
	EmergencyRover* eR;
	MountainousRover* mR;
	PolarRover* pR;

	bool canProceed = true;

	while (eMWL.peek(eM) && eM->getFD() >= currentDay && canProceed) {
		canProceed = false;
		if (eRWL.dequeue(eR)) {
			eMWL.dequeue(eM);
			eM->setWD(currentDay - eM->getFD());
			eR->assign(eM);
			MPL.insert(eM);
			RPL.insert(eR);
			canProceed = true;
		}
		else if (mRWL.dequeue(mR)) {
			eMWL.dequeue(eM);
			eM->setWD(currentDay - eM->getFD());
			mR->assign(eM);
			MPL.insert(eM);
			RPL.insert(mR);
			canProceed = true;
		}
		else if (pRWL.dequeue(pR)) {
			eMWL.dequeue(eM);
			eM->setWD(currentDay - eM->getFD());
			pR->assign(eM);
			MPL.insert(eM);
			RPL.insert(mR);
			canProceed = true;
		}
	}

	while (pMWL.peek(pM) && pM->getFD() >= currentDay && pRWL.dequeue(pR)) {
		pMWL.dequeue(pM);
		pM->setWD(currentDay - pM->getFD());
		pR->assign(pM);
		MPL.insert(pM);
		RPL.insert(pR);
	}

	canProceed = true;

	while ((mM = mMWL.peekFirst()) && mM->getFD() >= currentDay && canProceed) {
		canProceed = false;
		if (mRWL.dequeue(mR)) {
			mMWL.removeFirst();
			mM->setWD(currentDay - mM->getFD());
			mR->assign(mM);
			MPL.insert(mM);
			RPL.insert(mR);
			canProceed = true;
		}
		else if (eRWL.dequeue(eR)) {
			mMWL.removeFirst();
			mM->setWD(currentDay - mM->getFD());
			eR->assign(mM);
			MPL.insert(mM);
			RPL.insert(eR);
			canProceed = true;
		}
	}
}

bool MarsStation::isDone() {
	return Events.isEmpty() && eMWL.isEmpty() && mMWL.isEmpty() && pMWL.isEmpty() && MPL.isEmpty() && RPL.isEmpty() && eRCL.isEmpty() && mRCL.isEmpty() && pRCL.isEmpty();
}



MarsStation::MarsStation() {
	readFile();
	currentDay = 0;
}

MarsStation::~MarsStation() {
		Mission* m;
		EmergencyRover* eR;
		MountainousRover* mR;
		PolarRover* pR;
		while (CML.dequeue(m))
			delete m;
		while (eRWL.dequeue(eR))
			delete eR;
		while (mRWL.dequeue(mR))
			delete mR;
		while (pRWL.dequeue(pR))
			delete pR;
	}

bool MarsStation::mainfunc() { //TODO: name it a cooler name
	currentDay++;
	Return_From_Checkup();
	Return_From_Missions();
	Execute_Events();
	Auto_Promote();
	Assign_Missions();
	return isDone();
}

PriorityQueue<EmergencyMission>& MarsStation::getEMWL()
{
	return eMWL;
}

List<MountainousMission>& MarsStation::getMMWL()
{
	return mMWL;
}

Queue<PolarMission>& MarsStation::getPMWL()
{
	return pMWL;
}
int MarsStation::getCurrentday()
{
	return currentDay;
}
int MarsStation::getEMWLnum()
{
	return eMWL.getLength();
}
int MarsStation::getMMWLnum()
{
	return(mMWL.getLength());
	
}
int MarsStation::getPMWLnum()
{
	return pMWL.getLength();
}
List<Mission> & MarsStation::getMPL()
{
	return MPL;
}
List<Rover>& MarsStation::getRPL()
{
	return RPL;
}
Queue<Mission>& MarsStation::getCML()
{
	return CML;
}
Queue<PolarRover>& MarsStation::getPRWL()
{
	return pRWL;
}
Queue<EmergencyRover>& MarsStation::getERCL()
{
	return eRCL;
}
Queue<PolarRover>& MarsStation::getPRCL()
{
	return pRCL;
}
Queue<MountainousRover>& MarsStation::getMRCL()
{
	 return mRCL;
}
Queue<EmergencyRover>& MarsStation::getERWL()
{
	return eRWL;
}
Queue<MountainousRover>& MarsStation::getMRWL()
{
	return mRWL;
}


void MarsStation::writeFile()
{
	ofstream outputFile("outputSample.txt");

	Queue<Mission> tempQ = CML;
	Queue<Mission> temp;
	Mission* m1;
	Mission* m2;
	EmergencyMission* em;
	MountainousMission* mm;
	PolarMission* pm;
	EmergencyRover* er;
	MountainousRover* mr;
	PolarRover* pr;
	int totalM,  //Total number of missions
		totalR,  //Total number of rovers
		Auto,    //Percentage of automatically-promoted missions
		avgWait,
		avgExec,
		sumWD = 0,
		sumED = 0;

	outputFile << "CD" << "   "
		<< "ID" << "   "
		<< "FD" << "   "
		<< "WD" << "   "
		<< "ED" << endl;

	while (!tempQ.isEmpty())
	{
		tempQ.dequeue(m1);
		if (tempQ.isEmpty())
		{
			temp.enqueue(m1);
			return;
		}
		tempQ.dequeue(m2);
		if (m1->getCD() == m2->getCD())
		{
			while (!tempQ.isEmpty())
			{
				if (m1->getFD() < m2->getFD())
				{
					temp.enqueue(m1);
					tempQ.dequeue(m1);
				}
				else
				{
					temp.enqueue(m2);
					tempQ.dequeue(m2);
				}
			}
			if (m1->getFD() > m2->getFD())
			{
				temp.enqueue(m2);
				temp.enqueue(m1);
			}
			else
			{
				temp.enqueue(m1);
				temp.enqueue(m2);
			}
		}
		else
		{
			temp.enqueue(m1);
			temp.enqueue(m2);
		}
	}

	while (temp.isEmpty())
	{
		temp.dequeue(m1);
		outputFile << m1->getCD() << "    "
			<< m1->getID() << "    "
			<< m1->getFD() << "    "
			<< m1->getWD() << "    "
			<< m1->getED() << endl;
		sumED = sumED + m1->getED();
		sumWD = sumWD + m1->getWD();
	}

	outputFile << "………………………………………………" << endl;
	outputFile << "………………………………………………" << endl;

	totalM = em->getCount() + mm->getCount() + pm->getCount();
	outputFile << "Missions: " << totalM << " "
		<< "[M: " << mm->getCount()
		<< ", P: " << pm->getCount()
		<< ", E: " << em->getCount << "]" << endl;

	totalR = er->getCount() + mr->getCount() + pr->getCount();
	outputFile << "Rovers: " << totalR << "     "
		<< "[M: " << mr->getCount()
		<< ", P: " << pr->getCount()
		<< ", E: " << er->getCount << "]" << endl;

	avgWait = sumWD / totalM;
	avgExec = sumED / totalM;
	outputFile << "Avg Wait = " << avgWait << ", " << "Avg Exec = " << avgExec << endl;

	Auto = (mm->getPromotedCount() / (mm->getPromotedCount() + mm->getCount())) * 100;
	outputFile << "Auto-promoted: " << Auto << "%" << endl;

	outputFile.close();
}