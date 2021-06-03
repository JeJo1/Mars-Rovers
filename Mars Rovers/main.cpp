#include <iostream>
#include "MarsStation.h"

using namespace std;

int main() 
{
	MarsStation Station;

	while (!Station.isDone()) {
		Station.PerformNextDay();
	}

	return 0;
}