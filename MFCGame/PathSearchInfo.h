#pragma once
#include "StaticValue.h"
#include "PathSprite.h"
#include "MathLogic.h"
#include "cocos2d.h"
#include <functional>

//#include "paddle.h"
USING_NS_CC;
class PathSearchInfo:public CCNode//Ѱ·��(��Ҫ����Ѱ·�Ĳ������߼�)
{
public:
	PathSearchInfo(CCTMXTiledMap* tiledMap);

private:
	int m_playerMoveStep;//���ﵱǰ���г̵�����
	std::function<void(CCPoint)> m_moveDone;//�ƶ������ص�
	bool m_isSetMoveDoneCallback;

	std::function<void(vector<PathSprite*>)> m_drawPath;//���߻ص�  ������
	bool m_isSetDrawPathCallback;

	//std::function<void(CCPoint point, Paddle* selectObj)> m_selectObj;//ѡ������ص�
	bool m_isSetSelectObjCallback;

	CCTMXTiledMap* m_map;//��ͼ
	CCTMXLayer* m_road;//��·
	CCSize m_mapSize;//��ͼ��С
	CCSize m_tileSize;//��ͼ�Ŀ��С
	vector<PathSprite*> m_openList;//�����б�(���������ڽڵ�)
	PathSprite* m_inspectArray[MAP_WIDTH][MAP_HEIGHT];//ȫ����Ҫ���ĵ�
	vector<PathSprite*> m_pathList;//·���б�
	vector<PathSprite*> m_haveInspectList;//�������б�
	PathSprite* m_moveObj;//�ƶ�������
	bool m_enableMove;//�Ƿ����ƶ�
	bool m_isMoving;//�Ƿ������ƶ�
public:
	CCTMXTiledMap* getMap()
	{
		return m_map;
	}
	void setEnableMove(bool isEnable)
	{
		m_enableMove = isEnable;
	}

	bool getEnableMove()
	{
		return m_enableMove;
	}

	bool getIsMoving()
	{
		return m_isMoving;
	}
 	void setMoveDoneCallback(function<void(CCPoint)>& pFunc);//���ûص�

	void setDrawPathCallback(function<void(vector<PathSprite*>)>& pFunc);//���ûص�
	
//	void setSelectCallback(function<void(CCPoint point, Paddle* selectObj)> &pFunc);//���ûص�

	void initMapObject(const char* layerName, const char* objName);////��ʼ����ͼ�������(�������,��������ص�����)

	CCPoint getMapPositionByWorldPosition(CCPoint point);//������������õ���ͼ����

	CCPoint getWorldPositionByMapPosition(CCPoint point);//���ݵ�ͼ����õ���������

	void pathFunction( CCPoint point, PathSprite* obj );//����·������

private:
	void calculatePath();//����·��
	
	float calculateTwoObjDistance(PathSprite* obj1, PathSprite* obj2);//�������������ľ���

	void inspectTheAdjacentNodes(PathSprite* node, PathSprite* adjacent, PathSprite* endNode);//�����ڵĽڵ���뿪�Žڵ���
	
	PathSprite* getMinPathFormOpenList();//�ӿ��Žڵ��л�ȡFֵ��Сֵ�ĵ�
	
	PathSprite* getObjFromInspectArray(int x, int y);//���ݺ�������Ӽ�������л�ȡ��
	
	bool removeObjFromOpenList( PathSprite* sprite);//�ӿ����б����Ƴ�����
	
	void resetInspectArray();//���ü���б�
	
	bool detectWhetherCanPassBetweenTwoPoints(CCPoint p1, CCPoint p2);//���2��λ�����Ƿ����ϰ���
	
	void resetObjPosition();//�������λ��
	
	void clearPath();//���·��

	void moveObj();//�ƶ�ʵ�ֺ���
};