// Dialog_reason.cpp : 实现文件
//

#include "stdafx.h"
#include "TUMMS.h"
#include "Dialog_reason.h"
#include "afxdialogex.h"


// Dialog_reason 对话框

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


// Dialog_reason 消息处理程序


CString Dialog_reason::GetReason()
{
	return Reason;
}




void Dialog_reason::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	if (!IfEmpty())
	{
		UpdateData(true);
		CDialogEx::OnOK();
	}
	else MessageBox(CString("输入为空！"));
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
	// TODO:  在此添加控件通知处理程序代码
	tag = true;
	CDialogEx::OnCancel();
}
