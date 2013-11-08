#include <iostream>

#pragma once

using namespace std;
class Vehicle
{

protected:
int id;

public:
	Vehicle(int id);
	~Vehicle(void);
	virtual void display(ostream& = cout) = 0;
};

