//Train states
const enum trainStateT {NOT_ASSEMBLED,
	NOT_READY,
	READY,
	RUNNING,
	ARRIVED,
	FINISHED};

const int TIMESTEP = 10;
const int TRAIN_DELAY = 10;
const int SCHEDULE_BUILD = 30; //note: subtracted from depTime as build happens sooner.
const int SCHEDULE_READY = 30;
const int SCHEDULE_LEAVE = 10;
const int SCHEDULE_STRIP_TRAIN = 30;
const int SIM_TIME = 300;