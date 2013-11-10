/*
  File:         Simulation.h
  Objective:    Definition of class Simulation, a framework for
                discrete event-driven simulation
  Date:         2007 / Örjan Sterner
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

    // Add a new event to event queue.
    void scheduleEvent (Event * newEvent);

    int getTime() const { return currentTime; }

    void advance();

private:
    int currentTime; // Time for last processed event

     /* The event queue. Always sorted with respect to the times
        for the events. The event with the 'smallest' time is always
        placed first in queue and will be processed next. */

    priority_queue<Event*, vector<Event*>, EventComparison> eventQueue;
};