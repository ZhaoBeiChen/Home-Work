#pragma once
#include "afxwin.h"


// CAddFile �Ի���

class CAddFile : public CDialogEx
{
	DECLARE_DYNAMIC(CAddFile)

public:
	CAddFile(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddFile();

// �Ի�������
	enum { IDD = IDD_ADDFILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	// Դ�ļ�·��
	CEdit Control_pathEdit;
	// Դ�ļ�·��
	CString String_path;
	// �ļ���
	CString NewName;
	// �ļ���ʽ
	CComboBox Control_fileFormat;
	// �ļ���ʽ
	CString fileFormat;
	afx_msg void OnBnClickedLooks();
	afx_msg void OnBnClickedOk();
};
