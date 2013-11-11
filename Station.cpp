/*
  File:         Station.cpp
  Objective:    Implementations
  Edited:       2013 / Paul Frend
*/
#include "Station.h"

//************************************
// Method:    Station
// FullName:  Station::Station
// Access:    public 
// Returns:   
// Qualifier: :id(id),name(name),vehicles(vehicles)
// Parameter: int id
// Parameter: string name
// Parameter: vehicleSet vehicles
//************************************
Station::Station( int id, string name, vehicleSet vehicles )
	:id(id),name(name),vehicles(vehicles)
{}


//************************************
// Method:    ~Station
// FullName:  Station::~Station
// Access:    public 
// Returns:   
// Qualifier:
// Parameter: void
//************************************
Station::~Station(void)
{
	for (Vehicle* v : vehicles) {
		delete v;
		v = NULL;
	}
}


//find vehicle
//************************************
// Method:    findVehicle
// FullName:  Station::findVehicle
// Access:    public 
// Returns:   Vehicle*
// Qualifier:
// Parameter: string type
//************************************
Vehicle* Station::findVehicle(string type) {
	
	//NOTE: find_if is linear time. Would be better to use the find method of set as its O(1)
	//but not sure how to implement when not searching for the key.
	vit vi = find_if(vehicles.begin(),vehicles.end(),VehiclePred(type));

	//deref pointer to vehicle pointer
	return vi == vehicles.end() ? NULL : *vi;

}

//************************************
// Method:    removeVehicle
// FullName:  Station::removeVehicle
// Access:    public 
// Returns:   bool
// Qualifier:
// Parameter: Vehicle * vehicle
//************************************
bool Station::removeVehicle(Vehicle* vehicle){
	
	int success;
	
	//if specified by key, erase method will return num of elems erased.
    success = vehicles.erase(vehicle);
	
	//return true if 1 elem was erased.
	return success == 1;
}

//************************************
// Method:    display
// FullName:  Station::display
// Access:    public 
// Returns:   void
// Qualifier:
//************************************
void Station::display()
{
	cout << endl << endl
		<< "Station id: " << id << endl
		<< "station name: " << name << endl
		<< "total vehicles: " << vehicles.size() << endl
		<< "vehicle details: " << endl << endl;

	//print all vehicles
	for (Vehicle* v : vehicles) {
		if(v)
			v->display();
		cout << endl;
	}
}