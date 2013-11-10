#pragma once
#include "Train.h"
#include "Station.h"
#include <vector>
#include <set>
#include <unordered_map>
#include <fstream>

//forward declare
class Simulation;

class TrainController
{

private:
	map<int, Train*> trains; //int is the id of the train
	unordered_map<int, Station*> stations;
	Simulation* theSim;
	bool readInStations(string fileName);
	bool readInTrains(string fileName);
public:
	TrainController(void);
	~TrainController(void);
	bool readInData(string fileName);

};

