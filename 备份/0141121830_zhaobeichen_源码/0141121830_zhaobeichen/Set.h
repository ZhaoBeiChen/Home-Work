#pragma once
#include "afxcmn.h"
#include "SetPara.h"
#include "AddFile.h"
#include "EncryptionDialog.h"


// CSet 对话框

class CSet : public CDialogEx
{
	DECLARE_DYNAMIC(CSet)

public:
	CSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSet();

// 对话框数据
	enum { IDD = IDD_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// TabControl
	CTabCtrl Tab_chose_ctr;
	virtual BOOL OnInitDialog();

	CSetPara setPara_dia;
	CAddFile addFile_dia;
	EncryptionDialog encry_dia;
	afx_msg void OnSelchangeChose(NMHDR *pNMHDR, LRESULT *pResult);
};
