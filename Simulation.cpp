/*
  File:         Simulation.cpp
  Objective:    Implementation of class Simulation
  Date:         2011 / Örjan Sterner
  Edited:       2013 / Paul Frend
*/


#include "Simulation.h"
#include "Event.h"

// Execute events until event queue is empty
void Simulation::advance()

{
	//only process events that are meant to happen before currentTime
    while(eventQueue.top()->getTime() <= currentTime) {
        Event * nextEvent = eventQueue.top();
        eventQueue.pop(); 
        nextEvent->processEvent();
		
		delete nextEvent;
		nextEvent = NULL;

		if (eventQueue.empty())
		{
			return;
		}		
    }
}


void Simulation::scheduleEvent (Event * newEvent) {
    eventQueue.push (newEvent);
}