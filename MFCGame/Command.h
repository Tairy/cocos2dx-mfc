#pragma once
#include "Car.h"
#include "cocos2d.h"

class Command
{
public:
	Command(void);
	~Command(void);

	Car * switchCar(CCPoint targetPoint, vector<Car*> cars);
};

