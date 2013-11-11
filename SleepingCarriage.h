/*
  File:         SleepingCarriage.h
  Objective:    Header for SleepingCarriage class
  Date:         2013 / Paul Frend
*/
#pragma once
#include "PeopleCarriage.h"
class SleepingCarriage :
	public PeopleCarriage
{

private:
	int beds;

public:
	SleepingCarriage(int id, int beds);
	~SleepingCarriage(void);
	void display(ostream&);
};

