#pragma once
#include "peoplecarriage.h"
class SleepingCarriage :
	public PeopleCarriage
{

private:
	int beds;

public:
	SleepingCarriage(void);
	~SleepingCarriage(void);
	void display(ostream&);
};

