#pragma once


// CAlert_02 �Ի���

class CAlert_02 : public CDialogEx
{
	DECLARE_DYNAMIC(CAlert_02)

public:
	CAlert_02(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAlert_02();

// �Ի�������
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	bool makesure;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	bool returnChose();
};
