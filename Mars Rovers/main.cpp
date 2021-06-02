#include <iostream>
#include "MarsStation.h"
#include "UIClass.h"

using namespace std;

int main() 
{
	MarsStation Station;
	while (!Station.isDone()) {
		Station.mainfunc();
	}
	return 0;
}