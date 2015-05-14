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
	CCSprite* m_sprite;//��������Ƭ����
	PathSprite* m_parent;//���ڵ�
	PathSprite* m_child;//�ӽڵ�
	float m_costToSource;//����ʼ��ľ���
	int m_x;//��ͼ����
	int m_y;
	float m_FValue;

	int m_startX;//��ʼ��
	int m_startY;

	int m_endX;//������
	int m_endY;
};