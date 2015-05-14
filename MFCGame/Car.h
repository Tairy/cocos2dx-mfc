#pragma once
#include "PathSprite.h"

//enum WalkState
//{
//	WALK_LEFT,
//	WALK_RIGHT,
//	WALK_STAND
//};

class Car:public PathSprite
{
public:
	/*CCArmature *armature;
	WalkState m_walkState;*/
public:
	Car(CCSprite* sprite);
	bool is_busy;
};