#include "StdAfx.h"
#include "PathSearchInfo.h"

PathSearchInfo::PathSearchInfo( CCTMXTiledMap* tiledMap )
{
	memset(m_inspectArray, NULL, MAP_WIDTH*MAP_HEIGHT*sizeof(PathSprite*));
	m_isSetMoveDoneCallback = false;
	m_isSetDrawPathCallback = false;
	m_isSetSelectObjCallback = false;
	m_enableMove = true;

	m_map = tiledMap;
	m_mapSize = m_map->getMapSize();//获取地图的尺寸 地图单位
	m_tileSize = m_map->getTileSize();//获取瓦片的尺寸  世界单位
	m_road = m_map->layerNamed("road");//行走路径的地图

	for (int j = 0;  j < m_mapSize.height; j++) {
		for (int i = 0;  i < m_mapSize.width; i++) {
			CCSprite* _sp = m_road->tileAt(CCPoint(i, j));
			if (_sp) {
				PathSprite* _pathSprite = new PathSprite(_sp);
				_pathSprite->m_x = i;
				_pathSprite->m_y = j;

				m_inspectArray[i][j] = _pathSprite;//把地图中所有的点一一对应放入检测列表中
			}
		}
	}	
}

void PathSearchInfo::setMoveDoneCallback( function<void(CCPoint)>& pFunc )
{
	m_moveDone = pFunc;
	m_isSetMoveDoneCallback = true;
}

void PathSearchInfo::setDrawPathCallback( function<void(vector<PathSprite*>)>& pFunc )
{
	m_drawPath = pFunc;
	m_isSetDrawPathCallback = true;
}

//void PathSearchInfo::setSelectCallback( function<void(CCPoint point, Paddle* selectObj)> &pFunc )
//{
//	m_selectObj = pFunc;
//	m_isSetSelectObjCallback = true;
//}

