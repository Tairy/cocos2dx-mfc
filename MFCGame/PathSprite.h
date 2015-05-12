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
		CCSprite* m_sprite;//��������Ƭ����
		PathSprite* m_parent;//���ڵ�
		PathSprite* m_child;//�ӽڵ�
		float m_costToSource;//����ʼ��ľ���
		int m_x;//��ͼ����
		int m_y;
		float m_FValue;
};