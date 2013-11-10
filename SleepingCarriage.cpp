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