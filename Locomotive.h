/*
  File:         Locomotive.h
  Objective:    Header for Locomotive class
  Date:         2013 / Paul Frend
*/

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

