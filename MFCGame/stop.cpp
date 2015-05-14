#include "StdAfx.h"
#include "stop.h"


stop::stop(float x, float y, float width, float height, CCString* name) {
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
	m_name = name;
}


stop::~stop(void) {
}
