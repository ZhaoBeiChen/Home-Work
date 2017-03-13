// Dialog_admin.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TUMMS.h"
#include "Dialog_admin.h"
#include "afxdialogex.h"
#include "TUMMSDlg.h"
#include<string>
#include "Dialog_reason.h"
#include "Dialog_sendMail.h"
#include "Dialog_changePassword.h"
using namespace std;

extern control CONTROL;
extern CDBOperation dbOper;
extern bool bConn;
extern CRect rc;
// CDialog_admin �Ի���

IMPLEMENT_DYNAMIC(CDialog_admin, CDialogEx)

CDialog_admin::CDialog_admin(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialog_admin::IDD, pParent)
{

}

CDialog_admin::~CDialog_admin()
{
}

void CDialog_admin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialog_admin, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON5, &CDialog_admin::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialog_admin::OnBnClickedButton1)
	ON_BN_CLICKED(IDS_BUTTON_CHANGEADMIN_INF, &CDialog_admin::OnClickChangeInf)
	ON_BN_CLICKED(IDS_BUTTON_CHANGEADMIN_INF_1, &CDialog_admin::OnClickSaveChange)
	ON_BN_CLICKED(IDS_BUTTON_CHANGEADMIN_INF_2, &CDialog_admin::OnClickCancelChange)
	ON_BN_CLICKED(IDC_BUTTON2, &CDialog_admin::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDialog_admin::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CDialog_admin::OnBnClickedButton4)
	ON_NOTIFY(NM_CLICK, IDS_LISTCRTL_ADMIN_ORDERCHECK, OnClickInfOfOrder)
	ON_BN_CLICKED(IDS_BUTTON_ORDERCHECK_ADMIN, &CDialog_admin::OnClickAgreeOrder)
	ON_BN_CLICKED(IDS_BUTTON_ORDERCHECK_ADMIN_NO, &CDialog_admin::OnClickdisagreeOrder)
	ON_NOTIFY(NM_CLICK, IDS_LISTCTRL_USER_MAINLIST, OnClickInfOfMail)
	ON_BN_CLICKED(IDS_BUTTON_DELETEMAIL_USER, &CDialog_admin::OnClickDelete_mail)
	ON_BN_CLICKED(IDS_BUTTON_SENDMAIL_USER, &CDialog_admin::OnClickSendMail)
	ON_BN_CLICKED(IDC_BUTTON6, &CDialog_admin::OnBnClickedButton6)
END_MESSAGE_MAP()


// CDialog_admin ��Ϣ�������

CButton* CDialog_admin::NewMyButton(int nID, CRect rect, int nStyle)
{
	CString m_Caption;
	m_Caption.LoadString(nID); //ȡ��ť����
	CButton *p_Button = new CButton();
	ASSERT_VALID(p_Button);
	p_Button->Create(m_Caption, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | nStyle, rect, this, nID); //������ť
	CFont * f;
	f = new CFont;
	f->CreateFont(13, // nHeight 
		0, // nWidth 
		0, // nEscapement 
		0, // nOrientation 
		FW_BOLD, // nWeight 
		FALSE, // bItalic 
		FALSE, // bUnderline 
		0, // cStrikeOut 
		ANSI_CHARSET, // nCharSet 
		OUT_DEFAULT_PRECIS, // nOutPrecision 
		CLIP_DEFAULT_PRECIS, // nClipPrecision 
		DEFAULT_QUALITY, // nQuality 
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
		_T("����")); // lpszFac 

	GetDlgItem(nID)->SetFont(f);
	return p_Button;
}

CStatic* CDialog_admin::NewMyStatic(int nID, CString text, CRect rect, int nStyle)
{
	LPCTSTR P = (LPCTSTR)text;
	CStatic *p_static = new CStatic();
	ASSERT_VALID(p_static);
	p_static->Create(P, WS_CHILD | WS_VISIBLE | SS_LEFT | nStyle, rect, this, nID);  //������̬�ı�
	CFont * f;
	f = new CFont;
	f->CreateFont(13, // nHeight 
		0, // nWidth 
		0, // nEscapement 
		0, // nOrientation 
		FW_BOLD, // nWeight 
		FALSE, // bItalic 
		FALSE, // bUnderline 
		0, // cStrikeOut 
		ANSI_CHARSET, // nCharSet 
		OUT_DEFAULT_PRECIS, // nOutPrecision 
		CLIP_DEFAULT_PRECIS, // nClipPrecision 
		DEFAULT_QUALITY, // nQuality 
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
		_T("����")); // lpszFac 

	GetDlgItem(nID)->SetFont(f);
	return p_static;
}

CEdit* CDialog_admin::NewMyEdit(int nID, CRect rect, int nStyle)
{
	CEdit *p_edit = new CEdit();
	ASSERT_VALID(p_edit);
	p_edit->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | nStyle, rect, this, nID);  //������̬�ı�
	CFont * f;
	f = new CFont;
	f->CreateFont(13, // nHeight 
		0, // nWidth 
		0, // nEscapement 
		0, // nOrientation 
		FW_BOLD, // nWeight 
		FALSE, // bItalic 
		FALSE, // bUnderline 
		0, // cStrikeOut 
		ANSI_CHARSET, // nCharSet 
		OUT_DEFAULT_PRECIS, // nOutPrecision 
		CLIP_DEFAULT_PRECIS, // nClipPrecision 
		DEFAULT_QUALITY, // nQuality 
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
		_T("����")); // lpszFac 

	GetDlgItem(nID)->SetFont(f);
	return p_edit;
}

CListCtrl* CDialog_admin::NewMyListCtrl(int nID, CRect rect, int nStyle)
{
	CListCtrl *p = new CListCtrl();
	ASSERT_VALID(p);
	p->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | nStyle, rect, this, nID);

	LONG lStyle;
	lStyle = GetWindowLong(p->m_hWnd, GWL_STYLE);//��ȡ��ǰ����style
	lStyle &= ~LVS_TYPEMASK;
	DWORD dwStyle = p->GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_CHECKBOXES;
	p->SetExtendedStyle(dwStyle); //������չ���
	return p;
}

