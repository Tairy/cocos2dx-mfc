#include "StdAfx.h"
#include "Command.h"
#include "StaticValue.h"
#include "MathLogic.h"


Command::Command(void)
{
}


Command::~Command(void)
{
}

Car*  Command::switchCar(CCPoint targetPoint, vector<Car*> cars) {
	float min_dis = 10000000.0;
	int min_index = 0;
	for( int i = 0;  i < PLAYER_COUNT; i++ ) {
		float x = MathLogic::calculateLengthRequiredTwoPoint(targetPoint,CCPoint(float(cars[i]->m_x),float(cars[i]->m_y)) );
		if(x < min_dis) {
			min_index = i;
			min_dis = x;
		} 
		//CCLog("%f", x);
		CCLog("%f,%f",targetPoint.x,targetPoint.y);
		CCLog("%f,%f",float(cars[i]->m_x),float(cars[i]->m_y));
	}
	//CCLog("%d", min_index);
	//CCLog("%f", min_dis);
	return cars[min_index];
}
