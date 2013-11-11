/*
  File:         Vehicle.h
  Objective:    Header for vehicle class. Trains consist of vehicles.
  Date:         2013 / Paul Frend
*/
#pragma once
#include <iostream>
#include <string>


using namespace std;
class Vehicle
{

protected:
int id;
string type;

public:
	Vehicle(int id, string type);
	~Vehicle(void);
	virtual void display(ostream& = cout) = 0;
	string getType(){return type;} 
};

