
#include "stdafx.h"
#include "Function.h"
#include <afx.h>


CString GetTime()
{
	CTime t = CTime::GetCurrentTime(); //��ȡϵͳ����
	int d = t.GetDay(); //��ü���
	int y = t.GetYear(); //��ȡ���
	int m = t.GetMonth(); //��ȡ��ǰ�·�

	CString year("��");
	CString month("��");
	CString day("��");

	CString ye, mo, da;
	ye.Format(_T("%d"), y);
	mo.Format(_T("%d"), m);
	da.Format(_T("%d"), d);

	CString time;
	time = ye + year + mo + month + da + day;

	return time;
}