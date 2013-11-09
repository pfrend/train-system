#include "Train.h"


Train::Train(int id, map<trainSlot,Vehicle*> vehicles, int schedDepTime, int schedArrTime, Station* depStation, Station* arrStation)
	:id(id),
	vehicles(vehicles), //null pointers but to derived classes of vehicles.
	schedDepTime(schedDepTime),
	schedArrTime(schedArrTime),
	depStation(depStation),
	arrStation(arrStation), 
	late(false), 
	state(NOT_ASSEMBLED)    
{}


Train::~Train(void)
{
}


//add vehicles. pre:state is READY
//return true if all vehicles added
//return false if any vehicles weren't added
bool Train::addVehicles() {
	bool success = true;
	for (pair<const trainSlot,Vehicle*> &v : vehicles)
	{
		
		Vehicle *found = depStation->findVehicle(v.first.second);
		if (found) //if find by type
		{
			//remove from station
			depStation->removeVehicle(found);
			
			//add to train
			v.second = found;
			success = true;

		} else {
			success = false;
		}
		
		
	}
	return success;
}

bool Train::unloadVehicles() {
	bool success;
	for (pair<const trainSlot,Vehicle*> &v : vehicles)
	{
		
		if (v.second) //if vehicle exists
		{
			//add to station
			arrStation->addVehicle(v.second);
			
			//remove from train
			v.second = NULL;
			success = true;

		} else {
			success = false;
		}
	}
	return success;
}
