#pragma once
#include "carriage.h"
class FreightCarriage :
	public Carriage
{
public:
	FreightCarriage(int id, string type);
	~FreightCarriage(void);
	virtual void display(ostream&) = 0;
};

