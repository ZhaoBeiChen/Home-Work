#pragma once
#include "afxwin.h"
#include "stdafx.h"
#include "0141121830_zhaobeichen.h"

//返回特殊格式的时间
CString GetTime(int count){

	int M;
	int S;
	S = count % 60;
	M = count / 60;
	CString MM;
	CString SS;
	MM.Format(_T("%d"), M);
	SS.Format(_T("%d"), S);
	CString Fen("分");
	CString Miao("秒");
	return MM + Fen + SS + Miao;
}