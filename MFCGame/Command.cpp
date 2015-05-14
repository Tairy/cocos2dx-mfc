#include "StdAfx.h"
#include "Command.h"
#include "StaticValue.h"


Command::Command(void)
{
}


Command::~Command(void)
{
}

Car*  Command::switchCar(CCPoint targetPoint, vector<Car*> cars) {
	for( int i = 0;  i < PLAYER_COUNT; i++ ) {
		cerr<< cars[i]->m_x <<endl;
	}
	return cars[1];
}