//void PathSearchInfo::initMapObject( const char* layerName, const char* objName )
//{
//	//图片层
//	CCTMXLayer* _layer = m_map->layerNamed(layerName);
//	if (!_layer)
//	{
//		return;
//	}
//	//对象层
//	CCTMXObjectGroup* pipeGroup = m_map->objectGroupNamed(objName);
//	if (!pipeGroup)
//	{
//		return;
//	}
//	//得到所有的对象
//	CCArray* _array = pipeGroup->getObjects();
//	CCObject *_obj;
//	CCARRAY_FOREACH(_array, _obj )
//	{
//		//得一个
//		CCDictionary* _dictionary  = (CCDictionary*)_obj;
//
//		//得到属性
//		float _x = ((CCString*)_dictionary->objectForKey("x"))->floatValue();//世界单位
//		float _y= ((CCString*)_dictionary->objectForKey("y"))->floatValue();
//		float _width = ((CCString*)_dictionary->objectForKey("width"))->floatValue();//世界单位
//		float _height = ((CCString*)_dictionary->objectForKey("height"))->floatValue();
//		CCString* _name = ((CCString*)_dictionary->objectForKey("name"));
//
//		Workspace _worksapce(_x, _y, _width, _height, _name);
//
//		//CCString* _terminalX = ((CCString*)_dictionary->objectForKey("terminalX"));//终点x坐标
//		//CCString* _terminalY = ((CCString*)_dictionary->objectForKey("terminalY"));//终点y坐标
//		//CCString* _type = ((CCString*)_dictionary->objectForKey("type"));//物体类型
//		//CCString* _enableSit = ((CCString*)_dictionary->objectForKey("enableSit"));//是否能坐下
//		//CCString* _enableTouch =(( CCString*)_dictionary->objectForKey("enableTouch"));//是否能触摸
//		//CCString* _enablePickUp =(( CCString*)_dictionary->objectForKey("enablePickUp"));//是否能触摸
//
//		//Paddle* _parent = Paddle::paddleWithContentSize(CCSize(_widht, _height));//创建一个物体类
//
//		//设置物体属性
//		/*if (_terminalX && _terminalY)
//		{
//			_parent->m_terminal = CCPoint( _terminalX->floatValue(), _terminalY->floatValue());
//			if (m_isSetSelectObjCallback)
//			{
//				_parent->m_selectCallback =m_selectObj;
//			}
//
//		}
//		else
//		{
//			_parent->m_terminal = CCPoint(-1, -1);
//		}*/
//		/*_parent->m_type = _type?  (OBJTYPE)_type->intValue():NONE_TYPE;
//		_parent->m_enableSit = _enableSit? _enableSit->boolValue():false;
//		_parent->m_enableTouch = _enableTouch?_enableTouch->boolValue():false;
//		if (_enablePickUp)
//		{
//			_parent->m_enablePickUp = _enablePickUp->boolValue();
//			_parent->m_selectCallback =m_selectObj;
//		}
//		else
//		{
//			_parent->m_enablePickUp =false;
//		}*/
//		//设置物体位置
////		CCPoint _offset = CCPoint(_x, _y  );//偏移量
////		_parent->setPosition(_offset);
////		_parent->setAnchorPoint(CCPoint(0,0));
////
////		for (int i = 0; i < _widht/m_tileSize.width; i++)
////		{
////			for (int j = 0; j < _height/m_tileSize.height; j++)
////			{
////				CCSprite* _Sprite = _layer->tileAt(CCPoint(_x/m_tileSize.width+i,m_mapSize.height-1-_y/m_tileSize.height-j));
////				if (_Sprite)
////				{
////
////					_Sprite->retain();
////					_Sprite->removeFromParent();
////					_Sprite->setPosition(_Sprite->getPosition()-_offset);
////					_parent->addChild(_Sprite);
////					_Sprite->release();
////
////#if 0//测试该物体
////					CCMoveBy* action = CCMoveBy::create(1,CCPoint(0,50));
////					CCMoveBy* actionR = CCMoveBy::create(1,CCPoint(0,-50));
////					CCSequence* seq = CCSequence::create(action, actionR, NULL);
////					_Sprite->runAction(CCRepeatForever::create(seq));
////#endif
////
////				}
////
////			}
////		}
////
////		//设置对象深度
////		if (_parent->m_enablePickUp)
////		{
////			m_map->addChild(_parent, BASE_ZODER - getWorldPositionByMapPosition(m_mapSize).y  );
////		}
////		else
////		{
////			m_map->addChild(_parent, BASE_ZODER - _y );
////		}
////		
////
//	}
//} 

void PathSearchInfo::pathFunction( CCPoint point, PathSprite* obj )
{
	if (!m_enableMove)
	{
		return;
	}
	if (point.x <0 || point.y<0)
	{
		return;
	}
	// 		if (m_moveDone())//判断是否到达目的地
	// 		{
	// 			return;
	// 		}
	//m_moveDone();//判断是否到达目的地
	m_moveObj = obj;
	resetObjPosition();
	clearPath();

	PathSprite*_sp = m_inspectArray[(int)point.x][(int)(point.y)];
	if (_sp) {

		//获取触摸点, 设置为终点
		obj->m_endX = _sp->m_x;
		obj->m_endY = _sp->m_y;
		//计算路径
		calculatePath();

		resetInspectArray();
		//移动物体
		moveObj();

		//绘制路径
		if (m_isSetDrawPathCallback)
		{
			m_drawPath(m_pathList);
		}
	}

}

