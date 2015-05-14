#pragma once

#include "cocos2d.h"
#include "vector"
#include "cocos-ext.h"
using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;
class PathSprite 
{
public:
	PathSprite(CCSprite* sprite):m_parent(NULL),
					m_child(NULL),
					m_costToSource(0),
					m_FValue(0),
					m_sprite(sprite),
					m_startX(0),
					m_startY(0),
					m_endX(0),
					m_endY(0)
	{

	};
public:
	CCSprite* m_sprite;//包含的瓦片精灵
	PathSprite* m_parent;//父节点
	PathSprite* m_child;//子节点
	float m_costToSource;//到起始点的距离
	int m_x;//地图坐标
	int m_y;
	float m_FValue;

	int m_startX;//开始点
	int m_startY;

	int m_endX;//结束点
	int m_endY;
};