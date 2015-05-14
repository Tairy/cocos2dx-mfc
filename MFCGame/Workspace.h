#pragma once
#include "cocos2d.h"
USING_NS_CC;

class Workspace
{
public:
	Workspace(float x, float y, float width, float height, CCString* name);
	~Workspace(void);

public:
	float m_x;
	float m_y;
	float m_width;
	float m_height;
	CCString* m_name;
};

