// Alert_02.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "0141121830_zhaobeichen.h"
#include "Alert_02.h"
#include "afxdialogex.h"


// CAlert_02 �Ի���

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


// CAlert_02 ��Ϣ�������


void CAlert_02::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	makesure = true;
	CDialogEx::OnOK();
}


void CAlert_02::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	makesure = false;
	CDialogEx::OnCancel();
}

bool CAlert_02::returnChose(){

	return makesure;
}