void CDialog_admin::OnBnClickedButton5()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialog_admin::OnOK();
	CTUMMSDlg land;
	land.DoModal();
}


void CDialog_admin::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	switchPages();
	GetWindowRect(&rc);
	int p;
	int q;
	int t, b;
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString name("����:");
	CString sex("�Ա�:");
	CString tel("�绰:");
	CString num("��ʦ֤��:");
	p = rc.Width()*0.7;
	q = p + 150;
	t = rc.Height()*0.65;
	b = t + 50;
	b_personalInformation[0] = NewMyButton(IDS_BUTTON_CHANGEADMIN_INF, CRect(p, t, q, b), 0);

	p = rc.Width()*0.43;
	q = p + 100;
	t = rc.Height()*0.14;
	b = t + 20;
	s_personalInformation[6] = NewMyStatic(IDS_STATIC_ADMIN_INF_1, CONTROL.land.returnNumber(), CRect(p, t, q, b), 0);
	p = rc.Width()*0.29;
	q = p + 70;
	t = rc.Height()*0.14;
	b = t + 20;
	s_personalInformation[7] = NewMyStatic(IDS_STATIC_ADMIN_INF_2, num, CRect(p, t, q, b), 0);
	p = rc.Width()*0.42;
	q = p + 100;
	t = rc.Height()*0.24;
	b = t + 20;
	s_personalInformation[0] = NewMyStatic(IDS_STATIC_ADMIN_INF_3, CONTROL.land.returnUsername(), CRect(p, t, q, b), 0);
	p = rc.Width()*0.3;
	q = p + 50;
	t = rc.Height()*0.24;
	b = t + 20;
	s_personalInformation[1] = NewMyStatic(IDS_STATIC_ADMIN_INF_4, name, CRect(p, t, q, b), 0);
	p = rc.Width()*0.42;
	q = p + 100;
	t = rc.Height()*0.34;
	b = t + 20;
	s_personalInformation[2] = NewMyStatic(IDS_STATIC_ADMIN_INF_5, CONTROL.land.returnSex(), CRect(p, t, q, b), 0);
	p = rc.Width()*0.3;
	q = p + 50;
	t = rc.Height()*0.34;
	b = t + 20;
	s_personalInformation[3] = NewMyStatic(IDS_STATIC_ADMIN_INF_6, sex, CRect(p, t, q, b), 0);
	p = rc.Width()*0.42;
	q = p + 100;
	t = rc.Height()*0.44;
	b = t + 20;
	s_personalInformation[4] = NewMyStatic(IDS_STATIC_INFORMATION_7, CONTROL.land.returnTel(), CRect(p, t, q, b), 0);
	p = rc.Width()*0.3;
	q = p + 50;
	t = rc.Height()*0.44;
	b = t + 20;
	s_personalInformation[5] = NewMyStatic(IDS_STATIC_INFORMATION_8, tel, CRect(p, t, q, b), 0);
}


void CDialog_admin::OnClickChangeInf()
{
	if (b_personalInformation[0])
	for (int i = 0; i < 1; i++)
	{
		b_personalInformation[i]->DestroyWindow();
		delete b_personalInformation[i];
		b_personalInformation[i] = NULL;
	}

	s_personalInformation[0]->DestroyWindow();
	delete s_personalInformation[0];
	s_personalInformation[0] = NULL;
	s_personalInformation[2]->DestroyWindow();
	delete s_personalInformation[2];
	s_personalInformation[2] = NULL;
	s_personalInformation[4]->DestroyWindow();
	delete s_personalInformation[4];
	s_personalInformation[4] = NULL;

	GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(false);

	GetWindowRect(&rc);
	int p;
	int q;
	int t, b;

	p = rc.Width()*0.42;
	q = p + 100;
	t = rc.Height()*0.24;
	b = t + 20;
	s_changeinformation[0] = NewMyEdit(IDS_EDIT_ADMIN_NAME, CRect(p, t, q, b), 0);
	p = rc.Width()*0.42;
	q = p + 100;
	t = rc.Height()*0.34;
	b = t + 20;
	s_changeinformation[1] = NewMyEdit(IDS_EDIT_ADMIN_SEX, CRect(p, t, q, b), 0);
	p = rc.Width()*0.42;
	q = p + 100;
	t = rc.Height()*0.44;
	b = t + 20;
	s_changeinformation[2] = NewMyEdit(IDS_EDIT_ADMIN_TEL, CRect(p, t, q, b), 0);

	s_changeinformation[0]->SetWindowText(CONTROL.land.returnUsername());
	s_changeinformation[1]->SetWindowText(CONTROL.land.returnSex());
	s_changeinformation[2]->SetWindowText(CONTROL.land.returnTel());

	p = rc.Width()*0.7;
	q = p + 150;
	t = rc.Height()*0.65;
	b = t + 50;
	b_personalInformation[1] = NewMyButton(IDS_BUTTON_CHANGEADMIN_INF_1, CRect(p, t, q, b), 0);
	p = rc.Width()*0.4;
	q = p + 150;
	t = rc.Height()*0.65;
	b = t + 50;
	b_personalInformation[2] = NewMyButton(IDS_BUTTON_CHANGEADMIN_INF_2, CRect(p, t, q, b), 0);
}


