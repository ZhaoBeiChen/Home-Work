#pragma once
#include "afxwin.h"


// EncryptionDialog �Ի���

class EncryptionDialog : public CDialogEx
{
	DECLARE_DYNAMIC(EncryptionDialog)

public:
	EncryptionDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~EncryptionDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// Դ�ļ�·��
	CString m_path;
	// �����ļ�����
	CString newFileName;
	afx_msg void OnBnClickedLook();
	afx_msg void OnBnClickedOk();
	CEdit Control_newName;
	afx_msg void OnEnChangeRootfilePath();
	CComboBox Control_encry_format;
	CString Encry_format;
	virtual BOOL OnInitDialog();
};
