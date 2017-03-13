#pragma once
#include "afxwin.h"


// CDialog_user 对话框

struct shop
{
	CString m_num;
	CString m_name;
	double price;
	int count;
	shop *next;
	void add(CString,  shop * &head);
	void deleted(CString, shop * &head);
	void change(CString, int, shop * &head);
	bool check(CString, shop * &head);
	void empty(shop * &head);
};


class CDialog_user : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog_user)

public:
	CDialog_user(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialog_user();

// 对话框数据
	enum { IDD = IDD_NORMAL_USER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
//	virtual BOOL OnInitDialog();
	CButton* NewMyButton(int nID, CRect rect, int nStyle);
	CStatic* NewMyStatic(int nID,CString text, CRect rect, int nStyle);
	CEdit* NewMyEdit(int nID, CRect rect, int nStyle);
	CListCtrl* NewMyListCtrl(int nID, CRect rect, int nStyle);
	BOOL PreTranslateMessage(MSG* pMsg);
	void SetListItemText();
	void CoutTheDetail(CString);
	void OnClickInfOfMaterial();
	void switchPages();
	void CoutTheDetail_Order(CString);
	void CoutTheDetail_mail(CString);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBackToLand();
	afx_msg void OnBnClickedPersonalInformationNormal();
public:
	CButton* b_personalInformation[3];   //个人信息界面按钮
	CStatic* s_personalInformation[8];	//个人信息界面的信息显示静态文本
	CEdit* s_changeinformation[3];		//个人信息修改界面的编辑文本框
	CListCtrl* l_materialInf[3];
	CStatic* s_materialInf[5];
	CButton* b_materialBuy[3];
	CListCtrl* l_maillist[3];
	CStatic* s_mail[6];
	CButton* b_mail[4];
	CEdit* e_mail[2];
	int listSelFlag[2];

	CStatic* s_order[11];
	CButton* b_order[3];
	CListCtrl* l_order;
	CListCtrl* l_order_m;
	afx_msg void OnBnClickedMaterialPurchase();
	afx_msg void OnBnClickedOrderFormCheck();
	afx_msg void OnBnClickedMailCaseNormal();
	afx_msg void OnEnChangeUsername();
	afx_msg void OnBnClickChangeMessage();
	afx_msg void OnClickSaveChange();
	afx_msg void OnClickCancelChange();
	afx_msg void OnClickInfOfMaterial(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickAddShopCar();
	afx_msg void OnClickDeleteShopCar();
	afx_msg void OnDBClickShopCar(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickCommitOrder();
	afx_msg void OnClickMakesureOrder();
	afx_msg void OnClickCancelOrder();
	afx_msg void OnClickInfOfOrder(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickDeleteOrder();
	afx_msg void OnClickDeleteOrder_m();
	afx_msg void OnClickInfOfMail(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickDelete_mail();
	afx_msg void OnClickSendMail();
	afx_msg void OnClickAccomplishOrder();

public:
	CString Change_name;
	CString Change_sex;
	CString Change_tel;
	CString memory;      //点击记录
	CString memory_1;
	shop* head;
	// 数量
	CEdit m_SubItemEdit;
	// 数量
	CString cstrItemTextEdit;
	virtual BOOL OnInitDialog();
	afx_msg void OnKillfocusEdit1();
	afx_msg void OnBnClickedChangepassword();
	CString user_notice;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


