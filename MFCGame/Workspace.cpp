#include "StdAfx.h"
#include "Workspace.h"


Workspace::Workspace(float x, float y, float width, float height, CCString* name) {
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
	m_name = name;
}


Workspace::~Workspace(void)
{
}
