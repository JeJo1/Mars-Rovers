#include "MarsStation.h"
#include "FormulationEvent.h"
#include "CancelationEvent.h"
#include "PromotionEvent.h"

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
MarsStation* Event::m = 0;

void MarsStation::readFile() {
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
		EventCnt;

	//TODO::	1. Read info from the file and inititalize the above ints
	//			2. Construct events and add them to the list

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
		EmergencyMission* em = new EmergencyMission(currentDay, m->getID(), m->getTLOC(), m->getMDUR(), m->getSIG());
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

	/*Events.enqueue(new FormulationEvent('M', 2, 1, 100, 4, 5));
	Events.enqueue(new FormulationEvent('M', 5, 2, 250, 4, 4));
	Events.enqueue(new FormulationEvent('E', 5, 3, 500, 6, 3));
	Events.enqueue(new FormulationEvent('P', 6, 4, 900, 7, 4));
	Events.enqueue(new CancelationEvent(10, 1));
	Events.enqueue(new FormulationEvent('M', 18, 5, 560, 5, 9));
	Events.enqueue(new PromotionEvent(19, 2));
	Events.enqueue(new FormulationEvent('P', 25, 6, 190, 3, 1));*/
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