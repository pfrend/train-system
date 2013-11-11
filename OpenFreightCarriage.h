/*
  File:         OpenFreightCarriage.h
  Objective:    Header for OpenFreightCarriage class
  Date:         2013 / Paul Frend
*/

#pragma once
#include "freightcarriage.h"
class OpenFreightCarriage :
	public FreightCarriage
{

private:
	double loadCapacity;
	int loadSurface;

public:
	OpenFreightCarriage(int id, double loadCapacity, int loadSurface);
	~OpenFreightCarriage(void);
	virtual void display(ostream&);
};

