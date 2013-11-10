//Train states
const enum trainStateT {NOT_ASSEMBLED,
	NOT_READY,
	READY,
	RUNNING,
	ARRIVED,
	FINISHED};

const int TIMESTEP = 10;
const int SCHEDULE_READY = 30;