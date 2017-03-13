#pragma once


// CAlert_02 对话框

class CAlert_02 : public CDialogEx
{
	DECLARE_DYNAMIC(CAlert_02)

public:
	CAlert_02(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAlert_02();

// 对话框数据
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	bool makesure;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	bool returnChose();
};
