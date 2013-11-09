#pragma once
#include "locomotive.h"
class elecLoc :
	public Locomotive
{

private:
	int maxSpeedKm;
	int powerKw;
public:
	elecLoc(int id, int maxSpeedKm, int powerKw);
	~elecLoc(void);
	void display(ostream&);
};

