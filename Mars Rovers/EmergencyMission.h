#pragma once
#include "Mission.h"

class EmergencyMission : public Mission 
{
private:
	int priority;
	static int Count;

public:
	EmergencyMission() {};
	~EmergencyMission() {};

};