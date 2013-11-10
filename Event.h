#pragma once

// Forward declarations
class Simulation;
class TrainController;

class Event {
public:
    // Constructor requires time of event
    Event (unsigned int t) : time(t) { }
    ~Event() { }

    // Process event by invoking this method
    virtual void processEvent()=0;

    // Get time for this event
    unsigned int getTime() const {
        return time;
    }

protected:
    // Time for this event
    unsigned int time;
};



// Used to compare two Events with respect to time
class EventComparison {
public:
    bool operator() (Event * left, Event * right) {
        return left->getTime() > right->getTime();
    }
};

//--- Derived Event-classes ----------------------------------------------------

class BuildEvent : public Event {
public:
    BuildEvent (Simulation *sim, TrainController *tCtrl, int time, int trainId)
    : Event(time),theSim(sim),tCtrl(tCtrl),groupSize(trainId) { }

    virtual void processEvent();

protected:
    int groupSize;
    Simulation *theSim;
    TrainController *tCtrl;
};

class readyEvent : public Event {
public:
    readyEvent (Simulation *sim, TrainController *tCtrl, int time, int trainId)
    : Event(time),theSim(sim),tCtrl(tCtrl),trainId(trainId) { }

    virtual void processEvent();

protected:
    int trainId;
    Simulation *theSim;
    TrainController *tCtrl;
};



class LeaveEvent : public Event {
public:
    LeaveEvent(Simulation *sim, TrainController *tCtrl, int time, int trainId )
    :Event(time),theSim(sim),tCtrl(tCtrl),trainId(trainId) { }

    virtual void processEvent();

protected:
    int trainId;
    Simulation *theSim;
    TrainController *tCtrl;
};



class ArriveEvent : public Event {
public:
   ArriveEvent(Simulation *sim, TrainController *tCtrl, int time, int trainId )
   :Event(time),theSim(sim),tCtrl(tCtrl),trainId(trainId) { }

   virtual void processEvent();

protected:
   int trainId;
   Simulation *theSim;
   TrainController *tCtrl;
};


class FinishEvent : public Event {
public:
    FinishEvent (Simulation *sim, TrainController *tCtrl, int time, int trainId)
    :Event(time),theSim(sim),tCtrl(tCtrl),groupSize(trainId) { }

    virtual void processEvent();

protected:
    int groupSize;
    Simulation *theSim;
    TrainController *tCtrl;
};


class EndEvent : public Event {
public:
    EndEvent (Simulation *sim, TrainController *tCtrl, int time)
    : Event(time),theSim(sim),tCtrl(tCtrl) { }

    virtual void processEvent();

protected:
    Simulation *theSim;
    TrainController *tCtrl;

};

