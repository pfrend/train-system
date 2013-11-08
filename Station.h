#pragma once
#include <vector>
#include "Train.h"

using namespace std;

class Station
{

private:
	int id;
	vector<Train*> trains;


public:
	Station(void);
	~Station(void);
};

