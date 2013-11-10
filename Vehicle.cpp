#include "Vehicle.h"


Vehicle::Vehicle(int id, string type)
	:id(id),type(type)
{
}


Vehicle::~Vehicle(void)
{
}

void Vehicle::display( ostream& os /*= cout*/ )
{
	os << "Vehicle id " << id << endl
		<< "Vehicle type " << type << endl;
}
