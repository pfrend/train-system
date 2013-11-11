/*
  File:         Carriage.h
  Objective:    Header for Carriage class
  Date:         2013 / Paul Frend
*/

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

