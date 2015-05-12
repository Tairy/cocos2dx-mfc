#pragma once
#include "cocos2d.h"
#include "vector"
using namespace std;
USING_NS_CC;

class PathSprite 
{
	public:
		PathSprite(CCSprite* sprite)
		{
			m_parent = NULL;
			m_child = NULL;
			m_costToSource = 0;
			m_FValue = 0;
			m_sprite = sprite;
		};
	public:
		CCSprite* m_sprite;//包含的瓦片精灵
		PathSprite* m_parent;//父节点
		PathSprite* m_child;//子节点
		float m_costToSource;//到起始点的距离
		int m_x;//地图坐标
		int m_y;
		float m_FValue;
};