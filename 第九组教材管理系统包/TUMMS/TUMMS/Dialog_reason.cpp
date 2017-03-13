// Dialog_reason.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TUMMS.h"
#include "Dialog_reason.h"
#include "afxdialogex.h"


// Dialog_reason �Ի���

IMPLEMENT_DYNAMIC(Dialog_reason, CDialogEx)

Dialog_reason::Dialog_reason(CWnd* pParent /*=NULL*/)
	: CDialogEx(Dialog_reason::IDD, pParent)
	, Reason(_T(""))
{
	tag = false;
}

Dialog_reason::~Dialog_reason()
{
}

void Dialog_reason::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Reason);
}


BEGIN_MESSAGE_MAP(Dialog_reason, CDialogEx)
	ON_BN_CLICKED(IDOK, &Dialog_reason::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &Dialog_reason::OnBnClickedCancel)
END_MESSAGE_MAP()


// Dialog_reason ��Ϣ�������


CString Dialog_reason::GetReason()
{
	return Reason;
}




void Dialog_reason::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (!IfEmpty())
	{
		UpdateData(true);
		CDialogEx::OnOK();
	}
	else MessageBox(CString("����Ϊ�գ�"));
}

bool Dialog_reason::IfEmpty()
{
	UpdateData(true);
	if (Reason == "")
	{
		return true;
	}
	else return false;
}


void Dialog_reason::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	tag = true;
	CDialogEx::OnCancel();
}
