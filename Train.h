#pragma once
using namespace std;
#include <map>
#include "Vehicle.h"
#include "Constants.h"

//forward declare station
class Station;

class Train
{

private:
	int id;
	typedef map<int, Vehicle*>::iterator it;
	map<int,Vehicle*> vehicles;
	trainStateT state;
	int depTime,schedDepTime; //dep time = when train actually left. schedDepTime = when it was meant to leave.
	int arrTime, schedArrTime; //as above but for arrivals.
	bool late;
	Station* depStation, arrStation;
  
	bool active; //needed? to find connected trains just loop through and filter by state? Or have a pointer collection in TrainController which points to active trains and one which points to all trains.
	
	it checkId(int vehicleId); //find component with ID


public:
	Train(map<int,Vehicle*> vehicles, trainStateT state);
	~Train(void);
	void display(); //print out train details
	//TODO print out individual carriage details
	//Vehicle* getLocomotive();
};

