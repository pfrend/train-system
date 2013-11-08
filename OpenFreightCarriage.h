#pragma once
#include "freightcarriage.h"
class OpenFreightCarriage :
	public FreightCarriage
{

private:
	double loadCapacity;
	int loadSurface;

public:
	OpenFreightCarriage(void);
	~OpenFreightCarriage(void);
	void display(ostream&);
};

