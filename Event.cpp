/*
  File:         Event.cpp
  Objective:    Implementations
  Date:         2007 / Örjan Sterner
*/

#include "Event.h"
#include "TrainController.h"
#include "Simulation.h"

// Implementationer:

void BuildEvent::processEvent()
{
	//if (tCtrl->tryEnter(groupSize))
	//{
	//	//generate random num
	//	time += randBetween(MIN_ORDER_WAIT,MAX_ORDER_WAIT);
	//	theSim->scheduleEvent(new readyEvent(theSim, tCtrl, time, groupSize*BURGERS_PER_PERSON));
	//}

}

void readyEvent::processEvent()
{
	
	//theBar->order(trainId);
	//time += randBetween(MIN_SERVICE_WAIT, MAX_SERVICE_WAIT);
	//theSim->scheduleEvent(new LeaveEvent(theSim, theBar, time, trainId));
	
}

void LeaveEvent::processEvent()
{
	//tCtrl->serve(trainId);
	//time += SEAT_SEARCH_TIME;
	//theSim->scheduleEvent(new ArriveEvent(theSim, tCtrl, time, trainId/BURGERS_PER_PERSON));
}

void ArriveEvent::processEvent()
{
//	if (tCtrl->getChairs(trainId))
//	{
//		
//		time += randBetween(MIN_EATING_TIME,MAX_EATING_TIME);
//		theSim->scheduleEvent(new FinishEvent(theSim, tCtrl, time, trainId));
//	}
//	else 
//	{
//		time += SEAT_SEARCH_TIME;
//		theSim->scheduleEvent(new ArriveEvent(theSim, tCtrl, time, trainId));
//	}
}

void FinishEvent::processEvent()
{
	//tCtrl->leave(groupSize);
}

void EndEvent::processEvent()
{
	//tCtrl->closeDown();

}
