#pragma once
#include "afxwin.h"
#include "stdafx.h"
#include "0141121830_zhaobeichen.h"
#include  <direct.h>  
#include  <stdio.h> 

//���������ʽ��ʱ��
CString GetTime(int count){

	int M;
	int S;
	S = count % 60;
	M = count / 60;
	CString MM;
	CString SS;
	MM.Format(_T("%d"), M);
	SS.Format(_T("%d"), S);
	CString Fen("��");
	CString Miao("��");
	return MM + Fen + SS + Miao;
}

CString GetPath(){

	char buffer[MAX_PATH];
	_getcwd(buffer, MAX_PATH);
	CString path(buffer);
	return path;
}