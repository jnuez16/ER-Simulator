//Group Name: Midnight Company
//Members: Joshua Nuez and Joshua Vinton
//Project: Emergency Room Simulator

#include "Simulator.h"

int main()
{
	srand(time(NULL));
	Simulator* ER = new Simulator();
	ER->enter_data();
	ER->start_treatment();
	ER->menu();

	return 0;
}