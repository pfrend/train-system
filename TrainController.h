/*
  File:         TrainController.h
  Objective:    Header for TrainController class. Main class which operates on trains and stations and prints to user. Reacts to events.
  Date:         2013 / Paul Frend
*/
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
	int delayedTrips;
	int successTrips;
	int totalLateMins;
	bool readInStations(string fileName);
	bool readInTrains(string fileName);
	Train* getTrain(int id);
	Station* getStation( int stationId );
public:
	TrainController( Simulation *theSim);
	~TrainController( void );
	bool readInData( string stationFile, string trainFile);
	void scheduleEvents();
	
	//event functions
	bool tryBuild(int trainId);
	void readyTrain( int trainId );
	int dispatchTrain( int trainId ); //returns arrival time
	void arriveTrain( int trainId );
	void stripTrain( int trainId );
	void closeTracks();
	
	void printSummary();
	void printTrain(int trainId);
	void printStation(int stationId);

	int countNotAssembled();
	void display();
};
void waitForKey();

