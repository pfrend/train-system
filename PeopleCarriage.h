#pragma once
#include "carriage.h"
class PeopleCarriage :
	public Carriage
{

private:
	int seats;
	bool internet;

public:
	PeopleCarriage(void);
	~PeopleCarriage(void);
	void display(ostream&) = 0;
};