void CDialog_admin::OnClickSaveChange()
{

	//	CDBOperation dbOper;
	//	bool bConn = dbOper.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "zbc", "666666");
	if (false == bConn)
	{

		CString alter("���ݿ����ӳ���");
		MessageBox(alter);

		OnClickCancelChange();

	}
	_RecordsetPtr pRst;
	char sql[255] = { 0 };
	char *temp_1;
	char *temp_2;


	s_changeinformation[0]->GetWindowText(Change_name);
	s_changeinformation[1]->GetWindowText(Change_sex);
	s_changeinformation[2]->GetWindowText(Change_tel);

	Change_name.Remove(' ');
	Change_sex.Remove(' ');
	Change_tel.Remove(' ');
	USES_CONVERSION;
	//	int n_1 = CONTROL.land.returnNumber().GetLength();
	//	int len = WideCharToMultiByte(CP_ACP, 0, CONTROL.land.returnNumber(), CONTROL.land.returnNumber().GetLength(), NULL, 0, NULL, NULL);
	//	temp_2 = new char[len + 1];
	//	WideCharToMultiByte(CP_ACP, 0, CONTROL.land.returnNumber(), n_1, temp_2, len, NULL, NULL);
	//	temp_2[len + 1] = '/0';
	temp_2 = T2A(CONTROL.land.returnNumber());

	if (Change_name != CONTROL.land.returnUsername())
	{
		//		temp_1 = new char[100];
		//		temp_1 = (LPSTR)(LPCTSTR)Change_name;
		//		temp_2 = (LPSTR)(LPCTSTR)CONTROL.land.returnNumber();
		//		int n = Change_name.GetLength();
		//		int len = WideCharToMultiByte(CP_ACP, 0, Change_name, Change_name.GetLength(), NULL, 0, NULL, NULL);
		//		temp_1 = new char[len + 1];
		//		WideCharToMultiByte(CP_ACP, 0, Change_name, n, temp_1, len, NULL, NULL);
		//		temp_1[len + 1] = '/0';

		temp_1 = T2A(Change_name);
		sprintf_s(sql, "update SYS_ADMIN set mname = '%s' where mno = '%s'", temp_1, temp_2);
		pRst = dbOper.ExecuteWithResSQL(sql);

		if (pRst == NULL)
		{
			CString alter("�޸�ʧ�ܣ���");
			MessageBox(alter);
		}
	}
	if (Change_sex != CONTROL.land.returnSex())
	{
		//		temp_1 = (LPSTR)(LPCTSTR)Change_sex;
		//		temp_2 = (LPSTR)(LPCTSTR)CONTROL.land.returnNumber();
		temp_1 = T2A(Change_sex);
		sprintf_s(sql, "update SYS_ADMIN set msex = '%s' where mno = '%s'", temp_1, temp_2);
		pRst = dbOper.ExecuteWithResSQL(sql);

		if (pRst == NULL)
		{
			CString alter("�޸�ʧ�ܣ���");
			MessageBox(alter);
		}
	}
	if (Change_tel != CONTROL.land.returnTel())
	{
		//		temp_1 = (LPSTR)(LPCTSTR)Change_tel;
		//		temp_2 = (LPSTR)(LPCTSTR)CONTROL.land.returnNumber();
		temp_1 = T2A(Change_tel);
		sprintf_s(sql, "update SYS_ADMIN set mtel = '%s' where mno = '%s'", temp_1, temp_2);
		pRst = dbOper.ExecuteWithResSQL(sql);

		if (pRst == NULL)
		{
			CString alter("�޸�ʧ�ܣ���");
			MessageBox(alter);
		}
	}

	if (pRst != NULL)
	{
		CString alter("�޸ĳɹ�����");
		MessageBox(alter);
		CONTROL.land.Input(Change_name, Change_sex, Change_tel, CONTROL.land.returnNumber());
	}


	s_changeinformation[0]->DestroyWindow();
	delete s_changeinformation[0];
	s_changeinformation[0] = NULL;
	s_changeinformation[1]->DestroyWindow();
	delete s_changeinformation[1];
	s_changeinformation[1] = NULL;
	s_changeinformation[2]->DestroyWindow();
	delete s_changeinformation[2];
	s_changeinformation[2] = NULL;

	b_personalInformation[1]->DestroyWindow();
	delete b_personalInformation[1];
	b_personalInformation[1] = NULL;
	b_personalInformation[2]->DestroyWindow();
	delete b_personalInformation[2];
	b_personalInformation[2] = NULL;

	GetDlgItem(IDC_BUTTON1)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(true);

	s_personalInformation[1]->DestroyWindow();
	delete s_personalInformation[1];
	s_personalInformation[1] = NULL;
	s_personalInformation[3]->DestroyWindow();
	delete s_personalInformation[3];
	s_personalInformation[3] = NULL;
	s_personalInformation[5]->DestroyWindow();
	delete s_personalInformation[5];
	s_personalInformation[5] = NULL;
	s_personalInformation[6]->DestroyWindow();
	delete s_personalInformation[6];
	s_personalInformation[6] = NULL;
	s_personalInformation[7]->DestroyWindow();
	delete s_personalInformation[7];
	s_personalInformation[7] = NULL;

	OnBnClickedButton1();
}


void CDialog_admin::OnClickCancelChange()
{
	s_changeinformation[0]->DestroyWindow();
	delete s_changeinformation[0];
	s_changeinformation[0] = NULL;
	s_changeinformation[1]->DestroyWindow();
	delete s_changeinformation[1];
	s_changeinformation[1] = NULL;
	s_changeinformation[2]->DestroyWindow();
	delete s_changeinformation[2];
	s_changeinformation[2] = NULL;

	b_personalInformation[1]->DestroyWindow();
	delete b_personalInformation[1];
	b_personalInformation[1] = NULL;
	b_personalInformation[2]->DestroyWindow();
	delete b_personalInformation[2];
	b_personalInformation[2] = NULL;

	GetDlgItem(IDC_BUTTON1)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(true);

	s_personalInformation[1]->DestroyWindow();
	delete s_personalInformation[1];
	s_personalInformation[1] = NULL;
	s_personalInformation[3]->DestroyWindow();
	delete s_personalInformation[3];
	s_personalInformation[3] = NULL;
	s_personalInformation[5]->DestroyWindow();
	delete s_personalInformation[5];
	s_personalInformation[5] = NULL;
	s_personalInformation[6]->DestroyWindow();
	delete s_personalInformation[6];
	s_personalInformation[6] = NULL;
	s_personalInformation[7]->DestroyWindow();
	delete s_personalInformation[7];
	s_personalInformation[7] = NULL;

	OnBnClickedButton1();
}


