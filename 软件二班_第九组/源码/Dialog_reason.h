#pragma once


// Dialog_reason 对话框

class Dialog_reason : public CDialogEx
{
	DECLARE_DYNAMIC(Dialog_reason)

public:
	Dialog_reason(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Dialog_reason();
	CString GetReason();
	bool IfEmpty();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString Reason;
	bool tag;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
