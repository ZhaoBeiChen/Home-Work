// EncryptionDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "0141121830_zhaobeichen.h"
#include "EncryptionDialog.h"
#include "afxdialogex.h"
#include "Encryption.h"
#include <Shlwapi.h>


// EncryptionDialog �Ի���

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
	ON_EN_CHANGE(IDC_ROOTFILE_PATH, &EncryptionDialog::OnEnChangeRootfilePath)
END_MESSAGE_MAP()


// EncryptionDialog ��Ϣ�������


void EncryptionDialog::OnBnClickedLook()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(TRUE, "Text Files", "*.txt", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"text Files(*.txt)|All Files(*.*)|*.*||");
	if (dlg.DoModal() != IDOK)
	{
		return;
	}

	m_path = dlg.GetPathName();				//ȡ�ļ���ȫ�ƣ���������·����
	UpdateData(FALSE);
}


void EncryptionDialog::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	if (m_path != "" && newFileName != "" && Encry_format != "")
	{

		Encryption lock;
		lock.OnEncryption(m_path, newFileName, Encry_format);
		MessageBox(CString("���ܳɹ���"));

	}
	else{
	
		MessageBox(CString("�������ݲ���Ϊ�գ�"));
	}
	
}


void EncryptionDialog::OnEnChangeRootfilePath()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


BOOL EncryptionDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	Control_encry_format.AddString("mp3");
	Control_encry_format.AddString("wma");

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
