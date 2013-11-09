#pragma once
#include "Vehicle.h"
#include <string>

class Carriage :
	public Vehicle
{


public:
	Carriage(int id, string type);
	~Carriage(void);
	virtual void display(ostream&) = 0;
};

