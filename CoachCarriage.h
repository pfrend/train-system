/*
  File:         CoachCarriage.h
  Objective:    Header for CoachCarriage class
  Date:         2013 / Paul Frend
*/

#pragma once
#include "peoplecarriage.h"
class CoachCarriage :
	public PeopleCarriage
{

private:
	int seats;
	bool internet;

public:
	CoachCarriage(int id, int seats, bool internet);
	~CoachCarriage(void);
	virtual void display(ostream&);
};

