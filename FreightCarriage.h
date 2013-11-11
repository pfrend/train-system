/*
  File:         FreightCarriage.h
  Objective:    Header for FreightCarriage.h
  Date:         2013 / Paul Frend
*/

#pragma once
#include "carriage.h"
class FreightCarriage :
	public Carriage
{
public:
	FreightCarriage(int id, string type);
	~FreightCarriage(void);
	virtual void display(ostream&) = 0;
};

