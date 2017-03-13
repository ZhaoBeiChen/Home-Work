
#include "stdafx.h"
#include "Function.h"
#include <afx.h>


CString GetTime()
{
	CTime t = CTime::GetCurrentTime(); //获取系统日期
	int d = t.GetDay(); //获得几号
	int y = t.GetYear(); //获取年份
	int m = t.GetMonth(); //获取当前月份

	CString year("年");
	CString month("月");
	CString day("日");

	CString ye, mo, da;
	ye.Format(_T("%d"), y);
	mo.Format(_T("%d"), m);
	da.Format(_T("%d"), d);

	CString time;
	time = ye + year + mo + month + da + day;

	return time;
}