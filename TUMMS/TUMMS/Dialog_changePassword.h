#pragma once


// CDialog_changePassword �Ի���

class CDialog_changePassword : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog_changePassword)

public:
	CDialog_changePassword(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialog_changePassword();
	bool check();

// �Ի�������
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString old_password;
	CString new_password;
	CString makesure_password;
	afx_msg void OnBnClickedButton1();
};
