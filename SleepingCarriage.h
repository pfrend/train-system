#pragma once
#include "PeopleCarriage.h"
class SleepingCarriage :
	public PeopleCarriage
{

private:
	int beds;

public:
	SleepingCarriage(int id, int beds);
	~SleepingCarriage(void);
	void display(ostream&);
};