void PathSearchInfo::calculatePath()
{
#ifdef PRECISE_SEARCH_PATH
	//得到开始点的节点
	PathSprite*    _endNode= m_inspectArray[m_moveObj->m_startX][m_moveObj->m_startY];
	//得到结束点的节点
	PathSprite*   _startNode = m_inspectArray[m_moveObj->m_endX][m_moveObj->m_endY];

	//因为是开始点 把到起始点的距离设为0, F值也为0
	_startNode->m_costToSource = 0;
	_startNode->m_FValue = 0;

	//把已经检测过的点从检测列表中删除
	m_inspectArray[m_moveObj->m_endX][m_moveObj->m_endY] = NULL;
	//把该点放入已经检测过点的列表中
	m_haveInspectList.push_back(_startNode);
	//然后加入开放列表
	m_openList.push_back(_startNode);

	PathSprite* _node = NULL;
	while (true)
	{
		//得到离起始点最近的点(如果是第一次执行, 得到的是起点)
		_node = getMinPathFormOpenList();
		if (!_node)
		{
			//找不到路径
			break;
		}
		//把计算过的点从开放列表中删除
		removeObjFromOpenList( _node);
		int _x = _node->m_x;
		int _y = _node->m_y;

		//
		if (_x ==m_moveObj->m_startX && _y == m_moveObj->m_startY)
		{
			break;
		}

		//检测8个方向的相邻节点是否可以放入开放列表中


		PathSprite* _adjacent = NULL;




		_adjacent = getObjFromInspectArray(  _x +1, _y);
		inspectTheAdjacentNodes(_node, _adjacent, _endNode);

		_adjacent = getObjFromInspectArray(  _x , _y -1);
		inspectTheAdjacentNodes(_node, _adjacent, _endNode);

		_adjacent = getObjFromInspectArray(  _x -1, _y);
		inspectTheAdjacentNodes(_node, _adjacent, _endNode);

		_adjacent = getObjFromInspectArray(  _x , _y+1);
		inspectTheAdjacentNodes(_node, _adjacent, _endNode);


		_adjacent = getObjFromInspectArray( _x + 1, _y + 1);
		inspectTheAdjacentNodes(_node, _adjacent, _endNode);

		_adjacent = getObjFromInspectArray(  _x +1, _y-1);
		inspectTheAdjacentNodes(_node, _adjacent, _endNode);

		_adjacent = getObjFromInspectArray(  _x -1, _y - 1);
		inspectTheAdjacentNodes(_node, _adjacent, _endNode);

		_adjacent = getObjFromInspectArray(  _x -1, _y+1);
		inspectTheAdjacentNodes(_node, _adjacent, _endNode);


	}

	while (_node)
	{
		//把路径点加入到路径列表中
		//m_pathList.insert(m_pathList.begin(), _node);
		m_pathList.push_back(_node);
		_node = _node->m_parent;
	}
#else

	//得到开始点的节点
	PathSprite*   _startNode = m_inspectArray[m_moveObj->m_startX][m_moveObj->m_startY];
	//得到结束点的节点
	PathSprite*  _endNode = m_inspectArray[m_moveObj->m_endX][m_moveObj->m_endY];

	//因为是开始点 把到起始点的距离设为0, F值也为0
	_startNode->m_costToSource = 0;
	_startNode->m_FValue = 0;

	//把已经检测过的点从检测列表中删除
	m_inspectArray[m_moveObj->m_startX][m_moveObj->m_startY] = NULL;
	//把该点放入已经检测过点的列表中
	m_haveInspectList.push_back(_startNode);
	//然后加入开放列表
	m_openList.push_back(_startNode);

	PathSprite* _node = NULL;
	while (true)
	{
		//得到离起始点最近的点(如果是第一次执行, 得到的是起点)
		_node = getMinPathFormOpenList();
		if (!_node)
		{
			//找不到路径
			break;
		}
		//把计算过的点从开放列表中删除
		removeObjFromOpenList( _node);
		int _x = _node->m_x;
		int _y = _node->m_y;

		//
		if (_x ==m_moveObj->m_endX && _y == m_moveObj->m_endY)
		{
			break;
		}

		//检测8个方向的相邻节点是否可以放入开放列表中


		PathSprite* _adjacent = NULL;




		_adjacent = getObjFromInspectArray(  _x +1, _y);
		inspectTheAdjacentNodes(_node, _adjacent, _endNode);

		_adjacent = getObjFromInspectArray(  _x , _y -1);
		inspectTheAdjacentNodes(_node, _adjacent, _endNode);

		_adjacent = getObjFromInspectArray(  _x -1, _y);
		inspectTheAdjacentNodes(_node, _adjacent, _endNode);

		_adjacent = getObjFromInspectArray(  _x , _y+1);
		inspectTheAdjacentNodes(_node, _adjacent, _endNode);


		_adjacent = getObjFromInspectArray( _x + 1, _y + 1);
		inspectTheAdjacentNodes(_node, _adjacent, _endNode);

		_adjacent = getObjFromInspectArray(  _x +1, _y-1);
		inspectTheAdjacentNodes(_node, _adjacent, _endNode);

		_adjacent = getObjFromInspectArray(  _x -1, _y - 1);
		inspectTheAdjacentNodes(_node, _adjacent, _endNode);

		_adjacent = getObjFromInspectArray(  _x -1, _y+1);
		inspectTheAdjacentNodes(_node, _adjacent, _endNode);


	}

	while (_node)
	{
		//把路径点加入到路径列表中
		m_pathList.insert(m_pathList.begin(), _node);
		//m_pathList.push_back(_node);
		_node = _node->m_parent;
	}
#endif // PRECISE_SEARCH_PATH


}

