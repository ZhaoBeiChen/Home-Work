// Alert.cpp : 实现文件
//警告框

#include "stdafx.h"
#include "0141121830_zhaobeichen.h"
#include "Alert.h"
#include "afxdialogex.h"


// CAlert 对话框

IMPLEMENT_DYNAMIC(CAlert, CDialogEx)

CAlert::CAlert(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAlert::IDD, pParent)
{

}

CAlert::~CAlert()
{
}

void CAlert::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAlert, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAlert::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CAlert::OnBnClickedCancel)
END_MESSAGE_MAP()


// CAlert 消息处理程序


void CAlert::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	alert = true;
	CDialogEx::OnOK();
}


void CAlert::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	alert = false;
	CDialogEx::OnCancel();
}


bool CAlert::returnAlert(){

	return alert;
}
