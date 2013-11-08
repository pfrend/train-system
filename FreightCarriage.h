#pragma once
#include "carriage.h"
class FreightCarriage :
	public Carriage
{
public:
	FreightCarriage(void);
	~FreightCarriage(void);
	virtual void display(void) = 0;
};

