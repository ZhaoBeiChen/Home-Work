#pragma once


// CAlert_01 �Ի���

class CAlert_01 : public CDialogEx
{
	DECLARE_DYNAMIC(CAlert_01)

public:
	CAlert_01(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAlert_01();

// �Ի�������
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	bool makesure;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	bool returnChose();
};
