// Alert.cpp : ʵ���ļ�
//�����

#include "stdafx.h"
#include "0141121830_zhaobeichen.h"
#include "Alert.h"
#include "afxdialogex.h"


// CAlert �Ի���

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


// CAlert ��Ϣ�������


void CAlert::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	alert = true;
	CDialogEx::OnOK();
}


void CAlert::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	alert = false;
	CDialogEx::OnCancel();
}


bool CAlert::returnAlert(){

	return alert;
}
