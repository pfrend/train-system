#include "TrainController.h"


TrainController::TrainController(void)
{
}


TrainController::~TrainController(void)
{
}

bool TrainController::readInStations( string fileName )
{
	return true;
	

}

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
		trains.emplace(id,new Train(id,vehicles,depTime,arrTime,NULL,NULL));
	}
	return true;

}

bool TrainController::readInData( string fileName )
{
	if (readInStations(fileName))
	{
		return readInTrains(fileName);
	}
	return false;
}
