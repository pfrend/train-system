#pragma once
using namespace std;
#include <map>
#include "Vehicle.h"
#include "Constants.h"
#include "Station.h"

//forward declare station
class Station;

//trainSlot stored as key in trainMap, which stores all vehicles.
//int: vehicle order in train. string: vehicle type.
typedef pair<int,string> trainSlot; 

class Train
{

private:
	int id;
	typedef map<trainSlot, Vehicle*> trainMap;
	typedef trainMap::iterator it; //store pair in map so that we get access to type, order and vehicle in one 'row'
	trainMap vehicles; //pointers to vehicles.
	trainStateT state;
	int depTime,schedDepTime; //dep time = when train actually left. schedDepTime = when it was meant to leave.
	int arrTime, schedArrTime; //as above but for arrivals.
	bool late;
	Station* depStation;
	Station* arrStation;
	
  
	bool active; //needed? to find connected trains just loop through and filter by state? Or have a pointer collection in TrainController which points to active trains and one which points to all trains.
	
	it checkId(int vehicleId); //find component with ID


public:
	Train(int id, map<trainSlot,Vehicle*> vehicles, int schedDepTime, int schedArrTime, Station* depStation, Station* arrStation);
	~Train(void);
	bool addVehicles(); //tries to add vehicles from depStation
	bool unloadVehicles();

	int getSchedDepTime(){return schedDepTime;}
	trainStateT getState(){return state;}
	int getSchedArrTime(){return schedArrTime;}
	int getDepTime(){return depTime;}
	int getArrTime(){return arrTime;}
	int getDepStation(){return depStation->getId();}
	int getArrStation(){return arrStation->getId();}
	bool getLate(){return late;}
	int getVehicleCount(){return vehicles.size();}

	void setLate(bool nLate){late = nLate;}
	void setDepTime(int time){depTime = time;}
	void setState( trainStateT nState ){state = nState;}
	void arrDelay(int time){arrTime+=time;}

	void display(); //print out train details
	string convertState( trainStateT state );
	//TODO print out individual carriage details and more display methods
	//Vehicle* getLocomotive();
};

