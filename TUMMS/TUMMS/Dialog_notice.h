#pragma once


// CDialog_notice �Ի���

class CDialog_notice : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog_notice)

public:
	CDialog_notice(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialog_notice();

// �Ի�������
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString notice_title;
	CString notice_content;
	afx_msg void OnBnClickedButton1();
};
