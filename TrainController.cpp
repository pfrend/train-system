/*
  File:         TrainController.h
  Objective:    Implementations
  Edited:       2013 / Paul Frend
*/
#include "TrainController.h"


//************************************
// Method:    TrainController
// FullName:  TrainController::TrainController
// Access:    public 
// Returns:   
// Qualifier: : theSim(theSim), delayedTrips(0), successTrips(0), totalLateMins(0)
// Parameter: Simulation * theSim
//************************************
TrainController::TrainController( Simulation* theSim ) 
	: theSim(theSim), delayedTrips(0), successTrips(0), totalLateMins(0)
{}


//************************************
// Method:    ~TrainController
// FullName:  TrainController::~TrainController
// Access:    public 
// Returns:   
// Qualifier:
// Parameter: void
//************************************
TrainController::~TrainController(void)
{
	for (pair<int,Train*> train : trains) {
		delete train.second;
		train.second = NULL;
	}

	for (pair<int,Station*> station : stations) {
		delete station.second;
		station.second = NULL;
	}
	
}

//************************************
// Method:    readInStations
// FullName:  TrainController::readInStations
// Access:    private 
// Returns:   bool
// Qualifier:
// Parameter: string fileName
//************************************
bool TrainController::readInStations( string fileName )
{
	string name;
	int id, vAmt;

	//vars for reading vehicles
	int vId,seats, beds, loadSur, loadVol, maxSp, power; 
	double loadCap, fuelCon;
	bool internet;
	string vType;
	Vehicle* v;

	//create file
	fstream inFile(fileName,ios::in);
	if(!inFile) return false;

	//remove any existing stations
	//deleteTrains(); TODO
	

	while (inFile) {
		vehicleSet vehicles; //unordered multiset

		inFile >> id >> name >> vAmt; //get station id, name and amount of vehicles.
		inFile.get();

		for (int i = 0; i < vAmt; i++)
		{
			getline(inFile, vType);
			inFile >> vId;			

			if (vType == "CoachCarriage")
			{
				inFile >> seats >> internet;
				v = new CoachCarriage(vId,seats,internet);
			} else if (vType == "SleepingCarriage") {
				inFile >> beds;
				v = new SleepingCarriage(vId, beds);
			} else if (vType == "ClosedFreightCarriage") {
				inFile >> loadVol;
				v = new ClosedFreightCarriage(vId,loadVol);
			} else if (vType == "OpenFreightCarriage") {
				inFile >> loadCap >> loadSur;
				v = new OpenFreightCarriage(vId, loadCap, loadSur);
			} else if (vType == "elecLoc") {
				inFile >> maxSp >> power;
				v = new ElecLoc(vId,maxSp,power);
			} else if (vType == "dieselLoc") {
				inFile >> maxSp >> fuelCon;
				v = new DieselLoc(vId,maxSp, fuelCon);
			}
			inFile.get();
			vehicles.emplace(v);				
		}

		stations.emplace(id, new Station(id,name,vehicles)); //place in unordered map
	}
	inFile.close();
	return true;
	
}

//pre: stations with Id's that the trains specify already exist
//************************************
// Method:    readInTrains
// FullName:  TrainController::readInTrains
// Access:    private 
// Returns:   bool
// Qualifier:
// Parameter: string fileName
//************************************
bool TrainController::readInTrains( string fileName )
{
	string vType;
	int id, depId,arrId, arrTime, depTime, vAmt;

	//create file
	fstream inFile(fileName,ios::in);
	if(!inFile) return false;

	//remove any existing trains
	//deleteTrains(); TODO

	while (inFile) {

		trainMap vehicles; //trainSlot holds vehicle order in train and type

		inFile >> id >> depId >> arrId >> depTime >> arrTime >> vAmt;
		inFile.get();

		for (int i = 0; i < vAmt; i++)
		{
			getline(inFile, vType);

			//add vehicle types from file to vehicle map
			vehicles.emplace(trainSlot(i,vType),nullptr);
		}

		//TODO: find pointers to stations from their id's above.
		Station *arrStation = stations.find(arrId)->second;
		Station *depStation = stations.find(depId)->second;

		trains.emplace(id,new Train(id,vehicles,depTime,arrTime,depStation,arrStation));
	}
	inFile.close();
	return true;

}

