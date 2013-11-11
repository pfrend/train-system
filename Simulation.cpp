/*
  File:         Simulation.cpp
  Objective:    Implementation of class Simulation
  Date:         2011 / Örjan Sterner
  Edited:       2013 / Paul Frend
*/

#include "Simulation.h"
#include "Constants.h"
#include "Event.h"


Simulation::~Simulation() {
	while( ! eventQueue.empty()) {
		Event * delEvent = eventQueue.top();
		 eventQueue.pop();
		 delete delEvent;
		 delEvent = NULL;
	}
}

// Execute events until event queue is empty
bool Simulation::advance(int time)

{
	currentTime += time;

	//only process events that are meant to happen before currentTime
    while(eventQueue.top()->getTime() <= currentTime) {

		Event * nextEvent = eventQueue.top();
        eventQueue.pop(); 
        nextEvent->processEvent();
		
		if (eventQueue.empty())
		{
			return false;
		}		
		delete nextEvent;
		nextEvent = NULL;

    }

	if(currentTime >= SIM_TIME)
		return false;

	return true;

}


void Simulation::scheduleEvent (Event * newEvent) {
    eventQueue.push (newEvent);
}