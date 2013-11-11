/*
  File:         PeopleCarriage.h
  Objective:    Header for PeopleCarriage class
  Date:         2013 / Paul Frend
*/

#pragma once
#include "Carriage.h"
class PeopleCarriage : //abstract class for carriages which transport people
	public Carriage
{



public:
	PeopleCarriage(int id, string type);
	~PeopleCarriage(void);
	void display(ostream&) = 0;
};

