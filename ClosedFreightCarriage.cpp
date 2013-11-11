/*
  File:         ClosedFreightCarriage.cpp
  Objective:    Implementation of ClosedFreightCarriage class
  Edited:       2013 / Paul Frend
*/

#include "ClosedFreightCarriage.h"


ClosedFreightCarriage::ClosedFreightCarriage(int id, int loadingVolume)
	:FreightCarriage(id, "ClosedFreightCarriage"),
	loadingVolume(loadingVolume)
{
}


ClosedFreightCarriage::~ClosedFreightCarriage(void)
{
}

void ClosedFreightCarriage::display(ostream& os) {
	Vehicle::display(os);
	os << "loading Volume: " << loadingVolume << endl;
}