#pragma once
#include "afxwin.h"


// CAddFile 对话框

class CAddFile : public CDialogEx
{
	DECLARE_DYNAMIC(CAddFile)

public:
	CAddFile(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddFile();

// 对话框数据
	enum { IDD = IDD_ADDFILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	// 源文件路径
	CEdit Control_pathEdit;
	// 源文件路径
	CString String_path;
	// 文件名
	CString NewName;
	// 文件格式
	CComboBox Control_fileFormat;
	// 文件格式
	CString fileFormat;
	afx_msg void OnBnClickedLooks();
	afx_msg void OnBnClickedOk();
};
