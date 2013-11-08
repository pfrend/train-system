#pragma once
#include "vehicle.h"
class Carriage :
	public Vehicle
{
public:
	Carriage(void);
	~Carriage(void);
	virtual void display(ostream&) = 0;
};