float PathSearchInfo::calculateTwoObjDistance( PathSprite* obj1, PathSprite* obj2 )
{

	float _x = abs(obj2->m_x - obj1->m_x);
	float _y = abs(obj2->m_y - obj1->m_y);

	return _x + _y;
}

void PathSearchInfo::inspectTheAdjacentNodes( PathSprite* node, PathSprite* adjacent, PathSprite* endNode )
{
	if (adjacent)
	{
		float _x = abs(endNode->m_x - adjacent->m_x);
		float _y = abs(endNode->m_y - adjacent->m_y);

		float F , G, H1, H2, H3;
		adjacent->m_costToSource = node->m_costToSource + calculateTwoObjDistance(node, adjacent);//获得累计的路程
		G = adjacent->m_costToSource;

		//三种算法, 感觉H2不错
		H1 = _x + _y;
		H2 = hypot(_x, _y);
		H3 = max(_x, _y);

#if 1 //A*算法 = Dijkstra算法 + 最佳优先搜索
		F = G + H1;
#endif
#if 0//Dijkstra算法
		F = G;
#endif
#if 0//最佳优先搜索
		F = H2;
#endif
		adjacent->m_FValue = F;

		adjacent->m_parent = node;//设置父节点
		adjacent->m_sprite->setColor(ccORANGE);//搜寻过的节点设为橘色(测试用)
		m_haveInspectList.push_back(adjacent);
		node->m_child = adjacent;//设置子节点

		PathSearchInfo::m_inspectArray[adjacent->m_x][adjacent->m_y] = NULL;//把检测过的点从检测列表中删除
		PathSearchInfo::m_openList.push_back(adjacent);//加入开放列表
	}
}

PathSprite* PathSearchInfo::getMinPathFormOpenList()
{
	if (m_openList.size()>0) {
		PathSprite* _sp =* m_openList.begin();
		for (vector<PathSprite*>::iterator iter = m_openList.begin(); iter !=  m_openList.end(); iter++)
		{
			if ((*iter)->m_FValue < _sp->m_FValue)
			{
				_sp = *iter;
			}
		}
		return _sp;
	}
	else
	{
		return NULL;
	}

}

PathSprite* PathSearchInfo::getObjFromInspectArray( int x, int y )
{
	if (x >=0 && y >=0 && x < m_mapSize.width && y < m_mapSize.height) {
		return m_inspectArray[x][y];
	}
	return  NULL;
}

bool PathSearchInfo::removeObjFromOpenList( PathSprite* sprite )
{
	if (!sprite) {
		return  false;
	}
	for (vector<PathSprite*>::iterator iter = m_openList.begin(); iter !=  m_openList.end(); iter++)
	{
		if (*iter == sprite)
		{
			m_openList.erase(iter);
			return true;
		}
	}
	return false;

}  

