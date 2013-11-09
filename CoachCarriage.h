#pragma once
#include "peoplecarriage.h"
class CoachCarriage :
	public PeopleCarriage
{

private:
	int seats;
	bool internet;

public:
	CoachCarriage(int id, int seats, bool internet);
	~CoachCarriage(void);
	virtual void display(ostream&);
};

