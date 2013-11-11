/*
  File:         Train.h
  Objective:    Header for Train class. Represents train objects in system.
  Date:         2013 / Paul Frend
*/
#pragma once
using namespace std;
#include <map>
#include "Vehicle.h"
#include "Constants.h"
#include "Station.h"

//trainSlot stored as key in trainMap, which stores all vehicles.
//int: vehicle order in train. string: vehicle type.
typedef pair<int,string> trainSlot; 


//train compare binary function. order by order in train
class trainCompare {
public:
	bool operator() (trainSlot a, trainSlot b) const{
		return a.first < b.first;
	}
};

typedef map<trainSlot, Vehicle*, trainCompare> trainMap;

class Train
{

private:
	int id;
	typedef trainMap::iterator it; //store pair in map so that we get access to type, order and vehicle in one 'row'
	trainMap vehicles; //pointers to vehicles.
	trainStateT state; // enum of train states. see consts.h
	int depTime,schedDepTime; //dep time = when train actually left. schedDepTime = when it was meant to leave.
	int arrTime, schedArrTime; //as above but for arrivals.
	bool late;
	Station* depStation;
	Station* arrStation;
	
public:
	Train(int id, trainMap vehicles, int schedDepTime, int schedArrTime, Station* depStation, Station* arrStation);
	~Train(void);
	bool addVehicles(); //tries to add vehicles from depStation. TRUE if all added. FALSE if any failed.
	bool unloadVehicles(); //moves vehicles to arrStation

	int getSchedDepTime(){return schedDepTime;}
	trainStateT getState(){return state;}
	int getSchedArrTime(){return schedArrTime;}
	int getDepTime(){return depTime;}
	int getId(){return id;}
	int getArrTime(){return arrTime;}
	int getDepStation(){return depStation->getId();}
	int getArrStation(){return arrStation->getId();}
	bool getLate(){return late;}
	int getVehicleCount(){return vehicles.size();}

	void setLate(bool nLate){late = nLate;}
	void setDepTime(int time){depTime = time;}
	void setState( trainStateT nState ){state = nState;}
	void delay(int time){arrTime+=time;depTime+=time;}

	void display(); //print out train details
	string convertState( trainStateT state ); //convert enum to string

};

