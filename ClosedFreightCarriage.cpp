#include "ClosedFreightCarriage.h"


ClosedFreightCarriage::ClosedFreightCarriage(int id, int loadingVolume)
	:FreightCarriage(id, "ClosedFreightCarriage"),
	loadingVolume(loadingVolume)
{
}


ClosedFreightCarriage::~ClosedFreightCarriage(void)
{
}

void ClosedFreightCarriage::display(ostream&) {
}