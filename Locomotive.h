#pragma once
#include "vehicle.h"
class Locomotive :
	public Vehicle
{


public:
	Locomotive(int id, string type);
	~Locomotive(void);
	virtual void display(ostream&) = 0;
};

