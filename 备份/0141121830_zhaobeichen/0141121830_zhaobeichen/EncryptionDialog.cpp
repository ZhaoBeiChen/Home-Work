// EncryptionDialog.cpp : 实现文件
//加密界面对话框

#include "stdafx.h"
#include "0141121830_zhaobeichen.h"
#include "EncryptionDialog.h"
#include "afxdialogex.h"
#include "Encryption.h"
#include <Shlwapi.h>


// EncryptionDialog 对话框

IMPLEMENT_DYNAMIC(EncryptionDialog, CDialogEx)

EncryptionDialog::EncryptionDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(EncryptionDialog::IDD, pParent)
	, m_path(_T(""))
	, newFileName(_T(""))
	, Encry_format(_T(""))
{

}

EncryptionDialog::~EncryptionDialog()
{
}

void EncryptionDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ROOTFILE_PATH, m_path);
	DDX_Text(pDX, IDC_NEWNAME, newFileName);
	DDX_Control(pDX, IDC_NEWNAME, Control_newName);
	DDX_Control(pDX, IDC_MUSIC_FOR, Control_encry_format);
	DDX_CBString(pDX, IDC_MUSIC_FOR, Encry_format);
}


BEGIN_MESSAGE_MAP(EncryptionDialog, CDialogEx)
	ON_BN_CLICKED(IDC_LOOK, &EncryptionDialog::OnBnClickedLook)
	ON_BN_CLICKED(IDOK, &EncryptionDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// EncryptionDialog 消息处理程序


void EncryptionDialog::OnBnClickedLook()
{
	// TODO:  在此添加控件通知处理程序代码
	CFileDialog dlg(TRUE, "Text Files", "*.txt", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"text Files(*.txt)|All Files(*.*)|*.*||");
	if (dlg.DoModal() != IDOK)
	{
		return;
	}

	m_path = dlg.GetPathName();				//取文件名全称，包括完整路径。
	UpdateData(FALSE);
}


void EncryptionDialog::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if (m_path != "" && newFileName != "" && Encry_format != "")
	{

		Encryption lock;
		lock.OnEncryption(m_path, newFileName, Encry_format);  //加密
		MessageBox(CString("加密成功！"));

	}
	else{
	
		MessageBox(CString("输入内容不能为空！"));
	}
	
}




BOOL EncryptionDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	Control_encry_format.AddString("mp3");
	Control_encry_format.AddString("wma");

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
