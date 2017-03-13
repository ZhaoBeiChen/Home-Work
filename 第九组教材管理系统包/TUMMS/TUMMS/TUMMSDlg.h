
// TUMMSDlg.h : ͷ�ļ�
//

#pragma once
#include "DBOperation.h"


// CTUMMSDlg �Ի���
class CTUMMSDlg : public CDialog
{
// ����
public:
	CTUMMSDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TUMMS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	int USER_ID;
	

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedNormalUser();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedManageUser();
	afx_msg void OnBnClickedLandButton();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);


	// �û�������û���
	CString userName;
	// �û����������
	CString passWord;
	afx_msg void OnEnChangePassword();
	afx_msg void OnEnChangeUsername();
	CString the_notice_title;
	CString the_notice_content;
};

class Land
{
	CString UserName;
	CString Sex;
	CString Tel;
	CString Number;
	CString tag;
public:
	void Input(CString userName, CString sex, CString tel, CString number);
	bool check(CString userName, CString passWord, int USER_ID);
	void Input_tag(CString);
	CString returnUsername();
	CString returnSex();
	CString returnTel();
	CString returnNumber();
	CString returnTag();
};
