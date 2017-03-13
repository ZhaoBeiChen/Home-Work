#pragma once
#include "afxwin.h"


// EncryptionDialog 对话框

class EncryptionDialog : public CDialogEx
{
	DECLARE_DYNAMIC(EncryptionDialog)

public:
	EncryptionDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~EncryptionDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 源文件路径
	CString m_path;
	// 加密文件命名
	CString newFileName;
	afx_msg void OnBnClickedLook();
	afx_msg void OnBnClickedOk();
	CEdit Control_newName;
	afx_msg void OnEnChangeRootfilePath();
	CComboBox Control_encry_format;
	CString Encry_format;
	virtual BOOL OnInitDialog();
};
