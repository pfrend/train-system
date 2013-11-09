#include "CoachCarriage.h"


CoachCarriage::CoachCarriage(int id, int seats, bool internet)
	:PeopleCarriage(id, "CoachCarriage"),
	seats(seats),internet(internet)
{
}


CoachCarriage::~CoachCarriage(void)
{
}

void CoachCarriage::display(ostream&) {
}