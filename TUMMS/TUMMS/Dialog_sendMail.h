#pragma once


// CDialog_sendMail �Ի���

class CDialog_sendMail : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog_sendMail)

public:
	CDialog_sendMail(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialog_sendMail();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ����Ϣ�Ľ����˱��
	CString Sender_num;
	// ��Ϣ����
	CString Send_content;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCancel();
};
