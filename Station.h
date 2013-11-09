#pragma once
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <functional>
#include <map>
#include "Vehicle.h"

//forward declaration
class Train;

using namespace std;

class Station
{

private:
	int id;
	unordered_set<Train*> trains; //pool of trains that are assembled and ready to leave.
    typedef unordered_multiset<Vehicle*>::iterator vit;
	unordered_multiset<Vehicle*> vehicles; //the pool of vehicles sitting at a station.

public:
	Station(void);
	~Station(void);
	void addVehicle(Vehicle* vehicle) {vehicles.emplace(vehicle);}
	Vehicle* findVehicle(string type);
	bool removeVehicle(Vehicle* v);
};


//Function object for finding vehicle based on type
class VehiclePred {

private:
string type;

public:
	VehiclePred(const string type):type(type){}
	bool operator() (Vehicle* v) {
		return v->getType() == type;
	}
};

