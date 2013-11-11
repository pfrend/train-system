/*
  File:         dieselLoc.h
  Objective:    Header for DieselLoc class.
  Date:         2013 / Paul Frend
*/

#pragma once
#include "locomotive.h"
class DieselLoc : //diesel locomotive
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

