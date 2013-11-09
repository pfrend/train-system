#include <iostream>
#include <string>

#pragma once

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

