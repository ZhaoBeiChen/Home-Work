#pragma once


// CAlert �Ի���

class CAlert : public CDialogEx
{
	DECLARE_DYNAMIC(CAlert)

public:
	CAlert(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAlert();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	bool alert;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	bool returnAlert();
};
