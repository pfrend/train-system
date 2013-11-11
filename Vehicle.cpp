/*
  File:         Vehicle.cpp
  Objective:    Implementations
  Edited:       2013 / Paul Frend
*/
#include "Vehicle.h"


Vehicle::Vehicle(int id, string type)
	:id(id),type(type)
{
}


Vehicle::~Vehicle(void)
{
}

//************************************
// Method:    display
// FullName:  Vehicle::display
// Access:    virtual public 
// Returns:   void
// Qualifier:
// Parameter: ostream & os
//************************************
void Vehicle::display( ostream& os /*= cout*/ )
{
	os << "Vehicle id " << id << endl
		<< "Vehicle type " << type << endl;
}