cocos2d::CCPoint PathSearchInfo::getMapPositionByWorldPosition( CCPoint point )
{
	return CCPoint((int)(point.x/PathSearchInfo::m_tileSize.width),(int)(PathSearchInfo::m_mapSize.height - point.y/PathSearchInfo::m_tileSize.height) );
}

cocos2d::CCPoint PathSearchInfo::getWorldPositionByMapPosition( CCPoint point )
{
	return CCPoint(PathSearchInfo::m_tileSize.width * point.x, (PathSearchInfo::m_mapSize.height + point.y)*PathSearchInfo::m_tileSize.height);
}

void PathSearchInfo::resetInspectArray()
{
	for (vector<PathSprite*>::iterator iter = m_haveInspectList.begin(); iter != m_haveInspectList.end(); iter++)
	{
		//(*iter)->m_sprite->setColor(ccWHITE);
		(*iter)->m_costToSource = 0;
		(*iter)->m_FValue = 0;
		(*iter)->m_parent = NULL;
		(*iter)->m_child = NULL;

		m_inspectArray[(*iter)->m_x][(*iter)->m_y] = (*iter);
	}
}

bool PathSearchInfo::detectWhetherCanPassBetweenTwoPoints( CCPoint p1, CCPoint p2 )
{ 
	float _maxX = p1.x>p2.x?p1.x:p2.x;
	float _maxY = p1.y>p2.y?p1.y:p2.y;
	float _minX = p1.x<p2.x?p1.x:p2.x;
	float _minY = p1.y<p2.y?p1.y:p2.y;

	if (p1.x == p2.x)
	{
		if (_maxY - _minY >1)
		{
			return false;
		}
		float _x = p1.x;
		for (int _y = _minY; _y <=_maxY; _y++)
		{
			PathSprite*_sp = m_inspectArray[(int)_x][(int)(_y)];
			if (!_sp)
			{
				return false;
			} 
		}

	}
	else if (p1.y == p2.y)
	{
		if (_maxX - _minX > 1)
		{
			return false;
		}
		float _y = p1.y;
		for (int _x = _minX; _x <=_maxX; _x++ )
		{
			PathSprite*_sp = m_inspectArray[(int)_x][(int)(_y)];
			if (!_sp)
			{
				return false;
			} 
		}
	}
	else
	{
		for (int _y = _minY; _y <= _maxY; _y++)
		{
			for (int _x = _minX; _x <= _maxX; _x++)
			{
				float _length = MathLogic::linearEquationWithOneUnknown_solveShortLenghtRequiredPoint(p1, p2, CCPoint(_x, _y));
				float _maxLength = MathLogic::calculateLengthRequiredTwoPoint(CCPoint(0,0), CCPoint(0.5,0.5));
				if (_length < _maxLength)
				{
					PathSprite*_sp = m_inspectArray[(int)_x][(int)(_y)];
					if (!_sp)
					{
						return false;
					} 
				}

			}
		}
	}

	return true;
}

void PathSearchInfo::resetObjPosition(  )
{
#ifdef PRECISE_SEARCH_PATH

	CCPoint _point = getMapPositionByWorldPosition(m_moveObj->m_sprite->getPosition());
	CCSprite* _sp = m_road->tileAt(_point);

	if (_sp)
	{
		m_moveObj->m_x = _point.x;
		m_moveObj->m_y = _point.y;
	} 
	else
	{
		CCSprite* _up = m_road->tileAt(_point + CCPoint(0, -1));
		if (_up)
		{
			m_moveObj->m_x = _point.x;
			m_moveObj->m_y = _point.y - 1;
			return;
		}
		CCSprite* _down = m_road->tileAt(_point + CCPoint(0, 1));
		if (_down)
		{
			m_moveObj->m_x = _point.x;
			m_moveObj->m_y = _point.y +1;
			return;
		}
		CCSprite* _left = m_road->tileAt(_point + CCPoint(-1, 0));
		if (_left)
		{
			m_moveObj->m_x = _point.x -1;
			m_moveObj->m_y = _point.y ;
			return;
		}
		CCSprite* _right = m_road->tileAt(_point + CCPoint(1, 0));
		if (_right)
		{
			m_moveObj->m_x = _point.x + 1;
			m_moveObj->m_y = _point.y ;
			return;
		}

	}
#endif // PRECISE
}

