#include <iostream>
#include "MarsStation.h"
#include "UIClass.h"

using namespace std;

int main() 
{
	MarsStation Station;
	UIClass UI(&Station);
	UI.SelectMode();
	while (!Station.mainfunc()) {
		UI.Ready();
		UI.Output();
	}
	return 0;
}