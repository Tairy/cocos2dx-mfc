#include "StdAfx.h"
//#include "Paddle.h"
////#include "FilePath.h"
//using namespace std;
//Paddle::Paddle(void):m_chairPartSprite(NULL), m_playerSprite(NULL),m_enableSit(false)
//{
//}
//
//Paddle::~Paddle(void)
//{
//}
//
//CCRect Paddle::rect()
//{
//	CCSize s = this->getContentSize();
//	return CCRectMake(this->getPositionX(),  this->getPositionY(), s.width, s.height);
//}
//
//Paddle* Paddle::paddleWithContentSize(CCSize size)
//{
//	Paddle* pPaddle = new Paddle();
//	pPaddle->initWithTexture();
//	pPaddle->setContentSize(size);
//
//	pPaddle->autorelease();
//
//	return pPaddle;
//}
//
//bool Paddle::initWithTexture()
//{
//	if( CCSprite::init() )
//	{
//		m_state = kPaddleStateUngrabbed;
//	}
//
//	return true;
//}
//
//void Paddle::onEnter()
//{
//	CCDirector* pDirector = CCDirector::sharedDirector();
//	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
//	CCSprite::onEnter();
//}
//
//void Paddle::onExit()
//{
//	CCDirector* pDirector = CCDirector::sharedDirector();
//	pDirector->getTouchDispatcher()->removeDelegate(this);
//	CCSprite::onExit();
//}    
//
//bool Paddle::containsTouchLocation(CCPoint point)
//{
//	//CCLog("%f, %f", convertToNodeSpaceAR(point).x, convertToNodeSpaceAR(point).y);
//	return rect().containsPoint((point));
//
//}
//
//bool Paddle::ccTouchBegan(CCTouch* touch, CCEvent* event)
//{
//	if (m_isSelect) {
//		setSelect(false);
//
//	}
//	auto nodePosition = this->getParent()->convertToNodeSpace( touch->getLocation() );
//	CCLog("%f, %f", nodePosition.x, nodePosition.y);
//	if (m_state != kPaddleStateUngrabbed) return false;
//	if ( !containsTouchLocation(nodePosition) ) return false;
//	CCLog("touchSuccess")  ;
//	m_state = kPaddleStateGrabbed;
//
//	setSelect(true);
//
//	if (m_selectCallback)
//	{
//		m_selectCallback(m_terminal, this);
//	}
//	
//	//sitChair();
//	
//
//	return true;
//}
//
//void Paddle::ccTouchMoved(CCTouch* touch, CCEvent* event)
//{
//	// If it weren't for the TouchDispatcher, you would need to keep a reference
//	// to the touch from touchBegan and check that the current touch is the same
//	// as that one.
//	// Actually, it would be even more complicated since in the Cocos dispatcher
//	// you get CCSets instead of 1 UITouch, so you'd need to loop through the set
//	// in each touchXXX method.
//
//	CCAssert(m_state == kPaddleStateGrabbed, "Paddle - Unexpected state!");    
//
//	// CCPoint touchPoint = touch->getLocation();
//
//	//setPosition( ccp(touchPoint.x, getPosition().y) );
//}
//
//CCObject* Paddle::copyWithZone(CCZone *pZone)
//{
//	this->retain();
//	return this;
//}
//
//void Paddle::ccTouchEnded(CCTouch* touch, CCEvent* event)
//{
//	CCAssert(m_state == kPaddleStateGrabbed, "Paddle - Unexpected state!");    
//
//	m_state = kPaddleStateUngrabbed;
//} 
//
//void Paddle::touchDelegateRetain()
//{
//	this->retain();
//}
//
//void Paddle::touchDelegateRelease()
//{
//	this->release();
//}
//
//void Paddle::setSelect(bool isSelect)
//{
//	CCArray* _array = this->getChildren();
//	CCObject *_obj;
//	m_isSelect = isSelect;
//	CCARRAY_FOREACH(_array, _obj )
//	{
//		CCSprite* _sp = (CCSprite *)_obj;
//		if (isSelect)
//		{
//			_sp->setColor(ccRED);
//		}
//		else
//		{
//			_sp->setColor(ccWHITE);
//
//		}
//
//	}
//
//
//}
//
//void Paddle::setOpacity( GLubyte opacity )
//{
//	CCArray* _array = this->getChildren();
//	CCObject *_obj;
//	CCARRAY_FOREACH(_array, _obj )
//	{
//		CCSprite* _sp = (CCSprite *)_obj;
//		_sp->setOpacity(opacity);
//	}
//}
//
//void Paddle::sitChair()
//{
//	switch (m_type)
//	{
//	case NONE_TYPE:
//		break;
//	case CHAIR_LEFT:
//		{
//			m_playerSprite = CCSprite::create(g_chair_left_player);
//			m_playerSprite->setAnchorPoint(CCPoint());
//			m_playerSprite->setPosition(CCPoint(-8,-15));
//			this->addChild(m_playerSprite, 100);
//
//			m_chairPartSprite= CCSprite::create(g_chair_left_part);
//			m_chairPartSprite->setAnchorPoint(CCPoint());
//			m_chairPartSprite->setPosition(CCPoint(-15,-5));
//			this->addChild(m_chairPartSprite, 100);
//			break;
//		}
//	case CHAIR_FRON:
//		break;
//	case CHAIR_RIGHT:
//		break;
//	case CHAIR_BACK:
//		{
//
//			m_playerSprite = CCSprite::create(g_chair_back_player);
//			m_playerSprite->setAnchorPoint(CCPoint());
//			m_playerSprite->setPosition(CCPoint(-15,-5));
//			this->addChild(m_playerSprite);
//			break;
//		}
//	default:
//		break;
//	}
//}
//
//void Paddle::standUp()
//{
//	if (m_playerSprite)
//	{
//		m_playerSprite->removeFromParentAndCleanup(true);
//		m_playerSprite = NULL;
//	}
//	if (m_chairPartSprite)
//	{
//		m_chairPartSprite->removeFromParentAndCleanup(true);
//		m_chairPartSprite = NULL;
//	}
//}