void PathSearchInfo::clearPath(  )
{
	
	for (vector<PathSprite*>::iterator iter = m_haveInspectList.begin(); iter !=  m_haveInspectList.end(); iter++)
	{
		(*iter)->m_sprite->setColor(ccWHITE);
	}
	resetInspectArray();

	//把移除了障碍物的地图放入检测列表中
	//m_inspectList = m_mapList;
	m_openList.clear();
	m_pathList.clear();
	m_haveInspectList.clear();
	m_moveObj->m_startX = m_moveObj->m_x;
	m_moveObj->m_startY = m_moveObj->m_y;
	m_moveObj->m_sprite->stopAllActions();

	m_playerMoveStep = 0;
}

void PathSearchInfo::moveObj()
{
#ifndef PRECISE_SEARCH_PATH
	m_playerMoveStep++;
	m_isMoving = true;
	//如果运动完毕
	if (m_playerMoveStep >= m_pathList.size())
	{
		if (m_isSetMoveDoneCallback)
		{
			m_isMoving = false;
			m_moveDone(CCPoint((*(m_pathList.end()-1))->m_x, (*(m_pathList.end()-1))->m_y));
		}
		return;
	}
	//存储当前的移动进程
	m_moveObj->m_x = m_pathList[m_playerMoveStep]->m_x;
	m_moveObj->m_y = m_pathList[m_playerMoveStep]->m_y;

	//设置深度
	m_moveObj->m_sprite->setZOrder(BASE_ZODER - m_pathList[m_playerMoveStep]->m_sprite->getPositionY());

	//根据路径列表移动人物
	CCPoint _terminalPosition =  m_pathList[m_playerMoveStep]->m_sprite->getPosition()+m_tileSize/2;
	float _length =  MathLogic::calculateLengthRequiredTwoPoint(_terminalPosition,m_moveObj->m_sprite->getPosition());
	m_moveObj->m_sprite->runAction(CCSequence::create(CCMoveTo::create(MOVE_SPEED * _length,_terminalPosition), CCCallFunc::create(this, SEL_CallFunc(&PathSearchInfo::moveObj)), NULL));
#else
	m_isMoving = true;
	
	if (m_playerMoveStep == m_pathList.size()-1)
	{
		//sitChairJudge();
		if (m_isSetMoveDoneCallback)
		{
			m_isMoving = false;
			m_moveDone(CCPoint((*(m_pathList.end()-1))->m_x, (*(m_pathList.end()-1))->m_y));
		}
		return ;
	}

	for (int i = 1;i <= m_pathList.size() ;i++)
	{
		m_playerMoveStep = m_pathList.size()-i;

		if(detectWhetherCanPassBetweenTwoPoints(CCPoint(m_moveObj->m_x, m_moveObj->m_y), CCPoint(m_pathList[m_playerMoveStep]->m_x,m_pathList[m_playerMoveStep]->m_y)))
		{
			CCPoint _terminalPosition = m_pathList[m_playerMoveStep]->m_sprite->getPosition()+m_tileSize/2;
			float _length = MathLogic::calculateLengthRequiredTwoPoint(_terminalPosition,m_moveObj->m_sprite->getPosition());
			m_moveObj->m_sprite->runAction(CCSequence::create(CCMoveTo::create(MOVE_SPEED * _length,_terminalPosition), CCCallFunc::create(this, SEL_CallFunc(&PathSearchInfo::moveObj)), NULL));
			//存储当前的移动进程
			m_moveObj->m_x = m_pathList[m_playerMoveStep]->m_x;
			m_moveObj->m_y = m_pathList[m_playerMoveStep]->m_y;

			m_moveObj->m_sprite->setZOrder(BASE_ZODER - m_pathList[m_playerMoveStep]->m_sprite->getPositionY());

			break;
		}
	}


#endif
}