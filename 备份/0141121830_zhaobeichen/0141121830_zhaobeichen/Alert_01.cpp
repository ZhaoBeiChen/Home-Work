// Alert_01.cpp : 实现文件
//

#include "stdafx.h"
#include "0141121830_zhaobeichen.h"
#include "Alert_01.h"
#include "afxdialogex.h"


// CAlert_01 对话框

IMPLEMENT_DYNAMIC(CAlert_01, CDialogEx)

CAlert_01::CAlert_01(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAlert_01::IDD, pParent)
{

}

CAlert_01::~CAlert_01()
{
}

void CAlert_01::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAlert_01, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAlert_01::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CAlert_01::OnBnClickedCancel)
END_MESSAGE_MAP()


// CAlert_01 消息处理程序


void CAlert_01::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	makesure = true;
	CDialogEx::OnOK();
}


void CAlert_01::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	makesure = false;
	CDialogEx::OnCancel();
}

bool CAlert_01::returnChose(){

	return makesure;
}
