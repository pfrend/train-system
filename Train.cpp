#include "Train.h"


Train::Train(int id, map<trainSlot,Vehicle*> vehicles, int schedDepTime, int schedArrTime, Station* depStation, Station* arrStation)
	:id(id),
	vehicles(vehicles), //null pointers but to derived classes of vehicles.
	schedDepTime(schedDepTime),
	schedArrTime(schedArrTime),
	depTime(schedDepTime),
	arrTime(schedArrTime),
	depStation(depStation),
	arrStation(arrStation), 
	late(false), 
	state(NOT_ASSEMBLED)    
{}


Train::~Train(void)
{
}


//add vehicles. 
//pre: state == READY
//return true if all vehicles added
//return false if not all vehicles were added
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

void Train::display() {
	
	cout << endl << endl
		<< "Train id: " << id << endl
		<< "state: " << convertState(state) << endl
		<< "vehicles in train: " << endl << endl;

	//print all vehicles
	for (pair<const trainSlot,Vehicle*> &v : vehicles) {
		if(v.second)
			v.second->display();
	}
}

std::string Train::convertState( trainStateT state )
{
	switch(state)
	{
	case 0:
		return "NOT_ASSEMBLED";
	case 1:
		return "NOT_READY";

	case 2:
		return "READY";
	case 3:
		return "RUNNING";
	case 4:
		return "ARRIVED";
	case 5:
		return "FINISHED";
	}
}

