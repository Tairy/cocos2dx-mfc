#pragma once
#include "cocos2d.h"
USING_NS_CC;


class stop
{
public:
	stop(float x, float y, float width, float height, CCString* name);
	~stop(void);

public:
	float m_x;
	float m_y;
	float m_width;
	float m_height;
	CCString* m_name;
};

