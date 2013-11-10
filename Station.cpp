#include "Station.h"


Station::Station(void)
{
}


Station::~Station(void)
{
}


//find vehicle
Vehicle* Station::findVehicle(string type) {
	
	//NOTE: find_if is linear time. Would be better to use the find method of set as its O(1)
	//but not sure how to implement when not searching for the key.
	vit vi = find_if(vehicles.begin(),vehicles.end(),VehiclePred(type));

	//deref pointer to vehicle pointer
	return vi == vehicles.end() ? NULL : *vi;

}

bool Station::removeVehicle(Vehicle* vehicle){
	
	int success;
	
	//if specified by key, erase method will return num of elems erased.
    success = vehicles.erase(vehicle);
	
	//return true if 1 elem was erased.
	return success == 1;
}