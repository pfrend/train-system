#pragma once
#include "locomotive.h"
class elecLoc :
	public Locomotive
{

private:
	int maxSpeedKm;
	int powerKw;
public:
	elecLoc(void);
	~elecLoc(void);
	void display(ostream&);
};