void CDialog_admin::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	switchPages();

	////////////////////
	GetWindowRect(&rc);
	int p;
	int q;
	int t, b;

	p = rc.Width()*0.21;
	q = p + rc.Width()*0.6;
	t = rc.Height()*0.07;
	b = t + rc.Height()*0.27;
	l_order_c[0] = NewMyListCtrl(IDS_LISTCRTL_ADMIN_ORDERCHECK, CRect(p, t, q, b), 0);
	l_order_c[0]->InsertColumn(0, _T("�������:"), LVCFMT_LEFT, 100);
	l_order_c[0]->InsertColumn(1, _T("��ʼʱ��:"), LVCFMT_LEFT, 100);
	l_order_c[0]->InsertColumn(2, _T("����ʱ��:"), LVCFMT_LEFT, 70);
	l_order_c[0]->InsertColumn(3, _T("�����û�:"), LVCFMT_LEFT, 100);
	l_order_c[0]->InsertColumn(4, _T("�����ܼ�:"), LVCFMT_LEFT, 110);

	p = rc.Width()*0.21;
	q = p + rc.Width()*0.6;
	t = rc.Height()*0.37;
	b = t + rc.Height()*0.2;
	l_order_c[1] = NewMyListCtrl(IDS_LISTCRTL_ADMIN_ORDER_M, CRect(p, t, q, b), 0);
	l_order_c[1]->InsertColumn(0, _T("�̲ı��:"), LVCFMT_LEFT, 100);
	l_order_c[1]->InsertColumn(1, _T("�̲�����:"), LVCFMT_LEFT, 200);
	l_order_c[1]->InsertColumn(2, _T("��������:"), LVCFMT_LEFT, 100);

	p = rc.Width()*0.21;
	q = p + rc.Width()*0.6;
	t = rc.Height()*0.6;
	b = t + rc.Height()*0.15;
	l_order_c[2] = NewMyListCtrl(IDS_LISTCTRL_ORDEROWNER_ADMIN, CRect(p, t, q, b), 0);
	l_order_c[2]->InsertColumn(0, _T("��ʦ���:"), LVCFMT_LEFT, 100);
	l_order_c[2]->InsertColumn(1, _T("��ʦ����:"), LVCFMT_LEFT, 70);
	l_order_c[2]->InsertColumn(2, _T("�Ա�:"), LVCFMT_LEFT, 40);
	l_order_c[2]->InsertColumn(3, _T("����ѧԺ:"), LVCFMT_LEFT, 90);
	l_order_c[2]->InsertColumn(4, _T("ְ��:"), LVCFMT_LEFT, 100);


	_RecordsetPtr pRst;
	char sql[255] = { 0 };

	USES_CONVERSION;

	strcpy_s(sql,"select * from SYS_ORDER where status = '2'");
	pRst = dbOper.ExecuteWithResSQL(sql);

	if (pRst == NULL)
	{
		CString alter("����ʧ�ܣ���");
		MessageBox(alter);
	}

//	if (pRst->adoEOF)
//	{
//		CString alter("û�ж���Ŷ����");
//		MessageBox(alter);
//	}
	else if (!pRst->adoEOF)
	{

		pRst->MoveFirst(); //��¼��ָ���ƶ�����ѯ�������ǰ��
		_variant_t vNum, vBegindate, vEnddate, vSno, vSum;
		int nRow;
		while (!pRst->adoEOF)
		{

			vNum = pRst->GetCollect(_variant_t("num"));
			vBegindate = pRst->GetCollect(_variant_t("begindate"));
			vEnddate = pRst->GetCollect(_variant_t("enddate"));
			vSno = pRst->GetCollect(_variant_t("sno"));
			vSum = pRst->GetCollect(_variant_t("sum"));


			string num = (LPCSTR)_bstr_t(vNum);
			string begindate = (LPCSTR)_bstr_t(vBegindate);
			string enddate = (LPCSTR)_bstr_t(vEnddate);
			string sno = (LPCSTR)_bstr_t(vSno);
			string sum = (LPCSTR)_bstr_t(vSum);

			CString num_1;
			CString begindate_1;
			CString enddate_1;
			CString sno_1;
			CString sum_1;

			num_1 = num.c_str();
			begindate_1 = begindate.c_str();
			enddate_1 = enddate.c_str();
			sno_1 = sno.c_str();
			sum_1 = sum.c_str();

			num_1.Remove(' ');
			begindate_1.Remove(' ');
			enddate_1.Remove(' ');
			sno_1.Remove(' ');
			sum_1.Remove(' ');

			if (sno_1 == "1")
			{
				sno_1 = "δ��Ч";
			}
			else if (sno_1 == "2")
			{
				sno_1 = "�ȴ�ѧԺ����";
			}
			else if (sno_1 == "3")
			{
				sno_1 = "�ȴ��̲Ŀ�����";
			}
			else if (sno_1 == "4")
			{
				sno_1 = "�̲��ѿ�ʼ����";
			}
			else if (sno_1 == "5")
			{
				sno_1 = "ѧԺ����δͨ��";
			}
			else if (sno_1 == "6")
			{
				sno_1 = "�̲Ŀ�����δͨ��";
			}
			else if (sno_1 == "7")
			{
				sno_1 = "���������";
			}
			else if (sno_1 == "8")
			{
				sno_1 = "�����������";
			}

			nRow = l_order_c[0]->InsertItem(0, num_1);//������
			l_order_c[0]->SetItemText(nRow, 1, begindate_1);//��������
			l_order_c[0]->SetItemText(nRow, 2, enddate_1);//��������
			l_order_c[0]->SetItemText(nRow, 3, sno_1);
			l_order_c[0]->SetItemText(nRow, 4, sum_1);

			////////////////////////////////////////////



			/////////////////////////////////////////////////
			pRst->MoveNext();
		}
	}

	p = rc.Width()*0.83;
	q = p + rc.Width()*0.1;
	t = rc.Height()*0.57;
	b = t + 40;
	b_orderCheck[0] = NewMyButton(IDS_BUTTON_ORDERCHECK_ADMIN, CRect(p, t, q, b), 0);
	p = rc.Width()*0.83;
	q = p + rc.Width()*0.1;
	t = rc.Height()*0.67;
	b = t + 40;
	b_orderCheck[1] = NewMyButton(IDS_BUTTON_ORDERCHECK_ADMIN_NO, CRect(p, t, q, b), 0);
}



