
// MFCGame.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFCGameApp:
// �йش����ʵ�֣������ MFCGame.cpp
//

class CMFCGameApp : public CWinApp
{
public:
	CMFCGameApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFCGameApp theApp;