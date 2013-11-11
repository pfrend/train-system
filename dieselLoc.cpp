/*
  File:         dieselLoc.cpp
  Objective:    Implementation for dieselLoc class
  Edited:       2013 / Paul Frend
*/
#include "dieselLoc.h"


DieselLoc::DieselLoc(int id, int maxSpeedKm, double fuelConsumption)
	:Locomotive(id,"dieselLoc"), //parent
	maxSpeedKm(maxSpeedKm), fuelConsumption(fuelConsumption) //memb
{
}


DieselLoc::~DieselLoc(void)
{
}

void DieselLoc::display(ostream& os) {
	Vehicle::display(os);
	os << "max speed (km): " << maxSpeedKm << endl
		<< "Fuel consumption: " << fuelConsumption << endl;
}