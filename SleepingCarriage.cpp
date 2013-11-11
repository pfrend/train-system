/*
  File:         SleepingCarriage.cpp
  Objective:    Implementations
  Edited:       2013 / Paul Frend
*/
#include "SleepingCarriage.h"


SleepingCarriage::SleepingCarriage(int id, int beds)
	:PeopleCarriage(id,"SleepingCarriage"),
	beds(beds)
{
}


SleepingCarriage::~SleepingCarriage(void)
{
}

void SleepingCarriage::display(ostream& os) {
	Vehicle::display(os);
	os << "beds: " << beds << endl;
}