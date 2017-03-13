#pragma once
#include "afxwin.h"


// CDialog_manage �Ի���

class CDialog_manage : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog_manage)

public:
	CDialog_manage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialog_manage();

// �Ի�������
	enum { IDD = IDD_MANAGE_USER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	CButton* NewMyButton(int nID, CRect rect, int nStyle);
	CStatic* NewMyStatic(int nID, CString text, CRect rect, int nStyle);
	CEdit* NewMyEdit(int nID, CRect rect, int nStyle);
	CListCtrl* NewMyListCtrl(int nID, CRect rect, int nStyle);
	CComboBox* NewMyComboBox(int nID, CRect rect, int nStyle);
	void CoutTheDetail(CString);
	void CoutTheDetail_material(CString num);
	void CoutTheDetail_press(CString num);
	bool CheckNumInDB(CString);
	bool CheckNumInDB_material(CString);
	bool CheckNumInDB_press(CString);
	void CoutTheDetail_mail(CString);
	void CoutTheDetail_Order(CString);
	void CoutTheDetail_notice(CString);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedPersonalInformationNormal();
	afx_msg void OnClickSaveChange();
	afx_msg void OnClickCancelChange();
	afx_msg void OnClickCancelChange_1();
	afx_msg void OnClickAddPerson();
	afx_msg void OnClickSaveAddPerson();
	afx_msg void OnClickAddMaterial();
	afx_msg void OnClickSaveAddMaterial();
	afx_msg void OnClickAddPress();
	afx_msg void OnClickSaveAddPress();
	afx_msg void OnClickInfOfMail(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickDelete_mail();
	afx_msg void OnClickSendMail();
	afx_msg void OnClickAgreeOrder();
	afx_msg void OnClickdisagreeOrder();
public:
	CButton* b_personalInformation[3];   //������Ϣ���水ť
	CStatic* s_personalInformation[8];	//������Ϣ�������Ϣ��ʾ��̬�ı�
	CEdit* s_changeinformation[3];		//������Ϣ�����޸��ı���
	CListCtrl* l_personInf[3];			//��Ա���������Ա�б�
	CStatic* s_person_inf[12];			//��Ա������澲̬�ı�
	CButton* b_person_information[6];	//��Ա������水ť
	CEdit* s_changePerson_inf[6];		//��Ա��������ı��༭��
	CComboBox* c_changePerson_inf[3];
	CButton* b_changeMaterial[3];
	CListCtrl* l_maillist[3];
	CStatic* s_mail[6];
	CButton* b_mail[4];
	CEdit* e_mail[2];
	CListCtrl* l_order_c[3];
	CButton* b_orderCheck[3];
	CButton* b_notice[4];
	

	//������Ϣ�޸Ľ���ı༭�ı���
	void switchPages();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnClickInfOfPerson(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickInfOfMaterial(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickInfOfPress(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickChangePerson();
	afx_msg void OnClickSavePersonChange();
	afx_msg void OnClickDeletePerson();
	afx_msg void OnClickChangeMaterial();
	afx_msg void OnClickSaveMaterialChange();
	afx_msg void OnClickCancelChange_2();
	afx_msg void OnClickDeleteMaterial();
	afx_msg void OnClickChangePress();
	afx_msg void OnClickSavePressChange();
	afx_msg void OnClickCancelChange_3();
	afx_msg void OnClickDeletePress();
	afx_msg void OnClickInfOfOrder(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickInfOfOrder_accomplish(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickAccomplishDis();
	afx_msg void OnClickInfOfNotice(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickDelete_notice();
	afx_msg void OnClickAddNotice();
	afx_msg void OnClickPublishNotice();
	afx_msg void OnClickBackNotice();
public:
	CString Change_name;
	CString Change_sex;
	CString Change_tel;
	CString Change_num;
	CString Change_academy;
	CString Change_teaching;
	CString Change_author;
	CString Change_price;
	CString Change_isbn;
	CString Change_bbc;
	CString Change_address;

	CString Special_num;
	CString Special_name;
	CString Special_sex;
	CString Special_tel;
	CString Special_academy;
	CString Special_teaching;
	CString Special_author;
	CString Special_price;
	CString Special_isbn;
	CString Special_bbc;
	CString Special_address;

	CString memory;      //�����¼
	CString memory_1;
//	CStatic m_person_static;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton9();
};