//************************************
// Method:    readInData
// FullName:  TrainController::readInData
// Access:    public 
// Returns:   bool
// Qualifier:
// Parameter: string stationFile
// Parameter: string trainFile
//************************************
bool TrainController::readInData( string stationFile, string trainFile )
{
	if (readInStations(stationFile))
	{
		return readInTrains(trainFile);
	}
	return false;
}

//************************************
// Method:    scheduleEvents
// FullName:  TrainController::scheduleEvents
// Access:    public 
// Returns:   void
// Qualifier:
//************************************
void TrainController::scheduleEvents()
{
	//schedule build events for every train in system
	for (pair<int,Train*> train : trains) {
		int depTime = train.second->getSchedDepTime() - SCHEDULE_BUILD; //build should happen 30 minutes before departure
		theSim->scheduleEvent(new BuildEvent(theSim,this,depTime,train.first));
	}
}

//************************************
// Method:    tryBuild
// FullName:  TrainController::tryBuild
// Access:    public 
// Returns:   bool
// Qualifier:
// Parameter: int trainId
//************************************
bool TrainController::tryBuild(int trainId)
{
	//find train
	Train* tmpTrain = trains.find(trainId)->second;
	
	if (tmpTrain && tmpTrain->addVehicles())
	{
		cout << "time " << theSim->getTime() << ": Train " << trainId << " started building at station " << tmpTrain->getDepStation(); 

		//set state
		tmpTrain->setState(NOT_READY);
		
		return true;
	}
	cout << endl << endl << "time " << theSim->getTime() << ": Train " << trainId << " could not finish build at station " << tmpTrain->getDepStation();
	cout << endl << "Trying again in " << TRAIN_DELAY << " minutes";
		
		//delay train
		tmpTrain->delay(TRAIN_DELAY);
	

	//set train to late
	if ( ! tmpTrain->getLate()){
		tmpTrain->setLate(true);
	}
	
	return false;
}


//************************************
// Method:    readyTrain
// FullName:  TrainController::readyTrain
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int trainId
//************************************
void TrainController::readyTrain(int trainId)
{
	//find train
	Train* tmpTrain = trains.find(trainId)->second;

	//set state
	tmpTrain->setState(READY);
	
	cout << endl << "time " << theSim->getTime() << ": Train " << trainId << " has been assembled at station " << tmpTrain->getDepStation(); 
}

//************************************
// Method:    dispatchTrain
// FullName:  TrainController::dispatchTrain
// Access:    public 
// Returns:   int
// Qualifier:
// Parameter: int trainId
//************************************
int TrainController::dispatchTrain( int trainId )
{
	int lateness;
	//find train
	Train* tmpTrain = trains.find(trainId)->second;

	//set state
	tmpTrain->setState(RUNNING);

	//current time
	int cTime = theSim->getTime();


	//if train is leaving late
	if(tmpTrain->getLate()) {
		//how late is it
		lateness = cTime - tmpTrain->getSchedDepTime();
	}

	int arrTime = tmpTrain->getArrTime();

	cout << endl << "time " << theSim->getTime() << ": Train " << trainId << " just left station " << tmpTrain->getDepStation();
	if (tmpTrain->getLate())
		cout << endl << "It left " << lateness << " minutes late";
	else
		cout << endl << "It left on time ";

	cout << " and will arrive at time " << arrTime;

	return arrTime;
}

//************************************
// Method:    arriveTrain
// FullName:  TrainController::arriveTrain
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int trainId
//************************************
void TrainController::arriveTrain( int trainId )
{
	//find train
	Train* tmpTrain = trains.find(trainId)->second;
	tmpTrain->setState(ARRIVED);

	cout << endl << "time " << theSim->getTime() << ": Train " << trainId << " just arrived at station " << tmpTrain->getArrStation();

	//if train arrived late
	if (tmpTrain->getLate()) {
		int lateMins = tmpTrain->getArrTime() - tmpTrain->getSchedArrTime();
		delayedTrips++;
		totalLateMins += lateMins;
		cout << endl << "It arrived " << lateMins << " minutes late";
	}
	else {
		cout << endl << "It arrived on time ";
		successTrips++;
	}
}

