/*
  File:         elecLoc.h
  Objective:    Header for ElecLoc class
  Date:         2013 / Paul Frend
*/

#pragma once
#include "locomotive.h"
class ElecLoc : //electric locomotive
	public Locomotive
{

private:
	int maxSpeedKm;
	int powerKw;
public:
	ElecLoc(int id, int maxSpeedKm, int powerKw);
	~ElecLoc(void);
	void display(ostream&);
};

