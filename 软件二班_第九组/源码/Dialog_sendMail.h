#pragma once


// CDialog_sendMail 对话框

class CDialog_sendMail : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog_sendMail)

public:
	CDialog_sendMail(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialog_sendMail();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 该信息的接收人编号
	CString Sender_num;
	// 信息内容
	CString Send_content;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCancel();
};
