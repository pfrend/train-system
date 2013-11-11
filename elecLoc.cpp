/*
  File:         elecLoc.cpp
  Objective:    Implementation for elecLoc class
  Edited:       2013 / Paul Frend
*/

#include "elecLoc.h"


ElecLoc::ElecLoc(int id, int maxSpeedKm, int powerKw)
	:Locomotive(id, "elecLoc"),
	maxSpeedKm(maxSpeedKm),
	powerKw(powerKw)
{
}


ElecLoc::~ElecLoc(void)
{
}

void ElecLoc::display(ostream& os) {
	Vehicle::display(os);
	os << "max speed (km): " << maxSpeedKm << endl
		<< "Power (kW): " << powerKw << endl;
}