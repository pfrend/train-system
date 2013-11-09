#include "dieselLoc.h"


DieselLoc::DieselLoc(int id, int maxSpeedKm, double fuelConsumption)
	:Locomotive(id,"dieselLoc"), //parent
	maxSpeedKm(maxSpeedKm), fuelConsumption(fuelConsumption) //memb
{
}


DieselLoc::~DieselLoc(void)
{
}

void DieselLoc::display(ostream&) {
}