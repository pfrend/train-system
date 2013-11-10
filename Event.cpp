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
	if (tCtrl->tryBuild(trainId)) //tries to move all pointers from station to train
	{
		time += SCHEDULE_READY;
		theSim->scheduleEvent(new readyEvent(theSim, tCtrl, time, trainId));
	} else {
		time += TRAIN_DELAY;
		theSim->scheduleEvent(new BuildEvent(theSim,tCtrl,time,trainId));
	}

}

void readyEvent::processEvent()
{
	tCtrl->readyTrain(trainId);
	time += SCHEDULE_LEAVE;
	theSim->scheduleEvent(new LeaveEvent(theSim,tCtrl,time,trainId));
	
}

void LeaveEvent::processEvent()
{
	int arrTime = tCtrl->dispatchTrain(trainId);
	time = arrTime;
	theSim->scheduleEvent( new ArriveEvent(theSim, tCtrl, time, trainId));
}

void ArriveEvent::processEvent()
{

	tCtrl->arriveTrain(trainId);
	time += SCHEDULE_STRIP_TRAIN;
	theSim->scheduleEvent( new FinishEvent(theSim, tCtrl, time, trainId));

}

void FinishEvent::processEvent()
{
	tCtrl->stripTrain(trainId);

}

void EndEvent::processEvent()
{
	tCtrl->closeTracks();

}
