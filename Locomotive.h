#pragma once
#include "vehicle.h"
class Locomotive :
	public Vehicle
{
public:
	Locomotive(void);
	~Locomotive(void);
	virtual void display(ostream&) = 0;
};

