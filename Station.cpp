#include "Station.h"

Station::Station( int id, string name, vehicleSet vehicles )
	:id(id),name(name),vehicles(vehicles)
{}


Station::~Station(void)
{
	for (Vehicle* v : vehicles) {
		delete v;
		v = NULL;
	}
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

void Station::display()
{
	cout << endl << endl
		<< "Station id: " << id << endl
		<< "station name: " << name << endl
		<< "vehicles at station: " << endl << endl;

	//print all vehicles
	for (Vehicle* v : vehicles) {
		if(v)
			v->display();
		cout << endl;
	}
}