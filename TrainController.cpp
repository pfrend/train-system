#include "TrainController.h"


TrainController::TrainController( Simulation* theSim ) : theSim(theSim), delayedTrips(0)
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
		int depTime = train.second->getSchedDepTime() - 30; //build should happen 30 minutes before departure
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
		return true;
	}
	cout << "time " << theSim->getTime() << ": Train " << trainId << "could not build at station " << tmpTrain->getDepStation(); 

	//if this train hasn't been delayed yet, add it to the delayed trips counter
	if (!tmpTrain->getLate()) delayedTrips++;
	
	//set train to late so that above counter doesn't increment next time
	tmpTrain->setLate(true);

	return false;
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