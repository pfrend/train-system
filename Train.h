#pragma once
using namespace std;
#include <map>
#include "Vehicle.h"
#include "Constants.h"
class Train
{

private:
	typedef map<int, Vehicle*>::iterator it;
	map<int,Vehicle*> vehicles;
	trainStateT state;
	it checkId(int vehicleId); //find component with ID


public:
	Train(map<int,Vehicle*> vehicles, trainStateT state);
	~Train(void);
	void display(); //print out train details
	//TODO print out individual carriage details
};

