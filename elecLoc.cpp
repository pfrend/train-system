#include "elecLoc.h"


elecLoc::elecLoc(int id, int maxSpeedKm, int powerKw)
	:Locomotive(id, "ElecLoc"),
	maxSpeedKm(maxSpeedKm),
	powerKw(powerKw)
{
}


elecLoc::~elecLoc(void)
{
}

void elecLoc::display(ostream&) {
}