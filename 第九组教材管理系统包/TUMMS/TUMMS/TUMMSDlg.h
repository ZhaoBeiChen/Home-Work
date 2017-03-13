
// TUMMSDlg.h : 头文件
//

#pragma once
#include "DBOperation.h"


// CTUMMSDlg 对话框
class CTUMMSDlg : public CDialog
{
// 构造
public:
	CTUMMSDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TUMMS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	int USER_ID;
	

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedNormalUser();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedManageUser();
	afx_msg void OnBnClickedLandButton();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);


	// 用户输入的用户名
	CString userName;
	// 用户输入的密码
	CString passWord;
	afx_msg void OnEnChangePassword();
	afx_msg void OnEnChangeUsername();
	CString the_notice_title;
	CString the_notice_content;
};

class Land
{
	CString UserName;
	CString Sex;
	CString Tel;
	CString Number;
	CString tag;
public:
	void Input(CString userName, CString sex, CString tel, CString number);
	bool check(CString userName, CString passWord, int USER_ID);
	void Input_tag(CString);
	CString returnUsername();
	CString returnSex();
	CString returnTel();
	CString returnNumber();
	CString returnTag();
};
