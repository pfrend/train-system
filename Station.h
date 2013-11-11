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
typedef unordered_multiset<Vehicle*> vehicleSet;
typedef vehicleSet::iterator vit;

class Station
{

private:
	int id;
	string name;
	unordered_set<Train*> trains; //pool of trains that are assembled and ready to leave.
	unordered_multiset<Vehicle*> vehicles; //the pool of vehicles sitting at a station.

public:
	Station(int id, string name, vehicleSet vehicles);
	~Station(void);
	void addVehicle(Vehicle* vehicle) {vehicles.emplace(vehicle);}
	Vehicle* findVehicle(string type);
	bool removeVehicle(Vehicle* vehicle); //deletes pointer from vehicles, not the vehicle object from memory
	int getId(){return id;}
	void display();
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