//************************************
// Method:    printSummary
// FullName:  TrainController::printSummary
// Access:    public 
// Returns:   void
// Qualifier:
//************************************
void TrainController::printSummary()
{
	cout << "end of sim. Details:" << endl << endl
		<< delayedTrips << " trains delayed" << endl
		<< totalLateMins << " total late minutes" << endl
		<< successTrips << " total successful trips on time" << endl
		<< countNotAssembled() << " trains never left" << endl << endl;
}

//************************************
// Method:    stripTrain
// FullName:  TrainController::stripTrain
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int trainId
//************************************
void TrainController::stripTrain( int trainId )
{
	//find train
	Train* tmpTrain = trains.find(trainId)->second;

	int	loadSize = tmpTrain->getVehicleCount();

	//move vehicles to station
	tmpTrain->unloadVehicles();

	tmpTrain->setState(FINISHED);

	cout << "time " << theSim->getTime() << ": Train " << trainId << " finished at station " << tmpTrain->getArrStation();
	cout << endl << "It unloaded " << loadSize << " vehicles." << endl;
}

//************************************
// Method:    closeTracks
// FullName:  TrainController::closeTracks
// Access:    public 
// Returns:   void
// Qualifier:
//************************************
void TrainController::closeTracks()
{
	cout << "time " << theSim->getTime() << ": END. Train tracks are now closed. No trains are active.";
}

//************************************
// Method:    countNotAssembled
// FullName:  TrainController::countNotAssembled
// Access:    public 
// Returns:   int
// Qualifier:
//************************************
int TrainController::countNotAssembled()
{
	int count = 0;
	for (pair<int,Train*> train : trains) {
		if(train.second->getState() == NOT_ASSEMBLED) count++;
	}
	return count;
}

//************************************
// Method:    printTrain
// FullName:  TrainController::printTrain
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int trainId
//************************************
void TrainController::printTrain( int trainId )
{
	Train* t = getTrain(trainId);
	if (t) {
		t->display();
	} else {
		cout << "train not found!";
	}
}

//************************************
// Method:    getTrain
// FullName:  TrainController::getTrain
// Access:    private 
// Returns:   Train*
// Qualifier:
// Parameter: int id
//************************************
Train* TrainController::getTrain( int id )
{
	map<int,Train*>::iterator it;
	it = trains.find(id);
	if(it!=trains.end())
		return it->second;
	else
		return NULL;
	;
}

//************************************
// Method:    printStation
// FullName:  TrainController::printStation
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int stationId
//************************************
void TrainController::printStation( int stationId )
{
	Station* s = getStation(stationId);

	if (s) {
		s->display();
	} else {
		cout << "station not found!";
	}
}

//************************************
// Method:    getStation
// FullName:  TrainController::getStation
// Access:    private 
// Returns:   Station*
// Qualifier:
// Parameter: int stationId
//************************************
Station* TrainController::getStation( int stationId )
{
	unordered_map<int,Station*>::iterator it;
	it = stations.find(stationId);
	if(it!=stations.end())
		return it->second;
	else
		return NULL;
	;
}

//************************************
// Method:    display
// FullName:  TrainController::display
// Access:    public 
// Returns:   void
// Qualifier:
//************************************
void TrainController::display()
{
	cout << "Trains: " << endl;
	for (pair<int,Train*> train : trains) {
		cout << "Id: " << train.second->getId() << endl;
	}
	cout << endl
		<< "Stations: " << endl;
	for (pair<int,Station*> station : stations) {
		cout << "Id: " << station.second->getId() << " Name: " << station.second->getName() << endl;
	}
}




//HELPERS
//------------------------------------------------------------------------------
// Name : waitForKey
// Purpose : stalls program and waits for key press
// In data : -
// Out data : -
//------------------------------------------------------------------------------
void waitForKey()
{
	cout << endl << endl << "Press a key to continue!";
	cin.get();
}