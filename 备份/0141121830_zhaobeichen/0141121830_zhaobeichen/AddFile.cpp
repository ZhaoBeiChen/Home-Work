// AddFile.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "0141121830_zhaobeichen.h"
#include "AddFile.h"
#include "afxdialogex.h"
#include "Alert.h"

extern CString workPath;

// CAddFile �Ի���

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


// CAddFile ��Ϣ�������


BOOL CAddFile::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	Control_fileFormat.AddString("mp3");
	Control_fileFormat.AddString("wma");


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

//�����ť
void CAddFile::OnBnClickedLooks()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(TRUE, "mp3 Files", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"(*.mp3;*.wma)|*.mp3;*.wma;||");
	if (dlg.DoModal() != IDOK)
	{
		return;
	}

	String_path = dlg.GetPathName();				//ȡ�ļ���ȫ�ƣ���������·����
	UpdateData(FALSE);
}


void CAddFile::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
					MessageBox(CString("��ӳɹ���"));
				}
			}
			else{

				MessageBox(CString("��ӳɹ���"));
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
					MessageBox(CString("��ӳɹ���"));
				}
			}
			else{

				MessageBox(CString("��ӳɹ���"));
			}
		}
	}
	else MessageBox(CString("���ݲ���Ϊ�գ�"));

}
