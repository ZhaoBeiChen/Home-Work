// Alert_02.cpp : 实现文件
//

#include "stdafx.h"
#include "0141121830_zhaobeichen.h"
#include "Alert_02.h"
#include "afxdialogex.h"


// CAlert_02 对话框

IMPLEMENT_DYNAMIC(CAlert_02, CDialogEx)

CAlert_02::CAlert_02(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAlert_02::IDD, pParent)
{

}

CAlert_02::~CAlert_02()
{
}

void CAlert_02::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAlert_02, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAlert_02::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CAlert_02::OnBnClickedCancel)
END_MESSAGE_MAP()


// CAlert_02 消息处理程序


void CAlert_02::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	makesure = true;
	CDialogEx::OnOK();
}


void CAlert_02::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	makesure = false;
	CDialogEx::OnCancel();
}

bool CAlert_02::returnChose(){

	return makesure;
}
