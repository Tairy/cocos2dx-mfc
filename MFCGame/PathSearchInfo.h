#pragma once
#include "StaticValue.h"
#include "PathSprite.h"
#include "MathLogic.h"
#include "cocos2d.h"
#include <functional>

//#include "paddle.h"
USING_NS_CC;
class PathSearchInfo:public CCNode//寻路类(主要负责寻路的参数和逻辑)
{
public:
	PathSearchInfo(CCTMXTiledMap* tiledMap);

private:
	int m_playerMoveStep;//人物当前的行程的索引
	std::function<void(CCPoint)> m_moveDone;//移动结束回调
	bool m_isSetMoveDoneCallback;

	std::function<void(vector<PathSprite*>)> m_drawPath;//画线回调  调试用
	bool m_isSetDrawPathCallback;

	//std::function<void(CCPoint point, Paddle* selectObj)> m_selectObj;//选中物体回调
	bool m_isSetSelectObjCallback;

	CCTMXTiledMap* m_map;//地图
	CCTMXLayer* m_road;//道路
	CCSize m_mapSize;//地图大小
	CCSize m_tileSize;//地图的块大小
	vector<PathSprite*> m_openList;//开放列表(里面存放相邻节点)
	PathSprite* m_inspectArray[MAP_WIDTH][MAP_HEIGHT];//全部需要检测的点
	vector<PathSprite*> m_pathList;//路径列表
	vector<PathSprite*> m_haveInspectList;//检测过的列表
	PathSprite* m_moveObj;//移动的物体
	bool m_enableMove;//是否能移动
	bool m_isMoving;//是否正在移动
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
 	void setMoveDoneCallback(function<void(CCPoint)>& pFunc);//设置回调

	void setDrawPathCallback(function<void(vector<PathSprite*>)>& pFunc);//设置回调
	
//	void setSelectCallback(function<void(CCPoint point, Paddle* selectObj)> &pFunc);//设置回调

	void initMapObject(const char* layerName, const char* objName);////初始化地图里的物体(设置深度,设置物体回调函数)

	CCPoint getMapPositionByWorldPosition(CCPoint point);//根据世界坐标得到地图坐标

	CCPoint getWorldPositionByMapPosition(CCPoint point);//根据地图坐标得到世界坐标

	void pathFunction( CCPoint point, PathSprite* obj );//计算路径函数

private:
	void calculatePath();//计算路径
	
	float calculateTwoObjDistance(PathSprite* obj1, PathSprite* obj2);//计算两个物体间的距离

	void inspectTheAdjacentNodes(PathSprite* node, PathSprite* adjacent, PathSprite* endNode);//把相邻的节点放入开放节点中
	
	PathSprite* getMinPathFormOpenList();//从开放节点中获取F值最小值的点
	
	PathSprite* getObjFromInspectArray(int x, int y);//根据横纵坐标从检测数组中获取点
	
	bool removeObjFromOpenList( PathSprite* sprite);//从开放列表中移除对象
	
	void resetInspectArray();//重置检测列表
	
	bool detectWhetherCanPassBetweenTwoPoints(CCPoint p1, CCPoint p2);//检测2个位置中是否有障碍物
	
	void resetObjPosition();//重置玩家位置
	
	void clearPath();//清除路径

	void moveObj();//移动实现函数
};