#pragma once
#include "locomotive.h"
class dieselLoc :
	public Locomotive
{

private:
	int maxSpeedKm;
	double fuelConsumption;

public:
	dieselLoc(void);
	~dieselLoc(void);
	void display(ostream&);
};

