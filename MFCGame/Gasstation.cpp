#include "StdAfx.h"
#include "Gasstation.h"


Gasstation::Gasstation(float x, float y, float width, float height, CCString* name) {
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
	m_name = name;
}


Gasstation::~Gasstation(void)
{
}