void CDialog_admin::OnClickInfOfOrder(NMHDR* pNMHDR, LRESULT* pResult)
{
	CString str;
	int nId;
	//���ȵõ������λ��
	POSITION pos = l_order_c[0]->GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		GetDlgItem(IDS_BUTTON_ORDERCHECK_ADMIN)->EnableWindow(true);
		GetDlgItem(IDS_BUTTON_ORDERCHECK_ADMIN_NO)->EnableWindow(true);
		//�õ��кţ�ͨ��POSITIONת��
		nId = (int)l_order_c[0]->GetNextSelectedItem(pos);
		//�õ����е����ݣ�0��ʾ��һ�У�ͬ��1,2,3...��ʾ�ڶ���������...�У�
		str = l_order_c[0]->GetItemText(nId, 0);
		memory_1 = l_order_c[0]->GetItemText(nId, 0);
		memory = l_order_c[0]->GetItemText(nId, 3);
		CoutTheDetail_Order(str);
	}
	else
	{
		GetDlgItem(IDS_BUTTON_ORDERCHECK_ADMIN)->EnableWindow(false);
		GetDlgItem(IDS_BUTTON_ORDERCHECK_ADMIN_NO)->EnableWindow(false);

	}
}

void CDialog_admin::CoutTheDetail_Order(CString num)      //��ʾ�̲���ϸ��Ϣ
{
	l_order_c[1]->DeleteAllItems();
	l_order_c[2]->DeleteAllItems();

	USES_CONVERSION;
	_RecordsetPtr pRst_1;
	char sql_1[255] = { 0 };
	char* temp_1;
	temp_1 = T2A(num);

	sprintf_s(sql_1, "select * from SYS_ORDER_M where num = '%s'", temp_1);
	pRst_1 = dbOper.ExecuteWithResSQL(sql_1);

	if (pRst_1 == NULL)
	{
		CString alter("����ʧ�ܣ���");
		MessageBox(alter);
	}

	if (pRst_1->adoEOF)
	{
		CString alter("û�ж���Ŷ����");
		MessageBox(alter);
	}
	else
	{

		pRst_1->MoveFirst(); //��¼��ָ���ƶ�����ѯ�������ǰ��
		_variant_t vBno, vBname, vQua;
		int nRow_1;
		while (!pRst_1->adoEOF)
		{

			vBno = pRst_1->GetCollect(_variant_t("bno"));
			vBname = pRst_1->GetCollect(_variant_t("bname"));
			vQua = pRst_1->GetCollect(_variant_t("qua"));

			string bno = (LPCSTR)_bstr_t(vBno);
			string bname = (LPCSTR)_bstr_t(vBname);
			string qua = (LPCSTR)_bstr_t(vQua);

			CString bno_1;
			CString bname_1;
			CString qua_1;

			bno_1 = bno.c_str();
			bname_1 = bname.c_str();
			qua_1 = qua.c_str();

			bno_1.Remove(' ');
			bname_1.Remove(' ');
			qua_1.Remove(' ');

			nRow_1 = l_order_c[1]->InsertItem(0, bno_1);//������
			l_order_c[1]->SetItemText(nRow_1, 1, bname_1);//��������
			l_order_c[1]->SetItemText(nRow_1, 2, qua_1);//��������


			pRst_1->MoveNext();
		}
	}

	_RecordsetPtr pRst_2;
	char sql_2[255] = { 0 };
	char* temp_2;
	temp_2 = T2A(memory);
	sprintf_s(sql_2, "select * from SYS_USER where sno = '%s'", temp_2);
	pRst_2 = dbOper.ExecuteWithResSQL(sql_2);


	if (pRst_2->adoEOF)
	{
		CString alter("û���ҵ��������");
		MessageBox(alter);
	}
	else
	{
		pRst_2->MoveFirst(); //��¼��ָ���ƶ�����ѯ�������ǰ��
		_variant_t vSno, vSname, vSex, vAcademy, vTeaching;
		int nRow_1;
		while (!pRst_2->adoEOF)
		{

			vSno = pRst_2->GetCollect(_variant_t("sno"));
			vSname = pRst_2->GetCollect(_variant_t("sname"));
			vSex = pRst_2->GetCollect(_variant_t("sex"));
			vAcademy = pRst_2->GetCollect(_variant_t("academy"));
			vTeaching = pRst_2->GetCollect(_variant_t("teaching"));

			string sno = (LPCSTR)_bstr_t(vSno);
			string sname = (LPCSTR)_bstr_t(vSname);
			string sex = (LPCSTR)_bstr_t(vSex);
			string academy = (LPCSTR)_bstr_t(vAcademy);
			string teaching = (LPCSTR)_bstr_t(vTeaching);

			CString sno_1;
			CString sname_1;
			CString sex_1;
			CString academy_1;
			CString teaching_1;

			sno_1 = sno.c_str();
			sname_1 = sname.c_str();
			sex_1 = sex.c_str();
			academy_1 = academy.c_str();
			teaching_1 = teaching.c_str();

			sno_1.Remove(' ');
			sname_1.Remove(' ');
			sex_1.Remove(' ');
			academy_1.Remove(' ');
			teaching_1.Remove(' ');

			nRow_1 = l_order_c[2]->InsertItem(0, sno_1);//������
			l_order_c[2]->SetItemText(nRow_1, 1, sname_1);//��������
			l_order_c[2]->SetItemText(nRow_1, 2, sex_1);//��������
			l_order_c[2]->SetItemText(nRow_1, 3, academy_1);//��������
			l_order_c[2]->SetItemText(nRow_1, 4, teaching_1);//��������


			pRst_2->MoveNext();
		}
	}
}

