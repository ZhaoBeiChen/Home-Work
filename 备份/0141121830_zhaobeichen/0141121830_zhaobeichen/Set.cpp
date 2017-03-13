// Set.cpp : 实现文件
//设置界面

#include "stdafx.h"
#include "0141121830_zhaobeichen.h"
#include "Set.h"
#include "afxdialogex.h"


// CSet 对话框

IMPLEMENT_DYNAMIC(CSet, CDialogEx)

CSet::CSet(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSet::IDD, pParent)
{

}

CSet::~CSet()
{
}

void CSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHOSE, Tab_chose_ctr);
}


BEGIN_MESSAGE_MAP(CSet, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_CHOSE, &CSet::OnSelchangeChose)
END_MESSAGE_MAP()


// CSet 消息处理程序


BOOL CSet::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	Tab_chose_ctr.InsertItem(0,"参数设置");
	Tab_chose_ctr.InsertItem(1, "文件添加");
	Tab_chose_ctr.InsertItem(2, "文件加密");
	Tab_chose_ctr.InsertItem(3, "关于");


	setPara_dia.Create(IDD_SET_PARA, GetDlgItem(IDC_CHOSE));
	addFile_dia.Create(IDD_ADDFILE, GetDlgItem(IDC_CHOSE));
	encry_dia.Create(IDD_DIALOG1, GetDlgItem(IDC_CHOSE));
	about_dia.Create(IDD_ABOUTBOX, GetDlgItem(IDC_CHOSE));
	CRect rs;

	Tab_chose_ctr.GetClientRect(&rs);

	rs.top += 30;
	rs.bottom -= 60;
	rs.left += 1;
	rs.right -= 2;

	setPara_dia.MoveWindow(&rs);
	addFile_dia.MoveWindow(&rs);
	encry_dia.MoveWindow(&rs);
	about_dia.MoveWindow(&rs);

	setPara_dia.ShowWindow(true);
	addFile_dia.ShowWindow(false);
	encry_dia.ShowWindow(false);
	about_dia.ShowWindow(false);

	Tab_chose_ctr.SetCurSel(0);




	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CSet::OnSelchangeChose(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码

	int CurSel = Tab_chose_ctr.GetCurSel();

	switch (CurSel)
	{
	case 0: 
		setPara_dia.ShowWindow(true);
		addFile_dia.ShowWindow(false);
		encry_dia.ShowWindow(false);
		about_dia.ShowWindow(false);
		break;
	case 1:
		setPara_dia.ShowWindow(false);
		addFile_dia.ShowWindow(true);
		encry_dia.ShowWindow(false);
		about_dia.ShowWindow(false);
		break;
	case 2:
		setPara_dia.ShowWindow(false);
		addFile_dia.ShowWindow(false);
		encry_dia.ShowWindow(true);
		about_dia.ShowWindow(false);
		break;
	case 3:
		setPara_dia.ShowWindow(false);
		addFile_dia.ShowWindow(false);
		encry_dia.ShowWindow(false);
		about_dia.ShowWindow(true);
		break;
	default:
		break;
	}

	*pResult = 0;
}
