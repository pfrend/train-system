/*
  File:         ClosedFreightCarriage.h
  Objective:    Header for ClosedFreightCarriage class
  Date:         2013 / Paul Frend
*/

#pragma once
#include "freightcarriage.h"
class ClosedFreightCarriage :
	public FreightCarriage
{

private:
	int loadingVolume;

public:
	ClosedFreightCarriage(int id, int loadingVolume);
	~ClosedFreightCarriage(void);
	virtual void display(ostream&);
};