void CDialog_admin::OnClickAgreeOrder()
{
	CString num;
	USES_CONVERSION;
	char *temp;
	for (int i = 0; i < l_order_c[0]->GetItemCount(); i++)
	{
		if (l_order_c[0]->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED || l_order_c[0]->GetCheck(i))
		{
			num = l_order_c[0]->GetItemText(i, 3);
			_RecordsetPtr pRst;
			char sql[255] = { 0 };
			CString number;
			number = l_order_c[0]->GetItemText(i, 0);
			temp = T2A(number);
			sprintf_s(sql, "update SYS_ORDER set status = '3' where num = '%s'", temp);
			pRst = dbOper.ExecuteWithResSQL(sql);
			if (pRst == NULL)
			{
				MessageBox(CString("�޸�ʧ��"));
			}
			else
			{
				MessageBox(CString("�����ɹ���"));
			}

		}

	}
	OnBnClickedButton2();
}

void CDialog_admin::OnClickdisagreeOrder()
{
	CString num;
	CString rec;
	USES_CONVERSION;
	char *temp_1;
	char *sender;
	char *sender_name;
	char *receiver;
	char *content;
	char *mno;
	for (int i = 0; i < l_order_c[0]->GetItemCount(); i++)
	{
		if (l_order_c[0]->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED || l_order_c[0]->GetCheck(i))
		{
			_RecordsetPtr pRst;
			char sql[255] = { 0 };
			CString number;
			rec = l_order_c[0]->GetItemText(i, 3);
			CString contain;
			Dialog_reason temp;
			temp.DoModal();
			if (!temp.tag)
			{

				CString count_1;
				strcpy_s(sql, "select count(mno) count from SYS_MAIL");
				pRst = dbOper.ExecuteWithResSQL(sql);
				if (NULL == pRst)
				{
					CString alter("��ѯ���ݳ��ִ���");
					CDialog_admin a;
					a.MessageBox(alter);
				}
				else if (pRst->adoEOF)
				{
					pRst->Close();
					CDialog_admin a;
					CString alter("δ��ѯ�������");
					a.MessageBox(alter);
				}
				else
				{
					pRst->MoveFirst(); //��¼��ָ���ƶ�����ѯ�������ǰ��
					_variant_t  vCount;
					while (!pRst->adoEOF)
					{

						vCount = pRst->GetCollect(_variant_t("count"));

						string count = (LPCSTR)_bstr_t(vCount);

						count_1 = count.c_str();

						count_1.Remove(' ');

						int i = _ttoi(count_1);
						i = i + 1;
						count_1.Format(_T("%d"), i);
						if (i < 10)
						{
							CString a("000");
							num = a + count_1;
						}
						else if (i < 100)
						{
							CString a("00");
							num = a + count_1;
						}
						else if (i < 1000)
						{
							CString a("0");
							num = a + count_1;
						}


						_RecordsetPtr pRst_1;
						char sql_1[255] = { 0 };
						char *temp;
						while (true)
						{
							temp = T2A(num);
							sprintf_s(sql_1, "select * from SYS_MAIL where mno = '%s'", temp);
							pRst_1 = dbOper.ExecuteWithResSQL(sql_1);
							if (pRst_1 == NULL)
							{
								MessageBox(CString("��ѯ����"));
								break;
							}
							else if (pRst_1->adoEOF)
							{
								break;
							}
							else
							{
								i = i + 1;
								count_1.Format(_T("%d"), i);
								if (i < 10)
								{
									CString a("000");
									num = a + count_1;
								}
								else if (i < 100)
								{
									CString a("00");
									num = a + count_1;
								}
								else if (i < 1000)
								{
									CString a("0");
									num = a + count_1;
								}
								
							}
						}


						pRst->MoveNext();
					}
				}

				contain = temp.GetReason();
				CString system("��������Ϊ");
				CString num_1;
				num_1 = l_order_c[0]->GetItemText(i, 0);
				CString system_1("�Ķ���δͨ��ѧԺ��������ԭ���ǣ�");
				system = system + num_1 + system_1 + contain;
				sender = T2A(CONTROL.land.returnNumber());
				sender_name = T2A(CONTROL.land.returnUsername());
				receiver = T2A(rec);
				content = T2A(system);
				mno = T2A(num);
				sprintf_s(sql, "insert into SYS_MAIL(mno,sender,receiver,content,sender_name,ifread) values('%s','%s','%s','%s','%s','1')", mno ,sender,receiver, content, sender_name );
				pRst = dbOper.ExecuteWithResSQL(sql);
				
				if (pRst != NULL)
				{
					number = l_order_c[0]->GetItemText(i, 0);
					temp_1 = T2A(number);
					sprintf_s(sql, "update SYS_ORDER set status = '5' where num = '%s'", temp_1);
					pRst = dbOper.ExecuteWithResSQL(sql);
				}
				else
				{
					MessageBox(CString("����ʧ��"));
				}
			}

		}

	}
	OnBnClickedButton2();
}

void CDialog_admin::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	switchPages();
}


