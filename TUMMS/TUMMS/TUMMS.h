
// TUMMS.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "TUMMSDlg.h"


// CTUMMSApp: 
// �йش����ʵ�֣������ TUMMS.cpp
//

class CTUMMSApp : public CWinApp
{
public:
	CTUMMSApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTUMMSApp theApp;


class control
{
public:
	static Land land;
	//static void Tranland(CString userName, CString sex, CString tel );
	//static Land* GetUser();

};
