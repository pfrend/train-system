#pragma once
#include "peoplecarriage.h"
class CoachCarriage :
	public PeopleCarriage
{
public:
	CoachCarriage(void);
	~CoachCarriage(void);
	virtual void display(ostream&);
};

