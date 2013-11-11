/*
  File:         Simulation.h
  Objective:    Header for Simulation class. Takes events in priority queue.
  Date:         2013 / Paul Frend
*/

#pragma once

#include <queue>
#include <vector>
#include "Event.h"

using std::priority_queue;
using std::vector;

class Simulation {
public:
    Simulation () : eventQueue(), currentTime(0) { }
	~Simulation();

    // Add a new event to event queue.
    void scheduleEvent (Event * newEvent);

    int getTime() const { return currentTime; }

    bool advance(int time);

private:
    int currentTime; // Time for last processed event

     /* The event queue. Always sorted with respect to the times
        for the events. The event with the 'smallest' time is always
        placed first in queue and will be processed next. */

    priority_queue<Event*, vector<Event*>, EventComparison> eventQueue;
};