#include "Station.h"


Station::Station(void)
{
}


Station::~Station(void)
{
}


//find vehicle
Vehicle* Station::findVehicle(string type) {
	
	vit vi = find_if(vehicles.begin(),vehicles.end(),VehiclePred(type));

	//deref pointer to vehicle pointer
	return vi == vehicles.end() ? NULL : *vi;

}

bool Station::removeVehicle(Vehicle* v){
	
	int success;
	
	//if specified by key, erase method will return num of elems erased.
    success = vehicles.erase(v);
	
	//return true if 1 elem was erased.
	return success == 1;
}