#include "TrainController.h"


TrainController::TrainController( Simulation* theSim ) 
	: theSim(theSim), delayedTrips(0), successTrips(0)
{}


TrainController::~TrainController(void)
{
}

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
	
	vehicleSet vehicles; //unordered multiset

	while (inFile) {

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
				v = new elecLoc(vId,maxSp,power);
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

		map<trainSlot, Vehicle*> vehicles; //trainSlot holds vehicle order in train and type

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

		trains.emplace(id,new Train(id,vehicles,depTime,arrTime,arrStation,depStation));
	}
	inFile.close();
	return true;

}

bool TrainController::readInData( string stationFile, string trainFile )
{
	if (readInStations(stationFile))
	{
		return readInTrains(trainFile);
	}
	return false;
}

void TrainController::scheduleEvents()
{
	//schedule build events for every train in system
	for (pair<int,Train*> train : trains) {
		int depTime = train.second->getSchedDepTime() - SCHEDULE_BUILD; //build should happen 30 minutes before departure
		theSim->scheduleEvent(new BuildEvent(theSim,this,depTime,train.first));
	}
}

bool TrainController::tryBuild(int trainId)
{
	//find train
	Train* tmpTrain = trains.find(trainId)->second;
	
	if (tmpTrain && tmpTrain->addVehicles())
	{
		cout << "time " << theSim->getTime() << ": Train " << trainId << " finished building at station " << tmpTrain->getDepStation(); 

		//set state
		tmpTrain->setState(NOT_READY);
		
		return true;
	}
	cout << "time " << theSim->getTime() << ": Train " << trainId << "could not build at station " << tmpTrain->getDepStation(); 


	//set train to late
	if ( ! tmpTrain->getLate()){
		tmpTrain->setLate(true);
	}
	
	return false;
}


void TrainController::readyTrain(int trainId)
{
	//find train
	Train* tmpTrain = trains.find(trainId)->second;

	//set state
	tmpTrain->setState(READY);
	
	cout << "time " << theSim->getTime() << ": Train " << trainId << " has been assembled at station " << tmpTrain->getDepStation(); 
}

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
	
		//set current departure time
		tmpTrain->setDepTime(cTime);
		
		//how late is it
		lateness = cTime - tmpTrain->getSchedDepTime();

		//delay arrival time
		tmpTrain->arrDelay(lateness);
	}

	int arrTime = tmpTrain->getArrTime();

	cout << "time " << theSim->getTime() << ": Train " << trainId << " just left station " << tmpTrain->getDepStation();
	if (tmpTrain->getLate())
		cout << endl << "It left " << lateness << " minutes late";
	else
		cout << endl << "It left on time ";

	cout << " and will arrive at time " << arrTime;

	return arrTime;
}

void TrainController::arriveTrain( int trainId )
{
	//find train
	Train* tmpTrain = trains.find(trainId)->second;
	tmpTrain->setState(ARRIVED);

	cout << "time " << theSim->getTime() << ": Train " << trainId << " just arrived at station " << tmpTrain->getArrStation();

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

void TrainController::printSummary()
{
	cout << "end of sim. TODO: Summary details" << endl << endl;
}

void TrainController::stripTrain( int trainId )
{
	//find train
	Train* tmpTrain = trains.find(trainId)->second;

	int	loadSize = tmpTrain->getVehicleCount();

	//move vehicles to station
	tmpTrain->unloadVehicles();

	tmpTrain->setState(FINISHED);

	cout << "time " << theSim->getTime() << ": Train " << trainId << " finished at station " << tmpTrain->getArrStation();
	cout << endl << "It unloaded " << loadSize << " vehicles."
}

void TrainController::closeTracks()
{
	cout << "time " << theSim->getTime() << ": END. Train tracks are now closed. No more trains may leave.";
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