void CDialog_admin::OnBnClickedButton4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	switchPages();

	/////////////////

	GetWindowRect(&rc);
	int p;
	int q;
	int t, b;
	USES_CONVERSION;
	p = rc.Width()*0.23;
	q = p + rc.Width()*0.3;
	t = rc.Height()*0.07;
	b = t + rc.Height()*0.6;
	l_maillist[0] = NewMyListCtrl(IDS_LISTCTRL_USER_MAINLIST, CRect(p, t, q, b), 0);
	l_maillist[0]->InsertColumn(0, _T("��Ϣ���"), LVCFMT_LEFT, (rc.Width()*0.3)*0.33);
	l_maillist[0]->InsertColumn(1, _T("������"), LVCFMT_LEFT, (rc.Width()*0.3)*0.33);
	l_maillist[0]->InsertColumn(2, _T("�Ƿ��Ѷ�"), LVCFMT_LEFT, (rc.Width()*0.3)*0.33);

	_RecordsetPtr pRst;
	char sql[255] = { 0 };
	char *temp;
	temp = T2A(CONTROL.land.returnNumber());
	sprintf_s(sql, "select * from SYS_MAIL where receiver = '%s'",temp);
	pRst = dbOper.ExecuteWithResSQL(sql);
	if (NULL == pRst)
	{
		CString alter("��ѯ���ݳ��ִ���");
		MessageBox(alter);
	}
//	else if (pRst->adoEOF)
//	{
//		pRst->Close();
//
//		CString alter("��ѯ���ݳ��ִ���");
//		MessageBox(alter);
//	}
	else if (!pRst->adoEOF)
	{
		pRst->MoveFirst(); //��¼��ָ���ƶ�����ѯ�������ǰ��
		_variant_t vName, vIfread, vMno;
		while (!pRst->adoEOF)
		{
			vMno = pRst->GetCollect(_variant_t("mno"));

			vName = pRst->GetCollect(_variant_t("sender_name"));

			vIfread = pRst->GetCollect(_variant_t("ifread"));

			string mno = (LPCSTR)_bstr_t(vMno);
			string name = (LPCSTR)_bstr_t(vName);
			string ifread = (LPCSTR)_bstr_t(vIfread);

			CString mno_1;
			CString name_1;
			CString ifread_1;
			mno_1 = mno.c_str();
			name_1 = name.c_str();
			ifread_1 = ifread.c_str();
			mno_1.Remove(' ');
			name_1.Remove(' ');
			ifread_1.Remove(' ');

			if (ifread_1 == "1")
				ifread_1 = "δ�鿴";
			else if (ifread_1 == "2")
				ifread_1 = "�Ѳ鿴";

			int nRow = l_maillist[0]->InsertItem(0, mno_1);//������
			l_maillist[0]->SetItemText(nRow, 1, name_1);//��������
			l_maillist[0]->SetItemText(nRow, 2, ifread_1);

			pRst->MoveNext();

		}
	}

	p = rc.Width()*0.23;
	q = p + rc.Width()*0.09;
	t = rc.Height()*0.69;
	b = t + rc.Height()*0.08;
	b_mail[0] = NewMyButton(IDS_BUTTON_SENDMAIL_USER, CRect(p, t, q, b), 0);
	p = rc.Width()*0.34;
	q = p + rc.Width()*0.09;
	t = rc.Height()*0.69;
	b = t + rc.Height()*0.08;
	b_mail[1] = NewMyButton(IDS_BUTTON_DELETEMAIL_USER, CRect(p, t, q, b), 0);
}

void CDialog_admin::OnClickInfOfMail(NMHDR* pNMHDR, LRESULT* pResult)
{
	CString str;
	int nId;
	//���ȵõ������λ��
	POSITION pos = l_maillist[0]->GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		//		GetDlgItem(IDS_BUTTON_CHANGEMATERIAL_INF)->EnableWindow(true);
		//		GetDlgItem(IDS_BUTTON_DELETEMATERIAL)->EnableWindow(true);
		//�õ��кţ�ͨ��POSITIONת��
		nId = (int)l_maillist[0]->GetNextSelectedItem(pos);
		//�õ����е����ݣ�0��ʾ��һ�У�ͬ��1,2,3...��ʾ�ڶ���������...�У�
		str = l_maillist[0]->GetItemText(nId, 0);
		_RecordsetPtr pRst;
		char sql[255] = { 0 };
		USES_CONVERSION;
		char *temp;
		temp = T2A(str);
		sprintf_s(sql, "update SYS_MAIL set ifread = '2' where mno = '%s'", temp);
		pRst = dbOper.ExecuteWithResSQL(sql);
		if (NULL == pRst)
		{
			CString alter("���ݲ������ִ���");
			MessageBox(alter);
		}
		//		memory_1 = l_maillist[0]->GetItemText(nId, 0);
		CString a("�Ѳ鿴");
		l_maillist[0]->SetItemText(nId, 2, a);
		memory = l_maillist[0]->GetItemText(nId, 2);
		CoutTheDetail_mail(str);
	}
	else
	{
		//		GetDlgItem(IDS_BUTTON_CHANGEMATERIAL_INF)->EnableWindow(false);
		//		GetDlgItem(IDS_BUTTON_DELETEMATERIAL)->EnableWindow(false);

	}
}

