#pragma once
#include "locomotive.h"
class DieselLoc :
	public Locomotive
{

private:
	int maxSpeedKm;
	double fuelConsumption;

public:
	DieselLoc(int id, int maxSpeedKm, double fuelConsumption);
	~DieselLoc(void);
	void display(ostream&);
};

