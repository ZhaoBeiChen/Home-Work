#pragma once


// CDialog_notice 对话框

class CDialog_notice : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog_notice)

public:
	CDialog_notice(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialog_notice();

// 对话框数据
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString notice_title;
	CString notice_content;
	afx_msg void OnBnClickedButton1();
};
