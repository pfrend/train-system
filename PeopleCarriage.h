#pragma once
#include "Carriage.h"
class PeopleCarriage :
	public Carriage
{



public:
	PeopleCarriage(int id, string type);
	~PeopleCarriage(void);
	void display(ostream&) = 0;
};

