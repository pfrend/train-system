#pragma once
#include <vector>
#include "Train.h"

using namespace std;

class Station
{

private:
	int id;
	vector<Train*> trains; //can a station have more than one ready build trains? why not? multiple tracks?
	vector<Vehicle*> vehicles; //the pool of vehicles sitting at a station.

public:
	Station(void);
	~Station(void);
	void addVehicle(Vehicle* vehicle);
	Vehicle* findVehicle();
};

