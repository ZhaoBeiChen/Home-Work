#pragma once


// Dialog_reason �Ի���

class Dialog_reason : public CDialogEx
{
	DECLARE_DYNAMIC(Dialog_reason)

public:
	Dialog_reason(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Dialog_reason();
	CString GetReason();
	bool IfEmpty();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString Reason;
	bool tag;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
