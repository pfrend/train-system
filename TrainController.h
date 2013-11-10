#pragma once
#include <vector>
#include <set>
#include <unordered_map>
#include <fstream>

#include "Train.h"
#include "Station.h"
#include "CoachCarriage.h"
#include "SleepingCarriage.h"
#include "ClosedFreightCarriage.h"
#include "OpenFreightCarriage.h"
#include "elecLoc.h"
#include "dieselLoc.h"
#include "Simulation.h"

//forward declare
//class Simulation;

class TrainController
{

private:
	map<int, Train*> trains; //int is the id of the train
	unordered_map<int, Station*> stations; //int is id of station
	Simulation* theSim;
	bool readInStations(string fileName);
	bool readInTrains(string fileName);
	int delayedTrips;
	int successTrips;
	int totalLateMins;
public:
	TrainController( Simulation *theSim);
	~TrainController( void );
	bool readInData( string stationFile, string trainFile);
	void scheduleEvents();
	bool tryBuild(int trainId);
	void readyTrain( int trainId );
	void printSummary();
	int dispatchTrain( int trainId ); //returns arrival time
	void arriveTrain( int trainId );
};
void waitForKey();

