// Alert_01.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "0141121830_zhaobeichen.h"
#include "Alert_01.h"
#include "afxdialogex.h"


// CAlert_01 �Ի���

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


// CAlert_01 ��Ϣ�������


void CAlert_01::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	makesure = true;
	CDialogEx::OnOK();
}


void CAlert_01::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	makesure = false;
	CDialogEx::OnCancel();
}

bool CAlert_01::returnChose(){

	return makesure;
}
