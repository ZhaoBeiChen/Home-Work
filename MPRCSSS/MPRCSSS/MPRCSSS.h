
// MPRCSSS.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMPRCSSSApp: 
// �йش����ʵ�֣������ MPRCSSS.cpp
//

class CMPRCSSSApp : public CWinApp
{
public:
	CMPRCSSSApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMPRCSSSApp theApp;