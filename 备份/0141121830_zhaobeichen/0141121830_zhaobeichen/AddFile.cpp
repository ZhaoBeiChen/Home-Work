// AddFile.cpp : 实现文件
//

#include "stdafx.h"
#include "0141121830_zhaobeichen.h"
#include "AddFile.h"
#include "afxdialogex.h"
#include "Alert.h"

extern CString workPath;

// CAddFile 对话框

IMPLEMENT_DYNAMIC(CAddFile, CDialogEx)

CAddFile::CAddFile(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddFile::IDD, pParent)
	, String_path(_T(""))
	, NewName(_T(""))
	, fileFormat(_T(""))
{

}

CAddFile::~CAddFile()
{
}

void CAddFile::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MUSICFILEPATH, Control_pathEdit);
	DDX_Text(pDX, IDC_MUSICFILEPATH, String_path);
	DDX_Text(pDX, IDC_MUSICNAME, NewName);
	DDX_Control(pDX, IDC_MUSICFOR, Control_fileFormat);
	DDX_CBString(pDX, IDC_MUSICFOR, fileFormat);
}


BEGIN_MESSAGE_MAP(CAddFile, CDialogEx)
	ON_BN_CLICKED(IDC_LOOKS, &CAddFile::OnBnClickedLooks)
	ON_BN_CLICKED(IDOK, &CAddFile::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddFile 消息处理程序


BOOL CAddFile::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	Control_fileFormat.AddString("mp3");
	Control_fileFormat.AddString("wma");


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

//浏览按钮
void CAddFile::OnBnClickedLooks()
{
	// TODO:  在此添加控件通知处理程序代码
	CFileDialog dlg(TRUE, "mp3 Files", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"(*.mp3;*.wma)|*.mp3;*.wma;||");
	if (dlg.DoModal() != IDOK)
	{
		return;
	}

	String_path = dlg.GetPathName();				//取文件名全称，包括完整路径。
	UpdateData(FALSE);
}


void CAddFile::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (String_path != "" && NewName != "" && fileFormat != ""){
		if (fileFormat == "mp3"){

			CString _mp3(".mp3");
			CString p;
			p = workPath;
			CString filePath("//re//mp3//");
			filePath = p + filePath + NewName + _mp3;
			bool FILE = CopyFile(String_path, filePath, TRUE);
			if (!FILE){

				CAlert alert;
				alert.DoModal();
				if (alert.returnAlert()){

					CopyFile(String_path, filePath, FALSE);
					MessageBox(CString("添加成功！"));
				}
			}
			else{

				MessageBox(CString("添加成功！"));
			}
		}
		else if (fileFormat == "wma"){

			CString _wma(".wma");
			CString p;
			p = workPath;
			CString filePath("//re//wma//");
			filePath = p + filePath + NewName + _wma;
			bool FILE = CopyFile(String_path, filePath, TRUE);
			if (!FILE){

				CAlert alert;
				alert.DoModal();
				if (alert.returnAlert()){

					CopyFile(String_path, filePath, FALSE);
					MessageBox(CString("添加成功！"));
				}
			}
			else{

				MessageBox(CString("添加成功！"));
			}
		}
	}
	else MessageBox(CString("内容不能为空！"));

}
