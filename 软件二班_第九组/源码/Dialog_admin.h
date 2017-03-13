#pragma once


// CDialog_admin �Ի���

class CDialog_admin : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog_admin)

public:
	CDialog_admin(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialog_admin();
	void switchPages();

// �Ի�������
	enum { IDD = IDD_ADMIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	CButton* NewMyButton(int nID, CRect rect, int nStyle);
	CStatic* NewMyStatic(int nID, CString text, CRect rect, int nStyle);
	CEdit* NewMyEdit(int nID, CRect rect, int nStyle);
	CListCtrl* NewMyListCtrl(int nID, CRect rect, int nStyle);
	void CoutTheDetail_Order(CString);
	void CoutTheDetail_mail(CString);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton5();
	afx_msg void OnClickChangeInf();
	afx_msg void OnClickSaveChange();
	afx_msg void OnClickCancelChange();
	afx_msg void OnClickInfOfOrder(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickAgreeOrder();
	afx_msg void OnClickdisagreeOrder();
	afx_msg void OnClickInfOfMail(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickDelete_mail();
	afx_msg void OnClickSendMail();
public:
	CButton* b_personalInformation[3];   //������Ϣ���水ť
	CStatic* s_personalInformation[8];	//������Ϣ�������Ϣ��ʾ��̬�ı�
	CEdit* s_changeinformation[3];		//������Ϣ�޸Ľ���ı༭�ı���
	CListCtrl* l_order_c[3];
	CButton* b_orderCheck[2];
	CListCtrl* l_maillist[3];
	CStatic* s_mail[6];
	CButton* b_mail[4];
	CEdit* e_mail[2];
public:
	CString Change_name;
	CString Change_sex;
	CString Change_tel;
	CString memory;
	CString memory_1;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton6();
};
