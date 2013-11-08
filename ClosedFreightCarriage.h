#pragma once
#include "freightcarriage.h"
class ClosedFreightCarriage :
	public FreightCarriage
{

private:
	int loadingVolume;

public:
	ClosedFreightCarriage(void);
	~ClosedFreightCarriage(void);
	void display(ostream&);
};

