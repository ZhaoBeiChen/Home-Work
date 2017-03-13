#pragma once


// CAlert_01 对话框

class CAlert_01 : public CDialogEx
{
	DECLARE_DYNAMIC(CAlert_01)

public:
	CAlert_01(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAlert_01();

// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	bool makesure;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	bool returnChose();
};
