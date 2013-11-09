#pragma once
#include "freightcarriage.h"
class ClosedFreightCarriage :
	public FreightCarriage
{

private:
	int loadingVolume;

public:
	ClosedFreightCarriage(int id, int loadingVolume);
	~ClosedFreightCarriage(void);
	void display(ostream&);
};

