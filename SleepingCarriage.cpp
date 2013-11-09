#include "SleepingCarriage.h"


SleepingCarriage::SleepingCarriage(int id, int beds)
	:PeopleCarriage(id,"SleepingCarriage"),
	beds(beds)
{
}


SleepingCarriage::~SleepingCarriage(void)
{
}

void SleepingCarriage::display(ostream&) {
}