#include "TrainController.h"


TrainController::TrainController( Simulation* theSim ) : theSim(theSim)
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