void CDialog_admin::CoutTheDetail_mail(CString num)
{
	for (int i = 0; i < 6; i++)
	{
		if (s_mail[i])
		{
			s_mail[i]->DestroyWindow();
			delete s_mail[i];
			s_mail[i] = NULL;
		}
	}

	CString TITLE("��Ϣ����:");
	CString SENDER("�����˱��:");
	CString SENDER_NAME("������:");

	_RecordsetPtr pRst;
	char sql[255] = { 0 };
	USES_CONVERSION;
	char *temp;
	temp = T2A(num);
	sprintf_s(sql, "select * from SYS_MAIL WHERE mno = '%s'", temp);
	pRst = dbOper.ExecuteWithResSQL(sql);
	if (NULL == pRst)
	{
		CString alter("��ѯ���ݳ��ִ���");
		MessageBox(alter);
	}
	else if (pRst->adoEOF)
	{
		pRst->Close();

		//CString alter("δ��ѯ�������");
		//MessageBox(alter);
	}
	else
	{
		pRst->MoveFirst(); //��¼��ָ���ƶ�����ѯ�������ǰ��
		_variant_t vSender, vSender_name, vContent;
		GetWindowRect(&rc);
		int p;
		int q;
		int t, b;
		while (!pRst->adoEOF)
		{

			vSender = pRst->GetCollect(_variant_t("sender"));

			vSender_name = pRst->GetCollect(_variant_t("sender_name"));

			vContent = pRst->GetCollect(_variant_t("content"));


			string sender = (LPCSTR)_bstr_t(vSender);
			string sender_name = (LPCSTR)_bstr_t(vSender_name);
			string content = (LPCSTR)_bstr_t(vContent);

			CString sender_1;
			CString sender_name_1;
			CString content_1;

			sender_1 = sender.c_str();
			sender_name_1 = sender_name.c_str();
			content_1 = content.c_str();

			sender_1.Remove(' ');
			sender_name_1.Remove(' ');
			content_1.Remove(' ');

			p = rc.Width()*0.66;
			q = p + 150;
			t = rc.Height()*0.07;
			b = t + 20;
			s_mail[0] = NewMyStatic(IDS_STATIC_MANAGE_INF_1, sender_1, CRect(p, t, q, b), 0);
			p = rc.Width()*0.55;
			q = p + 90;
			t = rc.Height()*0.07;
			b = t + 20;
			s_mail[1] = NewMyStatic(IDS_STATIC_MANAGE_INF_2, SENDER, CRect(p, t, q, b), 0);

			p = rc.Width()*0.64;
			q = p + 250;
			t = rc.Height()*0.12;
			b = t + 20;
			s_mail[2] = NewMyStatic(IDS_STATIC_MANAGE_INF_3, sender_name_1, CRect(p, t, q, b), 0);
			p = rc.Width()*0.55;
			q = p + 80;
			t = rc.Height()*0.12;
			b = t + 20;
			s_mail[3] = NewMyStatic(IDS_STATIC_MANAGE_INF_4, SENDER_NAME, CRect(p, t, q, b), 0);

			p = rc.Width()*0.64;
			q = p + 200;
			t = rc.Height()*0.17;
			b = t + 100;
			s_mail[4] = NewMyStatic(IDS_STATIC_MANAGE_INF_5, content_1, CRect(p, t, q, b), 0);
			p = rc.Width()*0.55;
			q = p + 80;
			t = rc.Height()*0.17;
			b = t + 20;
			s_mail[5] = NewMyStatic(IDS_STATIC_MANAGE_INF_6, TITLE, CRect(p, t, q, b), 0);


			pRst->MoveNext();

		}
	}
}

void CDialog_admin::OnClickDelete_mail()
{
	CString num;
	USES_CONVERSION;
	char *temp;
	for (int i = 0; i < l_maillist[0]->GetItemCount(); i++)
	{
		if (l_maillist[0]->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED || l_maillist[0]->GetCheck(i))
		{
			num = l_maillist[0]->GetItemText(i, 2);
			if (memory == "�Ѳ鿴")
			{
				_RecordsetPtr pRst;
				char sql[255] = { 0 };
				CString number;
				number = l_maillist[0]->GetItemText(i, 0);
				temp = T2A(number);
				sprintf_s(sql, "delete from SYS_MAIL where mno = '%s'", temp);
				pRst = dbOper.ExecuteWithResSQL(sql);
				if (pRst == NULL)
				{
					MessageBox(CString("ɾ��ʧ��"));
				}
				else
				{
					MessageBox(CString("ɾ���ɹ�"));
				}

			}
			else
			{
				MessageBox(CString("����Ϣ��û�п���Ŷ��"));
			}
		}

	}
	OnBnClickedButton4();
}

void CDialog_admin::OnClickSendMail()
{
	CDialog_sendMail send;
	send.DoModal();
}

void CDialog_admin::switchPages()
{
	
	for (int i = 0; i < 1; i++)
	{
		if (b_personalInformation[i])
		{
			b_personalInformation[i]->DestroyWindow();
			delete b_personalInformation[i];
			b_personalInformation[i] = NULL;
		}
	}

	
	for (int i = 0; i < 8; i++)
	{
		if (s_personalInformation[i])
		{
			s_personalInformation[i]->DestroyWindow();
			delete s_personalInformation[i];
			s_personalInformation[i] = NULL;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (l_order_c[i])
		{
			l_order_c[i]->DestroyWindow();
			delete l_order_c[i];
			l_order_c[i] = NULL;
		}
	}

	for (int i = 0; i < 2; i++)
	{
		if (b_orderCheck[i])
		{
			b_orderCheck[i]->DestroyWindow();
			delete b_orderCheck[i];
			b_orderCheck[i] = NULL;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (l_maillist[i])
		{
			l_maillist[i]->DestroyWindow();
			delete l_maillist[i];
			l_maillist[i] = NULL;
		}
	}

	for (int i = 0; i < 6; i++)
	{
		if (s_mail[i])
		{
			s_mail[i]->DestroyWindow();
			delete s_mail[i];
			s_mail[i] = NULL;
		}
	}

	for (int i = 0; i < 6; i++)
	{
		if (b_mail[i])
		{
			b_mail[i]->DestroyWindow();
			delete b_mail[i];
			b_mail[i] = NULL;
		}
	}

}


BOOL CDialog_admin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	OnBnClickedButton1();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CDialog_admin::OnBnClickedButton6()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialog_changePassword a;
	a.DoModal();
}
