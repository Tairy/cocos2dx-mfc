//#ifndef _PADDLE_H_
//#define _PADDLE_H_
//
//#include "cocos2d.h"
//#include <functional>
////#include "stdafx.h"
////using namespace std;
//
//USING_NS_CC;
//
//typedef enum tagPaddleState 
//{
//	kPaddleStateGrabbed,
//	kPaddleStateUngrabbed
//} PaddleState; 
//enum OBJTYPE
//{
//	NONE_TYPE = 0,
//	CHAIR_LEFT = 1,
//	CHAIR_FRON = 2 ,
//	CHAIR_RIGHT = 3,
//	CHAIR_BACK = 4
//};
//class Paddle : public CCSprite, public CCTargetedTouchDelegate
//{
//public:
//	PaddleState        m_state;
//	bool m_isSelect;
//	bool m_enableSit;
//	bool m_enableTouch;
//	bool m_enablePickUp;
//	CCPoint m_terminal;
//	std::function<void(CCPoint, Paddle* )> m_selectCallback;
//	OBJTYPE m_type;
//	CCSprite* m_playerSprite;
//	CCSprite* m_chairPartSprite;
//public:
//	Paddle(void);
//	virtual ~Paddle(void);
//
//	CCRect rect();
//	bool initWithTexture();
//	virtual void onEnter();
//	virtual void onExit();
//	bool containsTouchLocation(CCPoint point);
//	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
//	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
//	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
//	virtual CCObject* copyWithZone(CCZone *pZone);
//
//	virtual void touchDelegateRetain();
//	virtual void touchDelegateRelease();
//
//	static Paddle* paddleWithContentSize(CCSize);//创建物体
//
//	void setSelect(bool isSelect);//选中时
//	void setOpacity(GLubyte opacity);
//	void sitChair();//坐下
//	void standUp();//站起
//	
//};
//
//#endif