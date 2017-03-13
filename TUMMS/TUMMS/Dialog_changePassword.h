#pragma once


// CDialog_changePassword 对话框

class CDialog_changePassword : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog_changePassword)

public:
	CDialog_changePassword(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialog_changePassword();
	bool check();

// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString old_password;
	CString new_password;
	CString makesure_password;
	afx_msg void OnBnClickedButton1();
};
