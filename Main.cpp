#include "Simulation.h"
#include "TrainController.h"

//test function definitions
void testVehicleArray();
void testCreateTrain();
void testAddVehicleToStation();
void testMoveVehicleToTrainFromStation();


int main() {
//testVehicleArray();
//testCreateTrain();
//testAddVehicleToStation();
//testMoveVehicleToTrainFromStation();

	Simulation *theSim = new Simulation;
	TrainController *tCtrl = new TrainController(theSim); //pass in sim.

	//1. read in stage, e.g how many stations, how many vehicles, how many trains
	//one file for stations and its vehicles, one for trains

	tCtrl->readInData("data/stations.dat","data/trains.dat");
	
	//2. create events from trains that have been read in
	//trains are located with pointers in trainController, sorted by dep time.
	//for each train, schedule an event, with its departure time, id, and station id.

	tCtrl->scheduleEvents();

	//print menu which lets user advance time


	char ch; //menu selection
	bool rerun = true, simHasEvents = true;
	int cTime;

	do
	{
		cout << string(100, '\n');

		cout << endl
			<< " *-*-*-*-* MENU *-*-*-*-*" << endl
			<< " 1. Advance time" << endl
			<< " 2. Get train info" << endl
			<< " 3. Get station info" << endl
			<< " 4. Quit" << endl << endl
			<< "Please make your selection:";

		cin >>ch; // user makes their choice
		cin.get();


		// run based on user input	
		switch(ch)
		{ 
		case '1':
			cout << endl << endl;
			
			if( ! simHasEvents) {
				cout << "End of simulation. Details: " << endl << endl;
				tCtrl->printSummary();
				rerun = false;
				break;
			}
			
			cout << "Moving forward " << TIMESTEP << " minutes..." << endl << endl;
			simHasEvents = theSim->advance(TIMESTEP);

			cTime = theSim->getTime();
			if(cTime >= SIM_TIME)
				theSim->scheduleEvent(new EndEvent(theSim,tCtrl,cTime));

			
			waitForKey();
			break;

		case '2':
			break;
		case '7':
		case 'q':
		case 'Q':
		case char(27):
			rerun = false;
			break; // end program with option 3, q or Q, or escape button
		default: cout << "not an option on the list!";
			waitForKey();
		}
	}while(rerun);	

system("pause");
return 0;
}


//*******************************
//TEST FUNCTIONS
//*******************************
void testVehicleArray(){

map<trainSlot, Vehicle*> testVehicles;
map<trainSlot, Vehicle*>::iterator it;

//add a logical vehicle, i.e. pointer 
Vehicle* v;
trainSlot v1(1,"DieselLoc");
trainSlot v2(2,"SleepingCarriage");


testVehicles.emplace(v1, v);
testVehicles.emplace(v2, v);

it = testVehicles.find(v2);
cout << it->first.second;

}



void testCreateTrain(){

	map<trainSlot, Vehicle*> testVehicles;
	Vehicle *v;
	Station *st1;
	Station *st2;
	int trainSize = 10;
	for (int i = 0; i < trainSize; i++)
	{
		testVehicles.emplace(trainSlot(i,"SleepingCarriage"),v); 
	}

	Train train(142, testVehicles, 300, 400, st1, st2);
	cout << "create train tested";

}

void testAddVehicleToStation(){
	//Station st1();
	//Vehicle *v = new CoachCarriage(10,30,true);
	//st1.addVehicle(v);

	////find vehicle at station
	//v = st1.findVehicle("CoachCarriage");
	
}

void testMoveVehicleToTrainFromStation() {

	//map<trainSlot, Vehicle*> testVehicles;
	//Vehicle *v, *v2;
	//Station st1(),st2();
	//Station* st1p = &st1;
	//Station* st2p = &st2;
	//int trainSize = 10;
	//
	////build vehicles for train
	//for (int i = 0; i < trainSize; i++)
	//{
	//	testVehicles.emplace(trainSlot(i,"SleepingCarriage"),nullptr); 
	//}

	////add vehicle of diff type
	//testVehicles.emplace(trainSlot(10, "CoachCarriage"),v);

	////create train
	//Train train(142, testVehicles, 300, 400, st1p, st2p);

	////add a vehicle to station
	//v2 = new CoachCarriage(10,30,true);
	//st1.addVehicle(v2);

	////find vehicle at station
	//v2 = st1.findVehicle("CoachCarriage");

	////try to build train
	//train.addVehicles();

	////unload train
	//train.unloadVehicles();

}


