
// 0141121830_zhaobeichen.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy0141121830_zhaobeichenApp: 
// �йش����ʵ�֣������ 0141121830_zhaobeichen.cpp
//

class CMy0141121830_zhaobeichenApp : public CWinApp
{
public:
	CMy0141121830_zhaobeichenApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy0141121830_zhaobeichenApp theApp;
