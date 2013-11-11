/*
  File:         Train.cpp
  Objective:    Implementations
  Edited:       2013 / Paul Frend
*/
#include "Train.h"


//************************************
// Method:    Train
// FullName:  Train::Train
// Access:    public 
// Returns:   
// Qualifier: :id(id), vehicles(vehicles), /*null pointers but to derived classes of vehicles. */ schedDepTime(schedDepTime), schedArrTime(schedArrTime), depTime(schedDepTime), arrTime(schedArrTime), depStation(depStation), arrStation(arrStation), late(false), state(NOT_ASSEMBLED)
// Parameter: int id
// Parameter: trainMap vehicles
// Parameter: int schedDepTime
// Parameter: int schedArrTime
// Parameter: Station * depStation
// Parameter: Station * arrStation
//************************************
Train::Train(int id, trainMap vehicles, int schedDepTime, int schedArrTime, Station* depStation, Station* arrStation)
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
	for (pair<const trainSlot,Vehicle*> &v : vehicles)
	{
		delete v.second;
		v.second = NULL;
	}
}



//************************************
// Method:    addVehicles
// FullName:  Train::addVehicles
// Access:    public 
// Returns:   bool true if all vehicles added. false if not all were added
// Qualifier:
//************************************
bool Train::addVehicles() {
	bool success = true;
	for (pair<const trainSlot,Vehicle*> &v : vehicles)
	{
		
		//only search for vehicles that are null
		if (!v.second) {

		Vehicle *found = depStation->findVehicle(v.first.second);
		if (found) //if find by type
		{
			//remove from station
			depStation->removeVehicle(found);
			
			//add to train
			v.second = found;
			//success = true;

		} else {
			success = false;
		}
		}
	}
	return success;
}

//************************************
// Method:    unloadVehicles
// FullName:  Train::unloadVehicles
// Access:    public 
// Returns:   bool
// Qualifier:
//************************************
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

//************************************
// Method:    display
// FullName:  Train::display
// Access:    public 
// Returns:   void
// Qualifier:
//************************************
void Train::display() {
	
	cout << endl << endl
		<< "Train id: " << id << endl
		<< "state: " << convertState(state) << endl
		<< "Departure: at " << depTime << " from station " << depStation->getId() << endl
		<< "Arrival: at " << arrTime << " at station " << arrStation->getId() << endl;
	if(late) cout << "Running late by " << depTime - schedDepTime << " minutes" << endl;
	
	cout << "vehicles in train: " << endl << endl;

	//print all vehicles
	for (pair<const trainSlot,Vehicle*> &v : vehicles) {

		if(v.second)
			v.second->display();
		else
			cout << "Not yet added: " << v.first.second;
		cout << endl;
	}
}

//************************************
// Method:    convertState
// FullName:  Train::convertState
// Access:    public 
// Returns:   std::string
// Qualifier:
// Parameter: trainStateT state
//************************************
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
	default:
		return "error";
	}
}

