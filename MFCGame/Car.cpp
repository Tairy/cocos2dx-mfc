#include "stdafx.h"
#include "Car.h"

Car::Car(CCSprite* sprite):PathSprite(sprite)
{
	PathSprite* player_temp = new PathSprite(CCSprite::create("res\\Player.png"));
	player_temp->m_sprite->setAnchorPoint(CCPoint(0.5,0.5));
	sprite->addChild(player_temp->m_sprite);
	//is_busy = false;
}