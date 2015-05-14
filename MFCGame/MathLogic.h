//
//  MathLogic.h
//  MapGame
//
//  Created by TinyUlt on 14/10/11.
//
//

#ifndef __MapGame__MathLogic__
#define __MapGame__MathLogic__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class MathLogic
{
public:
	//线性方程 一元二次方法 求y
	static float linearEquationWithOneUnknown_solveYRequiredX(CCPoint knownPoint1, CCPoint knownPoint2, float x)
	{
		float _x1 = knownPoint1.x;
		float _y1 = knownPoint1.y;
		float _x2 = knownPoint2.x;
		float _y2 = knownPoint2.y;
		float m_p1 = (_y1 -_y2)/(_x1-_x2);
		float m_p2 = _y1 - m_p1 * _x1;
		//         float m_p1 = (knownPoint1.y -knownPoint2.y)/(knownPoint1.x-knownPoint2.x);
		//         float m_p2 = knownPoint1.y - m_p1 * knownPoint1.x;

		return m_p1* x + m_p2;
	}

	//线性方程 一元二次方法 求x
	static float linearEquationWithOneUnknown_solveXRequiredY(CCPoint knownPoint1, CCPoint knownPoint2, float y)
	{
		float _x1 = knownPoint1.x;
		float _y1 = knownPoint1.y;
		float _x2 = knownPoint2.x;
		float _y2 = knownPoint2.y;
		float m_p1 = (_y1 -_y2)/(_x1-_x2);
		float m_p2 = _y1 - m_p1 * _x1;
		//         float m_p1 = (knownPoint1.y -knownPoint2.y)/(knownPoint1.x-knownPoint2.x);
		//         float m_p2 = knownPoint1.y - m_p1 * knownPoint1.x;

		return (y - m_p2)/m_p1;
	}

	//求点到直线最短路径长度
	static float linearEquationWithOneUnknown_solveShortLenghtRequiredPoint(CCPoint knownPoint1, CCPoint knownPoint2, CCPoint point)
	{
		if ((point.x == knownPoint1.x && point.y == knownPoint1.y) || (point.x == knownPoint2.x && point.y == knownPoint2.y))
		{
			return 0;
		}

		float _x1 = knownPoint1.x;
		float _y1 = knownPoint1.y;
		float _x2 = knownPoint2.x;
		float _y2 = knownPoint2.y;
		float m_p1 = (_y1 -_y2)/(_x1-_x2);
		float m_p2 = _y1 - m_p1 * _x1;

		CCPoint p1((point.y - m_p2)/m_p1, point.y);
		CCPoint p2(point.x, m_p1* point.x + m_p2);
		float offsetY = abs( p2.y - point.y);
		float offsetX = abs(p1.x - point.x);

		if (offsetX == 0 && offsetY == 0)
		{
			return 0;
		}


		return offsetX * offsetY / calculateLengthRequiredTwoPoint(p1, p2);
	}

	//计算2点距离
	static float calculateLengthRequiredTwoPoint(CCPoint p1, CCPoint p2)
	{
		float _offsetX = abs( p1.x - p2.x);
		float _offsetY =abs(  p1.y - p2.y);
		return sqrt(_offsetX * _offsetX + _offsetY * _offsetY);
	}

	//绝对值
	static float abs(float value)
	{
		return value>0?value:-value;
	}
};
#endif /* defined(__MapGame__MathLogic__) */
