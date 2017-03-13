// Dialog_manage.cpp : 实现文件
//

#include "stdafx.h"
#include "TUMMS.h"
#include "Dialog_manage.h"
#include "afxdialogex.h"
#include "TUMMSDlg.h"
#include<string>
#include "Dialog_sendMail.h"
#include "Dialog_reason.h"
#include "Dialog_changePassword.h"
#include "Dialog_notice.h"
#include "Function.h"
using namespace std;


extern control CONTROL;
extern CDBOperation dbOper;
extern bool bConn;
extern CRect rc;
extern CString n_title;
extern CString n_content;

// CDialog_manage 对话框

IMPLEMENT_DYNAMIC(CDialog_manage, CDialogEx)

CDialog_manage::CDialog_manage(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialog_manage::IDD, pParent)
{
	for (int i = 0; i < 6; i++)
	{
		s_changePerson_inf[i] = NULL;
	}

//	m_person_static.ShowWindow(SW_HIDE);
}

CDialog_manage::~CDialog_manage()
{
}

void CDialog_manage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
//	DDX_Control(pDX, IDC_PERSONAL_INFORMATION_NORMAL, m_person_static);
}


BEGIN_MESSAGE_MAP(CDialog_manage, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON7, &CDialog_manage::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialog_manage::OnBnClickedButton1)
	ON_BN_CLICKED(IDS_BUTTON_CHANGEMANAGEER_INFORMATION, &CDialog_manage::OnBnClickedPersonalInformationNormal)
	ON_BN_CLICKED(IDC_BUTTON2, &CDialog_manage::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDialog_manage::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CDialog_manage::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON6, &CDialog_manage::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON8, &CDialog_manage::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON5, &CDialog_manage::OnBnClickedButton5)
	ON_BN_CLICKED(IDS_BUTTON_CHANGEINF_MANAGE_1, &CDialog_manage::OnClickSaveChange)
	ON_BN_CLICKED(IDS_BUTTON_CHANGEINF_MANAGE_2, &CDialog_manage::OnClickCancelChange)
	ON_NOTIFY(NM_CLICK, IDS_USER_MATERIALLIST, OnClickInfOfPerson)
	ON_BN_CLICKED(IDS_BUTTON_CHANGEPERSON, &CDialog_manage::OnClickChangePerson)
	ON_BN_CLICKED(IDS_BUTTON_CANCELPERSON, &CDialog_manage::OnClickCancelChange_1)
	ON_BN_CLICKED(IDS_BUTTON_SAVEPERSON, &CDialog_manage::OnClickSavePersonChange)
	ON_BN_CLICKED(IDS_BUTTON_ADDPERSON, &CDialog_manage::OnClickAddPerson)
	ON_BN_CLICKED(IDS_BUTTON_SAVEADDPERSON, &CDialog_manage::OnClickSaveAddPerson)
	ON_BN_CLICKED(IDS_BUTTON_DELETEPERSON, &CDialog_manage::OnClickDeletePerson)
	ON_NOTIFY(NM_CLICK, IDS_MANAGE_MATERIALLIST, OnClickInfOfMaterial)
	ON_BN_CLICKED(IDS_BUTTON_CHANGEMATERIAL_INF, &CDialog_manage::OnClickChangeMaterial)
	ON_BN_CLICKED(IDS_BUTTON_SAVEMATERIALCHANGE, &CDialog_manage::OnClickSaveMaterialChange)
	ON_BN_CLICKED(IDS_BUTTON_CANCELCHANGEMATERIAL, &CDialog_manage::OnClickCancelChange_2)
	ON_BN_CLICKED(IDS_BUTTON_ADDMATERIAL, &CDialog_manage::OnClickAddMaterial)
	ON_BN_CLICKED(IDS_BUTTON_SAVEADDMATERIAL, &CDialog_manage::OnClickSaveAddMaterial)
	ON_BN_CLICKED(IDS_BUTTON_DELETEMATERIAL, &CDialog_manage::OnClickDeleteMaterial)
	ON_NOTIFY(NM_CLICK, IDS_MANAGE_PRESSLIST, OnClickInfOfPress)
	ON_BN_CLICKED(IDS_BUTTON_CHANGEPRESS_INF, &CDialog_manage::OnClickChangePress)
	ON_BN_CLICKED(IDS_BUTTON_SAVEPRESSCHANGE, &CDialog_manage::OnClickSavePressChange)
	ON_BN_CLICKED(IDS_BUTTON_CANCELCHANGE, &CDialog_manage::OnClickCancelChange_3)
	ON_BN_CLICKED(IDS_BUTTON_ADDPRESS, &CDialog_manage::OnClickAddPress)
	ON_BN_CLICKED(IDS_BUTTON_SAVEADDPRESS, &CDialog_manage::OnClickSaveAddPress)
	ON_BN_CLICKED(IDS_BUTTON_DELETEPRESS, &CDialog_manage::OnClickDeletePress)
	ON_NOTIFY(NM_CLICK, IDS_LISTCTRL_USER_MAINLIST, OnClickInfOfMail)
	ON_BN_CLICKED(IDS_BUTTON_DELETEMAIL_USER, &CDialog_manage::OnClickDelete_mail)
	ON_BN_CLICKED(IDS_BUTTON_SENDMAIL_USER, &CDialog_manage::OnClickSendMail)
	ON_NOTIFY(NM_CLICK, IDS_LISTCRTL_ADMIN_ORDERCHECK, OnClickInfOfOrder)
	ON_BN_CLICKED(IDS_BUTTON_ORDERCHECK_ADMIN, &CDialog_manage::OnClickAgreeOrder)
	ON_BN_CLICKED(IDS_BUTTON_ORDERCHECK_ADMIN_NO, &CDialog_manage::OnClickdisagreeOrder)
	ON_NOTIFY(NM_CLICK, IDS_LISTCTRL_ORDEROWNER_ADMIN, OnClickInfOfOrder_accomplish)
	ON_BN_CLICKED(IDS_BUTTON_ACCOMPLISH_DIS, &CDialog_manage::OnClickAccomplishDis)
	ON_BN_CLICKED(IDC_BUTTON9, &CDialog_manage::OnBnClickedButton9)
	ON_NOTIFY(NM_CLICK, IDS_LISTCTRL_NOTICELIST, OnClickInfOfNotice)
	ON_BN_CLICKED(IDS_BUTTON_DELETENOTICE, &CDialog_manage::OnClickDelete_notice)
	ON_BN_CLICKED(IDS_BUTTON_ADDNOTICE, &CDialog_manage::OnClickAddNotice)
	ON_BN_CLICKED(IDS_BUTTON_PUBLISHNOTICE, &CDialog_manage::OnClickPublishNotice)
	ON_BN_CLICKED(IDS_BUTTON_TAKENOTICE, &CDialog_manage::OnClickBackNotice)
END_MESSAGE_MAP()


// CDialog_manage 消息处理程序

CButton* CDialog_manage::NewMyButton(int nID, CRect rect, int nStyle)
{
	CString m_Caption;
	m_Caption.LoadString(nID); //取按钮标题
	CButton *p_Button = new CButton();
	ASSERT_VALID(p_Button);
	p_Button->Create(m_Caption, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | nStyle, rect, this, nID); //创建按钮
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
		_T("黑体")); // lpszFac 

	GetDlgItem(nID)->SetFont(f);
	return p_Button;
}

CStatic* CDialog_manage::NewMyStatic(int nID, CString text, CRect rect, int nStyle)
{
	LPCTSTR P = (LPCTSTR)text;
	CStatic *p_static = new CStatic();
	ASSERT_VALID(p_static);
	p_static->Create(P, WS_CHILD | WS_VISIBLE | SS_LEFT | nStyle, rect, this, nID);  //创建静态文本
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
		_T("黑体")); // lpszFac 

	GetDlgItem(nID)->SetFont(f);
	return p_static;
}

CEdit* CDialog_manage::NewMyEdit(int nID, CRect rect, int nStyle)
{
	CEdit *p_edit = new CEdit();
	ASSERT_VALID(p_edit);
	p_edit->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL| nStyle, rect, this, nID);  //创建静态文本
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
		_T("黑体")); // lpszFac 

	GetDlgItem(nID)->SetFont(f);
	return p_edit;
}

CListCtrl* CDialog_manage::NewMyListCtrl(int nID, CRect rect, int nStyle)
{
	CListCtrl *p = new CListCtrl();
	ASSERT_VALID(p);
	p->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | nStyle, rect, this, nID);

	LONG lStyle;
	lStyle = GetWindowLong(p->m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK;
	DWORD dwStyle = p->GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_CHECKBOXES;
	p->SetExtendedStyle(dwStyle); //设置扩展风格
	return p;
}

CComboBox* CDialog_manage::NewMyComboBox(int nID, CRect rect, int nStyle)
{
	CComboBox *p = new CComboBox();
	ASSERT_VALID(p);
	p->Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL| WS_TABSTOP | CBS_DROPDOWNLIST | nStyle, rect, this, nID);

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
		_T("黑体")); // lpszFac 

	GetDlgItem(nID)->SetFont(f);
	return p;
}

void CDialog_manage::OnBnClickedButton7()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialog_manage::OnOK();
	CTUMMSDlg land;
	land.DoModal();
}


void CDialog_manage::OnBnClickedButton1()
{

	// TODO:  在此添加控件通知处理程序代码

	switchPages();

	//////////////

	GetWindowRect(&rc);
	int p;
	int q;
	int t, b;
	// TODO:  在此添加控件通知处理程序代码
	CString name("姓名:");
	CString sex("性别:");
	CString tel("电话:");
	CString num("管理编号:");
	p = rc.Width()*0.7;
	q = p + 150;
	t = rc.Height()*0.65;
	b = t + 50;
	b_personalInformation[0] = NewMyButton(IDS_BUTTON_CHANGEMANAGEER_INFORMATION, CRect(p, t, q, b), 0);

	p = rc.Width()*0.43;
	q = p + 100;
	t = rc.Height()*0.14;
	b = t + 20;
	s_personalInformation[6] = NewMyStatic(IDS_STATIC_MANGE_INFORMATINO_1, CONTROL.land.returnNumber(), CRect(p, t, q, b), 0);
	p = rc.Width()*0.29;
	q = p + 70;
	t = rc.Height()*0.14;
	b = t + 20;
	s_personalInformation[7] = NewMyStatic(IDS_STATIC_MANGE_INFORMATINO_2, num, CRect(p, t, q, b), 0);
	p = rc.Width()*0.42;
	q = p + 100;
	t = rc.Height()*0.24;
	b = t + 20;
	s_personalInformation[0] = NewMyStatic(IDS_STATIC_MANGE_INFORMATINO_3, CONTROL.land.returnUsername(), CRect(p, t, q, b), 0);
	p = rc.Width()*0.3;
	q = p + 50;
	t = rc.Height()*0.24;
	b = t + 20;
	s_personalInformation[1] = NewMyStatic(IDS_STATIC_MANGE_INFORMATINO_4, name, CRect(p, t, q, b), 0);
	p = rc.Width()*0.42;
	q = p + 100;
	t = rc.Height()*0.34;
	b = t + 20;
	s_personalInformation[2] = NewMyStatic(IDS_STATIC_MANGE_INFORMATINO_5, CONTROL.land.returnSex(), CRect(p, t, q, b), 0);
	p = rc.Width()*0.3;
	q = p + 50;
	t = rc.Height()*0.34;
	b = t + 20;
	s_personalInformation[3] = NewMyStatic(IDS_STATIC_MANGE_INFORMATINO_6, sex, CRect(p, t, q, b), 0);
	p = rc.Width()*0.42;
	q = p + 100;
	t = rc.Height()*0.44;
	b = t + 20;
	s_personalInformation[4] = NewMyStatic(IDS_STATIC_MANGE_INFORMATINO_7, CONTROL.land.returnTel(), CRect(p, t, q, b), 0);
	p = rc.Width()*0.3;
	q = p + 50;
	t = rc.Height()*0.44;
	b = t + 20;
	s_personalInformation[5] = NewMyStatic(IDS_STATIC_MANGE_INFORMATINO_8, tel, CRect(p, t, q, b), 0);
}



void CDialog_manage::OnBnClickedPersonalInformationNormal()  
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

	GetDlgItem(IDC_BUTTON7)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON6)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON8)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(false);

	GetWindowRect(&rc);
	int p;
	int q;
	int t, b;

	p = rc.Width()*0.42;
	q = p + 100;
	t = rc.Height()*0.24;
	b = t + 20;
	s_changeinformation[0] = NewMyEdit(IDS_EDIT_MANAGE_NAME, CRect(p, t, q, b), 0);
	p = rc.Width()*0.42;
	q = p + 100;
	t = rc.Height()*0.34;
	b = t + 20;
//	s_changeinformation[1] = NewMyEdit(IDS_EDIT_MANAGE_SEX, CRect(p, t, q, b), 0);
	c_changePerson_inf[1] = NewMyComboBox(IDS_EDIT_PERSON_SEX, CRect(p, t, q, b), 0);
	((CComboBox*)GetDlgItem(IDS_EDIT_PERSON_SEX))->AddString(CString("男"));
	((CComboBox*)GetDlgItem(IDS_EDIT_PERSON_SEX))->AddString(CString("女"));
	p = rc.Width()*0.42;
	q = p + 100;
	t = rc.Height()*0.44;
	b = t + 20;
	s_changeinformation[2] = NewMyEdit(IDS_EDIT_MANAGE_TEL, CRect(p, t, q, b), 0);

	s_changeinformation[0]->SetWindowText(CONTROL.land.returnUsername());
//	s_changeinformation[1]->SetWindowText(CONTROL.land.returnSex());
	s_changeinformation[2]->SetWindowText(CONTROL.land.returnTel());

	p = rc.Width()*0.7;
	q = p + 150;
	t = rc.Height()*0.65;
	b = t + 50;
	b_personalInformation[1] = NewMyButton(IDS_BUTTON_CHANGEINF_MANAGE_1, CRect(p, t, q, b), 0);
	p = rc.Width()*0.4;
	q = p + 150;
	t = rc.Height()*0.65;
	b = t + 50;
	b_personalInformation[2] = NewMyButton(IDS_BUTTON_CHANGEINF_MANAGE_2, CRect(p, t, q, b), 0);
}

void CDialog_manage::OnClickSaveChange()
{

	//	CDBOperation dbOper;
	//	bool bConn = dbOper.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "zbc", "666666");
	if (false == bConn)
	{

		CString alter("数据库连接出错！");
		MessageBox(alter);

		OnClickCancelChange();

	}
	_RecordsetPtr pRst;
	char sql[255] = { 0 };
	char *temp_1;
	char *temp_2;


	s_changeinformation[0]->GetWindowText(Change_name);
//	s_changeinformation[1]->GetWindowText(Change_sex);
	s_changeinformation[2]->GetWindowText(Change_tel);
	((CComboBox*)GetDlgItem(IDS_EDIT_PERSON_SEX))->GetWindowText(Change_sex);

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
		sprintf_s(sql, "update SYS_MANAGE set bmname = '%s' where bmno = '%s'", temp_1, temp_2);
		pRst = dbOper.ExecuteWithResSQL(sql);

		if (pRst == NULL)
		{
			CString alter("修改失败！！");
			MessageBox(alter);
		}
	}
	if (Change_sex != CONTROL.land.returnSex())
	{
		//		temp_1 = (LPSTR)(LPCTSTR)Change_sex;
		//		temp_2 = (LPSTR)(LPCTSTR)CONTROL.land.returnNumber();
		temp_1 = T2A(Change_sex);
		sprintf_s(sql, "update SYS_MANAGE set bmsex = '%s' where bmno = '%s'", temp_1, temp_2);
		pRst = dbOper.ExecuteWithResSQL(sql);

		if (pRst == NULL)
		{
			CString alter("修改失败！！");
			MessageBox(alter);
		}
	}
	if (Change_tel != CONTROL.land.returnTel())
	{
		//		temp_1 = (LPSTR)(LPCTSTR)Change_tel;
		//		temp_2 = (LPSTR)(LPCTSTR)CONTROL.land.returnNumber();
		temp_1 = T2A(Change_tel);
		sprintf_s(sql, "update SYS_MANAGE set bmtel = '%s' where bmno = '%s'", temp_1, temp_2);
		pRst = dbOper.ExecuteWithResSQL(sql);

		if (pRst == NULL)
		{
			CString alter("修改失败！！");
			MessageBox(alter);
		}
	}

	if (pRst != NULL)
	{
		CString alter("修改成功！！");
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

	GetDlgItem(IDC_BUTTON7)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON6)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON8)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(true);

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


void CDialog_manage::OnClickCancelChange()
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

	GetDlgItem(IDC_BUTTON7)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON6)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON8)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(true);

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

void CDialog_manage::OnBnClickedButton2()		//人员管理
{
	// TODO:  在此添加控件通知处理程序代码
	switchPages();

//	m_person_static.ShowWindow(SW_SHOW);
	//////////////

	GetWindowRect(&rc);
	int p;
	int q;
	int t, b;
	p = rc.Width()*0.25;
	q = p + rc.Width()*0.27;
	t = rc.Height()*0.05;
	b = t + rc.Height()*0.75;
	l_personInf[0] = NewMyListCtrl(IDS_USER_MATERIALLIST, CRect(p, t, q, b), 0);
	l_personInf[0]->InsertColumn(0, _T("证件号码"), LVCFMT_LEFT, 150);
	l_personInf[0]->InsertColumn(1, _T("姓名"), LVCFMT_LEFT, 70);

	

	_RecordsetPtr pRst;
	char sql[255] = { 0 };
	strcpy_s(sql, "select * from SYS_USER");
	pRst = dbOper.ExecuteWithResSQL(sql);
	if (NULL == pRst)
	{
		CString alter("查询数据出现错误！");
		MessageBox(alter);
	}
	else if (pRst->adoEOF)
	{
		pRst->Close();

		CString alter("查询数据出现错误！");
		MessageBox(alter);
	}
	else
	{
		pRst->MoveFirst(); //记录集指针移动到查询结果集的前面
		_variant_t vNum, vName;
		while (!pRst->adoEOF)
		{

			vNum = pRst->GetCollect(_variant_t("sno"));

			vName = pRst->GetCollect(_variant_t("sname"));

			string sno = (LPCSTR)_bstr_t(vNum);
			string name = (LPCSTR)_bstr_t(vName);


			CString sno_1;
			CString name_1;


			sno_1 = sno.c_str();
			name_1 = name.c_str();


			sno_1.Remove(' ');
			name_1.Remove(' ');


			int nRow = l_personInf[0]->InsertItem(0, sno_1);//插入行
			l_personInf[0]->SetItemText(nRow, 1, name_1);//设置数据

			///////////////////////////////////////////////////列表信息
			pRst->MoveNext();

		}
	}

	p = rc.Width()*0.55;
	q = p + 70;
	t = rc.Height()*0.73;
	b = t + 40;
	b_person_information[0] = NewMyButton(IDS_BUTTON_ADDPERSON, CRect(p, t, q, b), 0);
	p = rc.Width()*0.65;
	q = p + 70;
	t = rc.Height()*0.73;
	b = t + 40;
	b_person_information[1] = NewMyButton(IDS_BUTTON_CHANGEPERSON, CRect(p, t, q, b), 0);
	p = rc.Width()*0.75;
	q = p + 70;
	t = rc.Height()*0.73;
	b = t + 40;
	b_person_information[2] = NewMyButton(IDS_BUTTON_DELETEPERSON, CRect(p, t, q, b), 0);

	GetDlgItem(IDS_BUTTON_CHANGEPERSON)->EnableWindow(false);
	GetDlgItem(IDS_BUTTON_DELETEPERSON)->EnableWindow(false);
	

}

void CDialog_manage::CoutTheDetail(CString num)
{
	for (int i = 0; i < 12; i++)
	{
		if (s_person_inf[i])
		{
			s_person_inf[i]->DestroyWindow();
			delete s_person_inf[i];
			s_person_inf[i] = NULL;
		}
	}

	CString NAME("姓名:");
	CString SEX("性别:");
	CString TEL("电话:");
	CString NUM("证件号码:");
	CString ACADEMY("学院:");
	CString TEACHING("所授课程:");

	_RecordsetPtr pRst;
	char sql[255] = { 0 };
	USES_CONVERSION;
	char *temp;
	temp = T2A(num);
	sprintf_s(sql, "select * from SYS_USER WHERE SNO = '%s'", temp);
	pRst = dbOper.ExecuteWithResSQL(sql);
	if (NULL == pRst)
	{
		CString alter("查询数据出现错误！");
		MessageBox(alter);
	}
	else if (pRst->adoEOF)
	{
		pRst->Close();

		//CString alter("未查询到结果！");
		//MessageBox(alter);
	}
	else
	{
		pRst->MoveFirst(); //记录集指针移动到查询结果集的前面
		_variant_t vNum, vName, vSex, vTel, vAcademy, vTeaching;
		GetWindowRect(&rc);
		int p;
		int q;
		int t, b;
		while (!pRst->adoEOF)
		{

			vNum = pRst->GetCollect(_variant_t("sno"));

			vName = pRst->GetCollect(_variant_t("sname"));

			vSex = pRst->GetCollect(_variant_t("sex"));

			vTel = pRst->GetCollect(_variant_t("tel"));

			vAcademy = pRst->GetCollect(_variant_t("academy"));

			vTeaching = pRst->GetCollect(_variant_t("teaching"));

			string sno = (LPCSTR)_bstr_t(vNum);
			string name = (LPCSTR)_bstr_t(vName);
			string sex = (LPCSTR)_bstr_t(vSex);
			string tel = (LPCSTR)_bstr_t(vTel);
			string academy = (LPCSTR)_bstr_t(vAcademy);
			string teaching = (LPCSTR)_bstr_t(vTeaching);

			CString sno_1;
			CString name_1;
			CString sex_1;
			CString tel_1;
			CString academy_1;
			CString teaching_1;

			sno_1 = sno.c_str();
			name_1 = name.c_str();
			sex_1 = sex.c_str();
			tel_1 = tel.c_str();
			academy_1 = academy.c_str();
			teaching_1 = teaching.c_str();

			sno_1.Remove(' ');
			name_1.Remove(' ');
			sex_1.Remove(' ');
			tel_1.Remove(' ');
			academy_1.Remove(' ');
			teaching_1.Remove(' ');

			p = rc.Width()*0.64;
			q = p + 150;
			t = rc.Height()*0.07;
			b = t + 20;
			s_person_inf[0] = NewMyStatic(IDS_STATIC_MANAGE_INF_1, sno_1, CRect(p, t, q, b), 0);
			p = rc.Width()*0.55;
			q = p + 80;
			t = rc.Height()*0.07;
			b = t + 20;
			s_person_inf[1] = NewMyStatic(IDS_STATIC_MANAGE_INF_2, NUM, CRect(p, t, q, b), 0);

			p = rc.Width()*0.64;
			q = p + 150;
			t = rc.Height()*0.12;
			b = t + 20;
			s_person_inf[2] = NewMyStatic(IDS_STATIC_MANAGE_INF_3, name_1, CRect(p, t, q, b), 0);
			p = rc.Width()*0.55;
			q = p + 80;
			t = rc.Height()*0.12;
			b = t + 20;
			s_person_inf[3] = NewMyStatic(IDS_STATIC_MANAGE_INF_4, NAME, CRect(p, t, q, b), 0);

			p = rc.Width()*0.64;
			q = p + 150;
			t = rc.Height()*0.17;
			b = t + 20;
			s_person_inf[4] = NewMyStatic(IDS_STATIC_MANAGE_INF_5, sex_1, CRect(p, t, q, b), 0);
			p = rc.Width()*0.55;
			q = p + 80;
			t = rc.Height()*0.17;
			b = t + 20;
			s_person_inf[5] = NewMyStatic(IDS_STATIC_MANAGE_INF_6, SEX, CRect(p, t, q, b), 0);

			p = rc.Width()*0.64;
			q = p + 150;
			t = rc.Height()*0.22;
			b = t + 20;
			s_person_inf[6] = NewMyStatic(IDS_STATIC_MANAGE_INF_7, tel_1, CRect(p, t, q, b), 0);
			p = rc.Width()*0.55;
			q = p + 80;
			t = rc.Height()*0.22;
			b = t + 20;
			s_person_inf[7] = NewMyStatic(IDS_STATIC_MANAGE_INF_8, TEL, CRect(p, t, q, b), 0);

			p = rc.Width()*0.64;
			q = p + 150;
			t = rc.Height()*0.27;
			b = t + 20;
			s_person_inf[8] = NewMyStatic(IDS_STATIC_MANAGE_INF_9, academy_1, CRect(p, t, q, b), 0);
			p = rc.Width()*0.55;
			q = p + 80;
			t = rc.Height()*0.27;
			b = t + 20;
			s_person_inf[9] = NewMyStatic(IDS_STATIC_MANAGE_INF_10, ACADEMY, CRect(p, t, q, b), 0);

			p = rc.Width()*0.64;
			q = p + 150;
			t = rc.Height()*0.32;
			b = t + 20;
			s_person_inf[10] = NewMyStatic(IDS_STATIC_MANAGE_INF_11, teaching_1, CRect(p, t, q, b), 0);
			p = rc.Width()*0.55;
			q = p + 80;
			t = rc.Height()*0.32;
			b = t + 20;
			s_person_inf[11] = NewMyStatic(IDS_STATIC_MANAGE_INF_12, TEACHING, CRect(p, t, q, b), 0);

			pRst->MoveNext();

		}
	}
}

void CDialog_manage::OnClickInfOfPerson(NMHDR* pNMHDR, LRESULT* pResult)
{
	CString str;
	int nId;
	//首先得到点击的位置
	POSITION pos = l_personInf[0]->GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		GetDlgItem(IDS_BUTTON_CHANGEPERSON)->EnableWindow(true);
		GetDlgItem(IDS_BUTTON_DELETEPERSON)->EnableWindow(true);
		//得到行号，通过POSITION转化
		nId = (int)l_personInf[0]->GetNextSelectedItem(pos);
		//得到列中的内容（0表示第一列，同理1,2,3...表示第二，三，四...列）
		str = l_personInf[0]->GetItemText(nId, 0);
		CoutTheDetail(str);
	}
	else
	{
		GetDlgItem(IDS_BUTTON_CHANGEPERSON)->EnableWindow(false);
		GetDlgItem(IDS_BUTTON_DELETEPERSON)->EnableWindow(false);

	}
}


void CDialog_manage::OnClickChangePerson()
{
	
	CString num;
	CString name;
	CString sex;
	CString tel;
	CString academy;
	CString teaching;
	
	s_person_inf[0]->GetWindowText(num);
	s_person_inf[2]->GetWindowText(name);
	s_person_inf[4]->GetWindowText(sex);
	s_person_inf[6]->GetWindowText(tel);
	s_person_inf[8]->GetWindowText(academy);
	s_person_inf[10]->GetWindowText(teaching);

	Special_num = num;
	Special_name = name;
	Special_sex = sex;
	Special_tel = tel;
	Special_academy = academy;
	Special_teaching = teaching;

	for (int i = 0; i < 12; i++)
	{
		if (s_person_inf[i] && (i % 2 == 0))
		{
			s_person_inf[i]->DestroyWindow();
			delete s_person_inf[i];
			s_person_inf[i] = NULL;
		}
	}

	for (int i = 0; i <3; i++)
	{
		if (c_changePerson_inf[i] )
		{
			c_changePerson_inf[i]->DestroyWindow();
			delete c_changePerson_inf[i];
			c_changePerson_inf[i] = NULL;
		}
	}

	GetDlgItem(IDC_BUTTON7)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON6)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON8)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(false);

	GetDlgItem(IDS_BUTTON_ADDPERSON)->EnableWindow(false);
	GetDlgItem(IDS_BUTTON_CHANGEPERSON)->EnableWindow(false);
	GetDlgItem(IDS_BUTTON_DELETEPERSON)->EnableWindow(false);

	GetWindowRect(&rc);
	int p;
	int q;
	int t, b;

	p = rc.Width()*0.85;
	q = p + 70;
	t = rc.Height()*0.73;
	b = t + 40;
	b_person_information[3] = NewMyButton(IDS_BUTTON_SAVEPERSON, CRect(p, t, q, b), 0);
	p = rc.Width()*0.85;
	q = p + 70;
	t = rc.Height()*0.66;
	b = t + 40;
	b_person_information[4] = NewMyButton(IDS_BUTTON_CANCELPERSON, CRect(p, t, q, b), 0);

	p = rc.Width()*0.64;
	q = p + 150;
	t = rc.Height()*0.07;
	b = t + 20;
	s_changePerson_inf[0] = NewMyEdit(IDS_EDIT_PERSON_NUM, CRect(p, t, q, b), 0);

	p = rc.Width()*0.64;
	q = p + 150;
	t = rc.Height()*0.12;
	b = t + 20;
	s_changePerson_inf[1] = NewMyEdit(IDS_EDIT_PERSON_NAME, CRect(p, t, q, b), 0);

	p = rc.Width()*0.64;
	q = p + 150;
	t = rc.Height()*0.17;
	b = t + 20;
//	s_changePerson_inf[2] = NewMyEdit(IDS_EDIT_PERSON_SEX, CRect(p, t, q, b), 0);
	c_changePerson_inf[1] = NewMyComboBox(IDS_EDIT_PERSON_SEX, CRect(p, t, q, b), 0);
	((CComboBox*)GetDlgItem(IDS_EDIT_PERSON_SEX))->AddString(CString("男"));
	((CComboBox*)GetDlgItem(IDS_EDIT_PERSON_SEX))->AddString(CString("女"));

	p = rc.Width()*0.64;
	q = p + 150;
	t = rc.Height()*0.22;
	b = t + 20;
	s_changePerson_inf[3] = NewMyEdit(IDS_EDIT_PERSON_TEL, CRect(p, t, q, b), 0);

	p = rc.Width()*0.64;
	q = p + 150;
	t = rc.Height()*0.27;
	b = t + 20;
//	s_changePerson_inf[4] = NewMyEdit(IDS_EDIT_PERSON_ACADEMY, CRect(p, t, q, b), 0);
	c_changePerson_inf[0] = NewMyComboBox(IDS_COMBOBOX_ACADEMY, CRect(p, t, q, b),0);
	((CComboBox*)GetDlgItem(IDS_COMBOBOX_ACADEMY))->AddString(CString("计算机学院"));
	((CComboBox*)GetDlgItem(IDS_COMBOBOX_ACADEMY))->AddString(CString("数学科学学院"));
	((CComboBox*)GetDlgItem(IDS_COMBOBOX_ACADEMY))->AddString(CString("经济管理学院"));
	((CComboBox*)GetDlgItem(IDS_COMBOBOX_ACADEMY))->AddString(CString("化工学院"));

	p = rc.Width()*0.64;
	q = p + 150;
	t = rc.Height()*0.32;
	b = t + 20;
	s_changePerson_inf[5] = NewMyEdit(IDS_EDIT_PERSON_TEACHING, CRect(p, t, q, b), 0);

	s_changePerson_inf[0]->SetWindowText(num);
	s_changePerson_inf[1]->SetWindowText(name);
//	s_changePerson_inf[2]->SetWindowText(sex);
	s_changePerson_inf[3]->SetWindowText(tel);
	//s_changePerson_inf[4]->SetWindowText(academy);
	s_changePerson_inf[5]->SetWindowText(teaching);

}

void CDialog_manage::OnClickCancelChange_1()
{

	CString num("");

	for (int i = 0; i < 12; i++)
	{
		if (s_person_inf[i] && (i % 2 != 0))
		{
			s_person_inf[i]->DestroyWindow();
			delete s_person_inf[i];
			s_person_inf[i] = NULL;
		}
	}
	s_changePerson_inf[0]->GetWindowText(num);

	for (int i = 0; i <6; i++)
	{
		if (s_changePerson_inf[i] )
		{
			s_changePerson_inf[i]->DestroyWindow();
			delete s_changePerson_inf[i];
			s_changePerson_inf[i] = NULL;
		}
	}

	for (int i = 0; i <3; i++)
	{
		if (c_changePerson_inf[i])
		{
			c_changePerson_inf[i]->DestroyWindow();
			delete c_changePerson_inf[i];
			c_changePerson_inf[i] = NULL;
		}
	}
	if (b_person_information[3])
	{
		b_person_information[3]->DestroyWindow();
		delete b_person_information[3];
		b_person_information[3] = NULL;
	}
	if (b_person_information[5])
	{
		b_person_information[5]->DestroyWindow();
		delete b_person_information[5];
		b_person_information[5] = NULL;
	}
	b_person_information[4]->DestroyWindow();
	delete b_person_information[4];
	b_person_information[4] = NULL;

	GetDlgItem(IDC_BUTTON7)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON6)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON8)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(true);

	GetDlgItem(IDS_BUTTON_ADDPERSON)->EnableWindow(true);
	GetDlgItem(IDS_BUTTON_CHANGEPERSON)->EnableWindow(true);
	GetDlgItem(IDS_BUTTON_DELETEPERSON)->EnableWindow(true);
	
	CoutTheDetail(num);

}

bool CDialog_manage::CheckNumInDB(CString num)
{
	if (false == bConn)
	{

		CString alter("数据库连接出错！");
		MessageBox(alter);

		OnClickCancelChange_1();

	}
	_RecordsetPtr pRst;
	char sql[255] = { 0 };
	char *temp_1;

	USES_CONVERSION;
	temp_1 = T2A(num);
	sprintf_s(sql, "select * from SYS_USER  where sno = '%s'", temp_1);

	pRst = dbOper.ExecuteWithResSQL(sql);

	if (pRst == NULL)
	{
		CString alter("查询失败！！");
		MessageBox(alter);
		return false;
	}
	if (pRst->adoEOF)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CDialog_manage::OnClickSavePersonChange()
{
	if (false == bConn)
	{

		CString alter("数据库连接出错！");
		MessageBox(alter);

		OnClickCancelChange_1();

	}
	_RecordsetPtr pRst;
	char sql[255] = { 0 };
	char *temp_1;
	char *temp_2;



	s_changePerson_inf[0]->GetWindowText(Change_num);
	s_changePerson_inf[1]->GetWindowText(Change_name);
//	s_changePerson_inf[2]->GetWindowText(Change_sex);
	s_changePerson_inf[3]->GetWindowText(Change_tel);
	s_changePerson_inf[5]->GetWindowText(Change_teaching);
	((CComboBox*)GetDlgItem(IDS_COMBOBOX_ACADEMY))->GetWindowText(Change_academy);
	((CComboBox*)GetDlgItem(IDS_EDIT_PERSON_SEX))->GetWindowText(Change_sex);
	if (Change_academy == "")
	{
		Change_academy = Special_academy;
	}

	Change_name.Remove(' ');
	Change_sex.Remove(' ');
	Change_num.Remove(' ');
	Change_tel.Remove(' ');
	Change_academy.Remove(' ');
	Change_teaching.Remove(' ');
	USES_CONVERSION;
	//	int n_1 = CONTROL.land.returnNumber().GetLength();
	//	int len = WideCharToMultiByte(CP_ACP, 0, CONTROL.land.returnNumber(), CONTROL.land.returnNumber().GetLength(), NULL, 0, NULL, NULL);
	//	temp_2 = new char[len + 1];
	//	WideCharToMultiByte(CP_ACP, 0, CONTROL.land.returnNumber(), n_1, temp_2, len, NULL, NULL);
	//	temp_2[len + 1] = '/0';
	temp_2 = T2A(Special_num);

	if (CheckNumInDB(Change_num))          //编号修改
	{
		if (check_number(Change_num))
		{
			//		temp_1 = new char[100];
			//		temp_1 = (LPSTR)(LPCTSTR)Change_name;
			//		temp_2 = (LPSTR)(LPCTSTR)CONTROL.land.returnNumber();
			//		int n = Change_name.GetLength();
			//		int len = WideCharToMultiByte(CP_ACP, 0, Change_name, Change_name.GetLength(), NULL, 0, NULL, NULL);
			//		temp_1 = new char[len + 1];
			//		WideCharToMultiByte(CP_ACP, 0, Change_name, n, temp_1, len, NULL, NULL);
			//		temp_1[len + 1] = '/0';

			temp_1 = T2A(Change_num);
			sprintf_s(sql, "update SYS_USER set sno = '%s' where sno = '%s'", temp_1, temp_2);
			pRst = dbOper.ExecuteWithResSQL(sql);

			if (pRst == NULL)
			{
				CString alter("修改失败！！");
				MessageBox(alter);
			}
		}
		else
		{
			MessageBox(CString("存在违法字符！"));
		}
	}
	temp_2 = T2A(Change_num);
	if (Change_name != Special_name)		//姓名
	{
		//		temp_1 = (LPSTR)(LPCTSTR)Change_sex;
		//		temp_2 = (LPSTR)(LPCTSTR)CONTROL.land.returnNumber();
		temp_1 = T2A(Change_name);
		sprintf_s(sql, "update SYS_USER set sname = '%s' where sno = '%s'", temp_1, temp_2);
		pRst = dbOper.ExecuteWithResSQL(sql);

		if (pRst == NULL)
		{
			CString alter("修改失败！！");
			MessageBox(alter);
		}
	}
	if (Change_sex != Special_sex)			//性别
	{
		//		temp_1 = (LPSTR)(LPCTSTR)Change_tel;
		//		temp_2 = (LPSTR)(LPCTSTR)CONTROL.land.returnNumber();
		temp_1 = T2A(Change_sex);
		sprintf_s(sql, "update SYS_USER set  sex= '%s' where sno = '%s'", temp_1, temp_2);
		pRst = dbOper.ExecuteWithResSQL(sql);

		if (pRst == NULL)
		{
			CString alter("修改失败！！");
			MessageBox(alter);
		}
	}
	if (Change_tel != Special_tel)			//电话
	{
		if (check_number(Change_tel))
		{
			//		temp_1 = (LPSTR)(LPCTSTR)Change_tel;
			//		temp_2 = (LPSTR)(LPCTSTR)CONTROL.land.returnNumber();
			temp_1 = T2A(Change_tel);
			sprintf_s(sql, "update SYS_USER set  sex= '%s' where sno = '%s'", temp_1, temp_2);
			pRst = dbOper.ExecuteWithResSQL(sql);

			if (pRst == NULL)
			{
				CString alter("修改失败！！");
				MessageBox(alter);
			}
		}
		else
		{
			MessageBox(CString("存在违法字符！"));
		}
	}
	if (Change_academy != Special_academy)			//学院
	{
		//		temp_1 = (LPSTR)(LPCTSTR)Change_tel;
		//		temp_2 = (LPSTR)(LPCTSTR)CONTROL.land.returnNumber();
		temp_1 = T2A(Change_academy);
		sprintf_s(sql, "update SYS_USER set academy= '%s' where sno = '%s'", temp_1, temp_2);
		pRst = dbOper.ExecuteWithResSQL(sql);

		if (pRst == NULL)
		{
			CString alter("修改失败！！");
			MessageBox(alter);
		}
	}
	if (Change_teaching != Special_teaching)			//职责
	{
		//		temp_1 = (LPSTR)(LPCTSTR)Change_tel;
		//		temp_2 = (LPSTR)(LPCTSTR)CONTROL.land.returnNumber();
		temp_1 = T2A(Change_teaching);
		sprintf_s(sql, "update SYS_USER set teaching= '%s' where sno = '%s'", temp_1, temp_2);
		pRst = dbOper.ExecuteWithResSQL(sql);

		if (pRst == NULL)
		{
			CString alter("修改失败！！");
			MessageBox(alter);
		}
	}

	if (pRst != NULL)
	{
		CString alter("修改成功！！");
		MessageBox(alter);
	}


	for (int i = 0; i < 6; i++)
	{
		if (s_changePerson_inf[i])
		{
			s_changePerson_inf[i]->DestroyWindow();
			delete s_changePerson_inf[i];
			s_changePerson_inf[i] = NULL;
		}
	}

	c_changePerson_inf[0]->DestroyWindow();
	delete c_changePerson_inf[0];
	c_changePerson_inf[0] = NULL;

	b_person_information[3]->DestroyWindow();
	delete b_person_information[3];
	b_person_information[3] = NULL;
	b_person_information[4]->DestroyWindow();
	delete b_person_information[4];
	b_person_information[4] = NULL;

	GetDlgItem(IDC_BUTTON7)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON6)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON8)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(true);

	for (int i = 0; i < 12; i++)
	{
		if (s_person_inf[i] && (i % 2 != 0))
		{
			s_person_inf[i]->DestroyWindow();
			delete s_person_inf[i];
			s_person_inf[i] = NULL;
		}
	}

	OnBnClickedButton2();
}

void CDialog_manage::OnClickAddPerson()
{
	for (int i = 0; i < 12; i++)
	{
		if (s_person_inf[i])
		{
			s_person_inf[i]->DestroyWindow();
			delete s_person_inf[i];
			s_person_inf[i] = NULL;
		}
	}

	GetDlgItem(IDC_BUTTON7)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON6)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON8)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(false);

	GetDlgItem(IDS_BUTTON_ADDPERSON)->EnableWindow(false);
	GetDlgItem(IDS_BUTTON_CHANGEPERSON)->EnableWindow(false);
	GetDlgItem(IDS_BUTTON_DELETEPERSON)->EnableWindow(false);

	GetWindowRect(&rc);
	int p;
	int q;
	int t, b;

	CString NAME("姓名:");
	CString SEX("性别:");
	CString TEL("电话:");
	CString NUM("证件号码:");
	CString ACADEMY("学院:");
	CString TEACHING("所授课程:");

	p = rc.Width()*0.55;
	q = p + 80;
	t = rc.Height()*0.07;
	b = t + 20;
	s_person_inf[1] = NewMyStatic(IDS_STATIC_MANAGE_INF_2, NUM, CRect(p, t, q, b), 0);

	p = rc.Width()*0.55;
	q = p + 80;
	t = rc.Height()*0.12;
	b = t + 20;
	s_person_inf[3] = NewMyStatic(IDS_STATIC_MANAGE_INF_4, NAME, CRect(p, t, q, b), 0);


	p = rc.Width()*0.55;
	q = p + 80;
	t = rc.Height()*0.17;
	b = t + 20;
	s_person_inf[5] = NewMyStatic(IDS_STATIC_MANAGE_INF_6, SEX, CRect(p, t, q, b), 0);


	p = rc.Width()*0.55;
	q = p + 80;
	t = rc.Height()*0.22;
	b = t + 20;
	s_person_inf[7] = NewMyStatic(IDS_STATIC_MANAGE_INF_8, TEL, CRect(p, t, q, b), 0);


	p = rc.Width()*0.55;
	q = p + 80;
	t = rc.Height()*0.27;
	b = t + 20;
	s_person_inf[9] = NewMyStatic(IDS_STATIC_MANAGE_INF_10, ACADEMY, CRect(p, t, q, b), 0);


	p = rc.Width()*0.55;
	q = p + 80;
	t = rc.Height()*0.32;
	b = t + 20;
	s_person_inf[11] = NewMyStatic(IDS_STATIC_MANAGE_INF_12, TEACHING, CRect(p, t, q, b), 0);


	

	
	p = rc.Width()*0.85;
	q = p + 70;
	t = rc.Height()*0.73;
	b = t + 40;
	b_person_information[5] = NewMyButton(IDS_BUTTON_SAVEADDPERSON, CRect(p, t, q, b), 0);
	p = rc.Width()*0.85;
	q = p + 70;
	t = rc.Height()*0.66;
	b = t + 40;
	b_person_information[4] = NewMyButton(IDS_BUTTON_CANCELPERSON, CRect(p, t, q, b), 0);

	p = rc.Width()*0.64;
	q = p + 150;
	t = rc.Height()*0.07;
	b = t + 20;
	s_changePerson_inf[0] = NewMyEdit(IDS_EDIT_PERSON_NUM, CRect(p, t, q, b), 0);

	p = rc.Width()*0.64;
	q = p + 150;
	t = rc.Height()*0.12;
	b = t + 20;
	s_changePerson_inf[1] = NewMyEdit(IDS_EDIT_PERSON_NAME, CRect(p, t, q, b), 0);

	p = rc.Width()*0.64;
	q = p + 150;
	t = rc.Height()*0.17;
	b = t + 20;
//	s_changePerson_inf[2] = NewMyEdit(IDS_EDIT_PERSON_SEX, CRect(p, t, q, b), 0);

	c_changePerson_inf[1] = NewMyComboBox(IDS_EDIT_PERSON_SEX, CRect(p, t, q, b), 0);
	((CComboBox*)GetDlgItem(IDS_EDIT_PERSON_SEX))->AddString(CString("男"));
	((CComboBox*)GetDlgItem(IDS_EDIT_PERSON_SEX))->AddString(CString("女"));

	p = rc.Width()*0.64;
	q = p + 150;
	t = rc.Height()*0.22;
	b = t + 20;
	s_changePerson_inf[3] = NewMyEdit(IDS_EDIT_PERSON_TEL, CRect(p, t, q, b), 0);

	p = rc.Width()*0.64;
	q = p + 150;
	t = rc.Height()*0.27;
	b = t + 20;
	//	s_changePerson_inf[4] = NewMyEdit(IDS_EDIT_PERSON_ACADEMY, CRect(p, t, q, b), 0);
	c_changePerson_inf[0] = NewMyComboBox(IDS_COMBOBOX_ACADEMY, CRect(p, t, q, b), 0);
	((CComboBox*)GetDlgItem(IDS_COMBOBOX_ACADEMY))->AddString(CString("计算机学院"));
	((CComboBox*)GetDlgItem(IDS_COMBOBOX_ACADEMY))->AddString(CString("数学科学学院"));
	((CComboBox*)GetDlgItem(IDS_COMBOBOX_ACADEMY))->AddString(CString("经济管理学院"));
	((CComboBox*)GetDlgItem(IDS_COMBOBOX_ACADEMY))->AddString(CString("化工学院"));

	p = rc.Width()*0.64;
	q = p + 150;
	t = rc.Height()*0.32;
	b = t + 20;
	s_changePerson_inf[5] = NewMyEdit(IDS_EDIT_PERSON_TEACHING, CRect(p, t, q, b), 0);

	s_changePerson_inf[0]->SetWindowTextW(CString(""));
}

void CDialog_manage::OnClickSaveAddPerson()
{
	USES_CONVERSION;

	CString add_num("");
	CString add_name("");
	CString add_sex("");
	CString add_tel("");
	CString add_academy("");
	CString add_teaching("");
	CString add_password("");

	s_changePerson_inf[0]->GetWindowText(add_num);
	s_changePerson_inf[1]->GetWindowText(add_name);
//	s_changePerson_inf[2]->GetWindowText(add_sex);
	s_changePerson_inf[3]->GetWindowText(add_tel);
	s_changePerson_inf[5]->GetWindowText(add_teaching);
	((CComboBox*)GetDlgItem(IDS_COMBOBOX_ACADEMY))->GetWindowText(add_academy);
	((CComboBox*)GetDlgItem(IDS_EDIT_PERSON_SEX))->GetWindowText(add_sex);


	add_num.Remove(' ');
	add_name.Remove(' ');
	add_sex.Remove(' ');
	add_tel.Remove(' ');
	add_academy.Remove(' ');
	add_teaching.Remove(' ');

	if (false == bConn)
	{

		CString alter("数据库连接出错！");
		MessageBox(alter);

		OnClickCancelChange_1();

	}
	if (add_num == "")
	{
		MessageBox(CString("证件号码不能为空！"));
	}
	if (add_name == "")
	{
		MessageBox(CString("姓名不能为空！"));
	}
	if (add_academy == "")
	{
		MessageBox(CString("学院不能为空！"));
	}
	if (add_teaching == "")
	{
		MessageBox(CString("职称不能为空！"));
	}
	if (!CheckNumInDB(add_num))
	{
		MessageBox(CString("该证件号码已经存在"));
	}
	if (add_num != "" && add_name != "" && add_academy != "" && add_teaching != "" && CheckNumInDB(add_num))
	{
		if (check_number(add_num) && check_number(add_tel))
		{
			add_password = add_num.Right(6);
			_RecordsetPtr pRst;
			char sql[255] = { 0 };
			char *temp_num;
			char *temp_name;
			char *temp_sex;
			char *temp_tel;
			char *temp_academy;
			char *temp_teaching;
			char *temp_password;

			temp_num = T2A(add_num);
			temp_name = T2A(add_name);
			temp_password = T2A(add_password);
			temp_tel = T2A(add_tel);
			temp_sex = T2A(add_sex);
			temp_academy = T2A(add_academy);
			temp_teaching = T2A(add_teaching);

			sprintf_s(sql, "insert into SYS_USER values('%s','%s','%s','%s','%s','%s','%s')", temp_num, temp_name, temp_password, temp_tel, temp_sex, temp_academy, temp_teaching);
			pRst = dbOper.ExecuteWithResSQL(sql);

			if (pRst == NULL)
			{
				CString alter("添加失败！！");
				MessageBox(alter);
			}

			if (pRst != NULL)
			{
				CString alter("修改成功！！");
				MessageBox(alter);
				int nRow = l_personInf[0]->InsertItem(0, add_num);//插入行
				l_personInf[0]->SetItemText(nRow, 1, add_name);//设置数据
			}
		}
		else
		{
			MessageBox(CString("存在违法字符！"));
		}
	}
	else
	{
		MessageBox(CString("存在空信息或编号已存在！"));
	}

	
	OnClickCancelChange_1();

}

void CDialog_manage::OnClickDeletePerson()
{
	CString num;
	USES_CONVERSION;
	for (int i = 0; i < l_personInf[0]->GetItemCount(); i++)
	{
		if (l_personInf[0]->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED || l_personInf[0]->GetCheck(i))
		{
			num = l_personInf[0]->GetItemText(i, 0);
			_RecordsetPtr pRst;
			char sql[255] = { 0 };
			char *temp;
			temp = T2A(num);
			sprintf_s(sql,"delete from SYS_USER where sno = '%s'",temp);
			pRst = dbOper.ExecuteWithResSQL(sql);
			if (pRst == NULL)
			{
				CString alter("删除失败！！");
				MessageBox(alter);
			}

			if (pRst != NULL)
			{
				CString alter("删除成功！！");
				MessageBox(alter);
				l_personInf[0]->DeleteItem(i);
			}		
		}
	}
	OnBnClickedButton2();
}

void CDialog_manage::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	switchPages();


	/////////////////////////////
	GetWindowRect(&rc);
	int p;
	int q;
	int t, b;
	p = rc.Width()*0.25;
	q = p + rc.Width()*0.27;;
	t = rc.Height()*0.05;
	b = t + rc.Height()*0.75;
	l_personInf[1] = NewMyListCtrl(IDS_MANAGE_MATERIALLIST, CRect(p, t, q, b), 0);
	l_personInf[1]->InsertColumn(0, _T("教材编号"), LVCFMT_LEFT, 90);
	l_personInf[1]->InsertColumn(1, _T("书名"), LVCFMT_LEFT, 160);



	_RecordsetPtr pRst;
	char sql[255] = { 0 };
	strcpy_s(sql, "select * from SYS_MATERIAL");
	pRst = dbOper.ExecuteWithResSQL(sql);
	if (NULL == pRst)
	{
		CString alter("查询数据出现错误！");
		MessageBox(alter);
	}
	else if (pRst->adoEOF)
	{
		pRst->Close();

		CString alter("查询数据出现错误！");
		MessageBox(alter);
	}
	else
	{
		pRst->MoveFirst(); //记录集指针移动到查询结果集的前面
		_variant_t vNum, vName;
		while (!pRst->adoEOF)
		{

			vNum = pRst->GetCollect(_variant_t("bno"));

			vName = pRst->GetCollect(_variant_t("bname"));

			string bno = (LPCSTR)_bstr_t(vNum);
			string bname = (LPCSTR)_bstr_t(vName);


			CString bno_1;
			CString bname_1;


			bno_1 = bno.c_str();
			bname_1 = bname.c_str();


			bno_1.Remove(' ');
			bname_1.Remove(' ');


			int nRow = l_personInf[1]->InsertItem(0, bno_1);//插入行
			l_personInf[1]->SetItemText(nRow, 1, bname_1);//设置数据

			///////////////////////////////////////////////////列表信息
			pRst->MoveNext();

		}
	}

	p = rc.Width()*0.55;
	q = p + 70;
	t = rc.Height()*0.73;
	b = t + 40;
	b_person_information[0] = NewMyButton(IDS_BUTTON_ADDMATERIAL, CRect(p, t, q, b), 0);
	p = rc.Width()*0.65;
	q = p + 70;
	t = rc.Height()*0.73;
	b = t + 40;
	b_person_information[1] = NewMyButton(IDS_BUTTON_CHANGEMATERIAL_INF, CRect(p, t, q, b), 0);
	p = rc.Width()*0.75;
	q = p + 70;
	t = rc.Height()*0.73;
	b = t + 40;
	b_person_information[2] = NewMyButton(IDS_BUTTON_DELETEMATERIAL, CRect(p, t, q, b), 0);

	GetDlgItem(IDS_BUTTON_CHANGEMATERIAL_INF)->EnableWindow(false);
	GetDlgItem(IDS_BUTTON_DELETEMATERIAL)->EnableWindow(false);

}

void CDialog_manage::OnClickInfOfMaterial(NMHDR* pNMHDR, LRESULT* pResult)
{
	CString str;
	int nId;
	//首先得到点击的位置
	POSITION pos = l_personInf[1]->GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		GetDlgItem(IDS_BUTTON_CHANGEMATERIAL_INF)->EnableWindow(true);
		GetDlgItem(IDS_BUTTON_DELETEMATERIAL)->EnableWindow(true);
		//得到行号，通过POSITION转化
		nId = (int)l_personInf[1]->GetNextSelectedItem(pos);
		//得到列中的内容（0表示第一列，同理1,2,3...表示第二，三，四...列）
		str = l_personInf[1]->GetItemText(nId, 0);
		CoutTheDetail_material(str);
	}
	else
	{
		GetDlgItem(IDS_BUTTON_CHANGEMATERIAL_INF)->EnableWindow(false);
		GetDlgItem(IDS_BUTTON_DELETEMATERIAL)->EnableWindow(false);

	}
}


void CDialog_manage::CoutTheDetail_material(CString num)
{
	for (int i = 0; i < 12; i++)
	{
		if (s_person_inf[i])
		{
			s_person_inf[i]->DestroyWindow();
			delete s_person_inf[i];
			s_person_inf[i] = NULL;
		}
	}

	CString NAME("名称:");
	CString AUTHOR("作者:");
	CString PRICE("价格:");
	CString NUM("编号:");
	CString ISBN("ISBN:");
	CString BBC("版次:");

	_RecordsetPtr pRst;
	char sql[255] = { 0 };
	USES_CONVERSION;
	char *temp;
	temp = T2A(num);
	sprintf_s(sql, "select * from SYS_MATERIAL WHERE BNO = '%s'", temp);
	pRst = dbOper.ExecuteWithResSQL(sql);
	if (NULL == pRst)
	{
		CString alter("查询数据出现错误！");
		MessageBox(alter);
	}
	else if (pRst->adoEOF)
	{
		pRst->Close();

		//CString alter("未查询到结果！");
		//MessageBox(alter);
	}
	else
	{
		pRst->MoveFirst(); //记录集指针移动到查询结果集的前面
		_variant_t vNum, vName, vAuthor, vPrice, vIsbn, vBbc;
		GetWindowRect(&rc);
		int p;
		int q;
		int t, b;
		while (!pRst->adoEOF)
		{

			vNum = pRst->GetCollect(_variant_t("bno"));

			vName = pRst->GetCollect(_variant_t("bname"));

			vAuthor = pRst->GetCollect(_variant_t("bauthor"));

			vPrice = pRst->GetCollect(_variant_t("bprice"));

			vIsbn = pRst->GetCollect(_variant_t("isbn"));

			vBbc = pRst->GetCollect(_variant_t("bbc"));

			string bno = (LPCSTR)_bstr_t(vNum);
			string bname = (LPCSTR)_bstr_t(vName);
			string author = (LPCSTR)_bstr_t(vAuthor);
			string price = (LPCSTR)_bstr_t(vPrice);
			string isbn = (LPCSTR)_bstr_t(vIsbn);
			string bbc = (LPCSTR)_bstr_t(vBbc);

			CString bno_1;
			CString bname_1;
			CString price_1;
			CString author_1;
			CString isbn_1;
			CString bbc_1;

			bno_1 = bno.c_str();
			bname_1 = bname.c_str();
			price_1 = price.c_str();
			author_1 = author.c_str();
			isbn_1 = isbn.c_str();
			bbc_1 = bbc.c_str();

			bno_1.Remove(' ');
			bname_1.Remove(' ');
			price_1.Remove(' ');
			author_1.Remove(' ');
			isbn_1.Remove(' ');
			bbc_1.Remove(' ');

			CString yuan("元");
			price_1 += yuan;

			p = rc.Width()*0.64;
			q = p + 150;
			t = rc.Height()*0.07;
			b = t + 20;
			s_person_inf[0] = NewMyStatic(IDS_STATIC_MANAGE_INF_1, bno_1, CRect(p, t, q, b), 0);
			p = rc.Width()*0.55;
			q = p + 80;
			t = rc.Height()*0.07;
			b = t + 20;
			s_person_inf[1] = NewMyStatic(IDS_STATIC_MANAGE_INF_2, NUM, CRect(p, t, q, b), 0);

			p = rc.Width()*0.64;
			q = p + 250;
			t = rc.Height()*0.12;
			b = t + 20;
			s_person_inf[2] = NewMyStatic(IDS_STATIC_MANAGE_INF_3, bname_1, CRect(p, t, q, b), 0);
			p = rc.Width()*0.55;
			q = p + 80;
			t = rc.Height()*0.12;
			b = t + 20;
			s_person_inf[3] = NewMyStatic(IDS_STATIC_MANAGE_INF_4, NAME, CRect(p, t, q, b), 0);

			p = rc.Width()*0.64;
			q = p + 150;
			t = rc.Height()*0.17;
			b = t + 20;
			s_person_inf[4] = NewMyStatic(IDS_STATIC_MANAGE_INF_5, author_1, CRect(p, t, q, b), 0);
			p = rc.Width()*0.55;
			q = p + 80;
			t = rc.Height()*0.17;
			b = t + 20;
			s_person_inf[5] = NewMyStatic(IDS_STATIC_MANAGE_INF_6, AUTHOR, CRect(p, t, q, b), 0);

			p = rc.Width()*0.64;
			q = p + 150;
			t = rc.Height()*0.22;
			b = t + 20;
			s_person_inf[6] = NewMyStatic(IDS_STATIC_MANAGE_INF_7, price_1, CRect(p, t, q, b), 0);
			p = rc.Width()*0.55;
			q = p + 80;
			t = rc.Height()*0.22;
			b = t + 20;
			s_person_inf[7] = NewMyStatic(IDS_STATIC_MANAGE_INF_8, PRICE, CRect(p, t, q, b), 0);

			p = rc.Width()*0.64;
			q = p + 150;
			t = rc.Height()*0.27;
			b = t + 20;
			s_person_inf[8] = NewMyStatic(IDS_STATIC_MANAGE_INF_9, isbn_1, CRect(p, t, q, b), 0);
			p = rc.Width()*0.55;
			q = p + 80;
			t = rc.Height()*0.27;
			b = t + 20;
			s_person_inf[9] = NewMyStatic(IDS_STATIC_MANAGE_INF_10, ISBN, CRect(p, t, q, b), 0);

			p = rc.Width()*0.64;
			q = p + 150;
			t = rc.Height()*0.32;
			b = t + 20;
			s_person_inf[10] = NewMyStatic(IDS_STATIC_MANAGE_INF_11, bbc_1, CRect(p, t, q, b), 0);
			p = rc.Width()*0.55;
			q = p + 80;
			t = rc.Height()*0.32;
			b = t + 20;
			s_person_inf[11] = NewMyStatic(IDS_STATIC_MANAGE_INF_12, BBC, CRect(p, t, q, b), 0);

			pRst->MoveNext();

		}
	}
}


void CDialog_manage::OnClickChangeMaterial()
{

	CString num;
	CString name;
	CString author;
	CString price;
	CString isbn;
	CString bbc;

	s_person_inf[0]->GetWindowText(num);
	s_person_inf[2]->GetWindowText(name);
	s_person_inf[4]->GetWindowText(author);
	s_person_inf[6]->GetWindowText(price);
	s_person_inf[8]->GetWindowText(isbn);
	s_person_inf[10]->GetWindowText(bbc);

	Special_num = num;
	Special_name = name;
	Special_author = author;
	Special_price = price;
	Special_isbn = isbn;
	Special_bbc = bbc;

	for (int i = 0; i < 12; i++)
	{
		if (s_person_inf[i] && (i % 2 == 0))
		{
			s_person_inf[i]->DestroyWindow();
			delete s_person_inf[i];
			s_person_inf[i] = NULL;
		}
	}

	GetDlgItem(IDC_BUTTON7)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON6)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON8)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(false);

	GetDlgItem(IDS_BUTTON_ADDMATERIAL)->EnableWindow(false);
	GetDlgItem(IDS_BUTTON_CHANGEMATERIAL_INF)->EnableWindow(false);
	GetDlgItem(IDS_BUTTON_DELETEMATERIAL)->EnableWindow(false);

	GetWindowRect(&rc);
	int p;
	int q;
	int t, b;

	p = rc.Width()*0.85;
	q = p + 70;
	t = rc.Height()*0.73;
	b = t + 40;
	b_person_information[3] = NewMyButton(IDS_BUTTON_SAVEMATERIALCHANGE, CRect(p, t, q, b), 0);
	p = rc.Width()*0.85;
	q = p + 70;
	t = rc.Height()*0.66;
	b = t + 40;
	b_person_information[4] = NewMyButton(IDS_BUTTON_CANCELCHANGEMATERIAL, CRect(p, t, q, b), 0);

	p = rc.Width()*0.64;
	q = p + 150;
	t = rc.Height()*0.07;
	b = t + 20;
	s_changePerson_inf[0] = NewMyEdit(IDS_EDIT_PERSON_NUM, CRect(p, t, q, b), 0);

	p = rc.Width()*0.64;
	q = p + 150;
	t = rc.Height()*0.12;
	b = t + 20;
	s_changePerson_inf[1] = NewMyEdit(IDS_EDIT_PERSON_NAME, CRect(p, t, q, b), 0);

	p = rc.Width()*0.64;
	q = p + 150;
	t = rc.Height()*0.17;
	b = t + 20;
	s_changePerson_inf[2] = NewMyEdit(IDS_EDIT_PERSON_SEX, CRect(p, t, q, b), 0);

	p = rc.Width()*0.64;
	q = p + 150;
	t = rc.Height()*0.22;
	b = t + 20;
	s_changePerson_inf[3] = NewMyEdit(IDS_EDIT_PERSON_TEL, CRect(p, t, q, b), 0);

	p = rc.Width()*0.64;
	q = p + 150;
	t = rc.Height()*0.27;
	b = t + 20;
	s_changePerson_inf[4] = NewMyEdit(IDS_EDIT_PERSON_ACADEMY, CRect(p, t, q, b), 0);
//	c_changePerson_inf[0] = NewMyComboBox(IDS_COMBOBOX_ACADEMY, CRect(p, t, q, b), 0);
//	((CComboBox*)GetDlgItem(IDS_COMBOBOX_ACADEMY))->AddString(CString("计算机学院"));
//	((CComboBox*)GetDlgItem(IDS_COMBOBOX_ACADEMY))->AddString(CString("数学科学学院"));
//	((CComboBox*)GetDlgItem(IDS_COMBOBOX_ACADEMY))->AddString(CString("经济管理学院"));
//	((CComboBox*)GetDlgItem(IDS_COMBOBOX_ACADEMY))->AddString(CString("化工学院"));

	p = rc.Width()*0.64;
	q = p + 150;
	t = rc.Height()*0.32;
	b = t + 20;
	s_changePerson_inf[5] = NewMyEdit(IDS_EDIT_PERSON_TEACHING, CRect(p, t, q, b), 0);

	s_changePerson_inf[0]->SetWindowText(num);
	s_changePerson_inf[1]->SetWindowText(name);
	s_changePerson_inf[2]->SetWindowText(author);
	s_changePerson_inf[3]->SetWindowText(price);
	s_changePerson_inf[4]->SetWindowText(isbn);
	s_changePerson_inf[5]->SetWindowText(bbc);

}

bool CDialog_manage::CheckNumInDB_material(CString num)
{
	if (false == bConn)
	{

		CString alter("数据库连接出错！");
		MessageBox(alter);

		OnClickCancelChange_2();

	}
	_RecordsetPtr pRst;
	char sql[255] = { 0 };
	char *temp_1;

	USES_CONVERSION;
	temp_1 = T2A(num);
	sprintf_s(sql, "select * from SYS_MATERIAL  where bno = '%s'", temp_1);

	pRst = dbOper.ExecuteWithResSQL(sql);

	if (pRst == NULL)
	{
		CString alter("查询失败！！");
		MessageBox(alter);
		return false;
	}
	if (pRst->adoEOF)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CDialog_manage::OnClickSaveMaterialChange()
{
	if (false == bConn)
	{

		CString alter("数据库连接出错！");
		MessageBox(alter);

		OnClickCancelChange_2();

	}
	_RecordsetPtr pRst;
	char sql[255] = { 0 };
	char *temp_1;
	char *temp_2;



	s_changePerson_inf[0]->GetWindowText(Change_num);
	s_changePerson_inf[1]->GetWindowText(Change_name);
	s_changePerson_inf[2]->GetWindowText(Change_author);
	s_changePerson_inf[3]->GetWindowText(Change_price);
	s_changePerson_inf[4]->GetWindowText(Change_isbn);
	s_changePerson_inf[5]->GetWindowText(Change_bbc);
//	((CComboBox*)GetDlgItem(IDS_COMBOBOX_ACADEMY))->GetWindowText(Change_academy);
//	if (Change_academy == "")
//	{
//		Change_academy = Special_academy;
//	}

	Change_name.Remove(' ');
	Change_author.Remove(' ');
	Change_num.Remove(' ');
	Change_price.Remove(' ');
	Change_isbn.Remove(' ');
	Change_bbc.Remove(' ');
	USES_CONVERSION;
	//	int n_1 = CONTROL.land.returnNumber().GetLength();
	//	int len = WideCharToMultiByte(CP_ACP, 0, CONTROL.land.returnNumber(), CONTROL.land.returnNumber().GetLength(), NULL, 0, NULL, NULL);
	//	temp_2 = new char[len + 1];
	//	WideCharToMultiByte(CP_ACP, 0, CONTROL.land.returnNumber(), n_1, temp_2, len, NULL, NULL);
	//	temp_2[len + 1] = '/0';
	temp_2 = T2A(Special_num);

	if (CheckNumInDB_material(Change_num))          //编号修改
	{
		if (check_number(Change_num))
		{
			//		temp_1 = new char[100];
			//		temp_1 = (LPSTR)(LPCTSTR)Change_name;
			//		temp_2 = (LPSTR)(LPCTSTR)CONTROL.land.returnNumber();
			//		int n = Change_name.GetLength();
			//		int len = WideCharToMultiByte(CP_ACP, 0, Change_name, Change_name.GetLength(), NULL, 0, NULL, NULL);
			//		temp_1 = new char[len + 1];
			//		WideCharToMultiByte(CP_ACP, 0, Change_name, n, temp_1, len, NULL, NULL);
			//		temp_1[len + 1] = '/0';

			temp_1 = T2A(Change_num);
			sprintf_s(sql, "update SYS_MATERIAL set bno = '%s' where bno = '%s'", temp_1, temp_2);
			pRst = dbOper.ExecuteWithResSQL(sql);

			if (pRst == NULL)
			{
				CString alter("修改失败！！");
				MessageBox(alter);
			}
		}
		else
		{
			MessageBox(CString("存在非法字符！"));
		}
	}
	temp_2 = T2A(Change_num);
	if (Change_name != Special_name)		//姓名
	{
		//		temp_1 = (LPSTR)(LPCTSTR)Change_sex;
		//		temp_2 = (LPSTR)(LPCTSTR)CONTROL.land.returnNumber();
		temp_1 = T2A(Change_name);
		sprintf_s(sql, "update SYS_MATERIAL set bname = '%s' where bno = '%s'", temp_1, temp_2);
		pRst = dbOper.ExecuteWithResSQL(sql);

		if (pRst == NULL)
		{
			CString alter("修改失败！！");
			MessageBox(alter);
		}
	}
	if (Change_author != Special_author)			//性别
	{
		//		temp_1 = (LPSTR)(LPCTSTR)Change_tel;
		//		temp_2 = (LPSTR)(LPCTSTR)CONTROL.land.returnNumber();
		temp_1 = T2A(Change_author);
		sprintf_s(sql, "update SYS_MATERIAL set bauthor= '%s' where bno = '%s'", temp_1, temp_2);
		pRst = dbOper.ExecuteWithResSQL(sql);

		if (pRst == NULL)
		{
			CString alter("修改失败！！");
			MessageBox(alter);
		}
	}
	if (Change_price != Special_price)			//电话
	{
		if (check_float(Change_price))
		{
			//		temp_1 = (LPSTR)(LPCTSTR)Change_tel;
			//		temp_2 = (LPSTR)(LPCTSTR)CONTROL.land.returnNumber();
			CString str1("元");
			CString str2("");
			Change_price.Replace(str1, str2);
			//		temp_1 = T2A(Change_price);
			double price_2 = _wtof(Change_price.GetBuffer(0));

			sprintf_s(sql, "update SYS_MATERIAL set bprice= %f where bno = '%s'", price_2, temp_2);
			pRst = dbOper.ExecuteWithResSQL(sql);

			if (pRst == NULL)
			{
				CString alter("修改失败！！");
				MessageBox(alter);
			}
		}
		else
		{
			MessageBox(CString("存在非法字符！"));
		}
	}
	if (Change_isbn != Special_isbn)			//学院
	{
		if (check_isbn(Change_isbn))
		{
			//		temp_1 = (LPSTR)(LPCTSTR)Change_tel;
			//		temp_2 = (LPSTR)(LPCTSTR)CONTROL.land.returnNumber();
			temp_1 = T2A(Change_isbn);
			sprintf_s(sql, "update SYS_MATERIAL set isbn= '%s' where bno = '%s'", temp_1, temp_2);
			pRst = dbOper.ExecuteWithResSQL(sql);

			if (pRst == NULL)
			{
				CString alter("修改失败！！");
				MessageBox(alter);
			}
		}
		else
		{
			MessageBox(CString("存在非法字符！"));
		}
	}
	if (Change_bbc != Special_bbc)			//职责
	{
		if (check_number(Change_bbc))
		{
			//		temp_1 = (LPSTR)(LPCTSTR)Change_tel;
			//		temp_2 = (LPSTR)(LPCTSTR)CONTROL.land.returnNumber();
			temp_1 = T2A(Change_bbc);
			sprintf_s(sql, "update SYS_MATERIAL set bbc= '%s' where bno = '%s'", temp_1, temp_2);
			pRst = dbOper.ExecuteWithResSQL(sql);

			if (pRst == NULL)
			{
				CString alter("修改失败！！");
				MessageBox(alter);
			}
		}
		else
		{
			MessageBox(CString("存在非法字符！"));
		}
	}

	if (pRst != NULL)
	{
		CString alter("修改成功！！");
		MessageBox(alter);
	}


	for (int i = 0; i < 6; i++)
	{
		if (s_changePerson_inf[i])
		{
			s_changePerson_inf[i]->DestroyWindow();
			delete s_changePerson_inf[i];
			s_changePerson_inf[i] = NULL;
		}
	}

//	c_changePerson_inf[0]->DestroyWindow();
//	delete c_changePerson_inf[0];
//	c_changePerson_inf[0] = NULL;

	b_person_information[3]->DestroyWindow();
	delete b_person_information[3];
	b_person_information[3] = NULL;
	b_person_information[4]->DestroyWindow();
	delete b_person_information[4];
	b_person_information[4] = NULL;

	GetDlgItem(IDC_BUTTON7)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON6)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON8)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(true);

	for (int i = 0; i < 12; i++)
	{
		if (s_person_inf[i] && (i % 2 != 0))
		{
			s_person_inf[i]->DestroyWindow();
			delete s_person_inf[i];
			s_person_inf[i] = NULL;
		}
	}

	OnBnClickedButton3();
}


void CDialog_manage::OnClickCancelChange_2()
{

	CString num("");

	for (int i = 0; i < 12; i++)
	{
		if (s_person_inf[i] && (i % 2 != 0))
		{
			s_person_inf[i]->DestroyWindow();
			delete s_person_inf[i];
			s_person_inf[i] = NULL;
		}
	}
	s_changePerson_inf[0]->GetWindowText(num);

	for (int i = 0; i <6; i++)
	{
		if (s_changePerson_inf[i])
		{
			s_changePerson_inf[i]->DestroyWindow();
			delete s_changePerson_inf[i];
			s_changePerson_inf[i] = NULL;
		}
	}

	for (int i = 0; i <3; i++)
	{
		if (c_changePerson_inf[i])
		{
			c_changePerson_inf[i]->DestroyWindow();
			delete c_changePerson_inf[i];
			c_changePerson_inf[i] = NULL;
		}
	}
	if (b_person_information[3])
	{
		b_person_information[3]->DestroyWindow();
		delete b_person_information[3];
		b_person_information[3] = NULL;
	}
	if (b_person_information[5])
	{
		b_person_information[5]->DestroyWindow();
		delete b_person_information[5];
		b_person_information[5] = NULL;
	}
	b_person_information[4]->DestroyWindow();
	delete b_person_information[4];
	b_person_information[4] = NULL;

	GetDlgItem(IDC_BUTTON7)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON6)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON8)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(true);

	GetDlgItem(IDS_BUTTON_ADDMATERIAL)->EnableWindow(true);
	GetDlgItem(IDS_BUTTON_CHANGEMATERIAL_INF)->EnableWindow(true);
	GetDlgItem(IDS_BUTTON_DELETEMATERIAL)->EnableWindow(true);

	CoutTheDetail_material(num);

}

void CDialog_manage::OnClickAddMaterial()
{
	for (int i = 0; i < 12; i++)
	{
		if (s_person_inf[i])
		{
			s_person_inf[i]->DestroyWindow();
			delete s_person_inf[i];
			s_person_inf[i] = NULL;
		}
	}

	GetDlgItem(IDC_BUTTON7)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON6)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON8)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(false);

	GetDlgItem(IDS_BUTTON_ADDMATERIAL)->EnableWindow(false);
	GetDlgItem(IDS_BUTTON_CHANGEMATERIAL_INF)->EnableWindow(false);
	GetDlgItem(IDS_BUTTON_DELETEMATERIAL)->EnableWindow(false);

	GetWindowRect(&rc);
	int p;
	int q;
	int t, b;

	CString NAME("名称:");
	CString AUTHOR("作者:");
	CString PRICE("价格:");
	CString NUM("编号:");
	CString ISBN("ISBN:");
	CString BBC("版次:");

	p = rc.Width()*0.55;
	q = p + 80;
	t = rc.Height()*0.07;
	b = t + 20;
	s_person_inf[1] = NewMyStatic(IDS_STATIC_MANAGE_INF_2, NUM, CRect(p, t, q, b), 0);

	p = rc.Width()*0.55;
	q = p + 80;
	t = rc.Height()*0.12;
	b = t + 20;
	s_person_inf[3] = NewMyStatic(IDS_STATIC_MANAGE_INF_4, NAME, CRect(p, t, q, b), 0);


	p = rc.Width()*0.55;
	q = p + 80;
	t = rc.Height()*0.17;
	b = t + 20;
	s_person_inf[5] = NewMyStatic(IDS_STATIC_MANAGE_INF_6, AUTHOR, CRect(p, t, q, b), 0);


	p = rc.Width()*0.55;
	q = p + 80;
	t = rc.Height()*0.22;
	b = t + 20;
	s_person_inf[7] = NewMyStatic(IDS_STATIC_MANAGE_INF_8, PRICE, CRect(p, t, q, b), 0);


	p = rc.Width()*0.55;
	q = p + 80;
	t = rc.Height()*0.27;
	b = t + 20;
	s_person_inf[9] = NewMyStatic(IDS_STATIC_MANAGE_INF_10, ISBN, CRect(p, t, q, b), 0);


	p = rc.Width()*0.55;
	q = p + 80;
	t = rc.Height()*0.32;
	b = t + 20;
	s_person_inf[11] = NewMyStatic(IDS_STATIC_MANAGE_INF_12, BBC, CRect(p, t, q, b), 0);





	p = rc.Width()*0.85;
	q = p + 70;
	t = rc.Height()*0.73;
	b = t + 40;
	b_person_information[5] = NewMyButton(IDS_BUTTON_SAVEADDMATERIAL, CRect(p, t, q, b), 0);
	p = rc.Width()*0.85;
	q = p + 70;
	t = rc.Height()*0.66;
	b = t + 40;
	b_person_information[4] = NewMyButton(IDS_BUTTON_CANCELCHANGEMATERIAL, CRect(p, t, q, b), 0);

	p = rc.Width()*0.64;
	q = p + 150;
	t = rc.Height()*0.07;
	b = t + 20;
	s_changePerson_inf[0] = NewMyEdit(IDS_EDIT_PERSON_NUM, CRect(p, t, q, b), 0);

	p = rc.Width()*0.64;
	q = p + 150;
	t = rc.Height()*0.12;
	b = t + 20;
	s_changePerson_inf[1] = NewMyEdit(IDS_EDIT_PERSON_NAME, CRect(p, t, q, b), 0);

	p = rc.Width()*0.64;
	q = p + 150;
	t = rc.Height()*0.17;
	b = t + 20;
	s_changePerson_inf[2] = NewMyEdit(IDS_EDIT_PERSON_SEX, CRect(p, t, q, b), 0);

	p = rc.Width()*0.64;
	q = p + 150;
	t = rc.Height()*0.22;
	b = t + 20;
	s_changePerson_inf[3] = NewMyEdit(IDS_EDIT_PERSON_TEL, CRect(p, t, q, b), 0);

	p = rc.Width()*0.64;
	q = p + 150;
	t = rc.Height()*0.27;
	b = t + 20;
	s_changePerson_inf[4] = NewMyEdit(IDS_EDIT_PERSON_ACADEMY, CRect(p, t, q, b), 0);
//	c_changePerson_inf[0] = NewMyComboBox(IDS_COMBOBOX_ACADEMY, CRect(p, t, q, b), 0);
//	((CComboBox*)GetDlgItem(IDS_COMBOBOX_ACADEMY))->AddString(CString("计算机学院"));
//	((CComboBox*)GetDlgItem(IDS_COMBOBOX_ACADEMY))->AddString(CString("数学科学学院"));
//	((CComboBox*)GetDlgItem(IDS_COMBOBOX_ACADEMY))->AddString(CString("经济管理学院"));
//	((CComboBox*)GetDlgItem(IDS_COMBOBOX_ACADEMY))->AddString(CString("化工学院"));

	p = rc.Width()*0.64;
	q = p + 150;
	t = rc.Height()*0.32;
	b = t + 20;
	s_changePerson_inf[5] = NewMyEdit(IDS_EDIT_PERSON_TEACHING, CRect(p, t, q, b), 0);

	s_changePerson_inf[0]->SetWindowTextW(CString(""));
}

void CDialog_manage::OnClickSaveAddMaterial()
{
	USES_CONVERSION;

	CString add_num("");
	CString add_name("");
	CString add_author("");
	CString add_price("");
	CString add_isbn("");
	CString add_bbc("");

	s_changePerson_inf[0]->GetWindowText(add_num);
	s_changePerson_inf[1]->GetWindowText(add_name);
	s_changePerson_inf[2]->GetWindowText(add_author);
	s_changePerson_inf[3]->GetWindowText(add_price);
	s_changePerson_inf[4]->GetWindowText(add_isbn);
	s_changePerson_inf[5]->GetWindowText(add_bbc);
//	((CComboBox*)GetDlgItem(IDS_COMBOBOX_ACADEMY))->GetWindowText(add_academy);


	add_num.Remove(' ');
	add_name.Remove(' ');
	add_author.Remove(' ');
	add_price.Remove(' ');
	add_isbn.Remove(' ');
	add_bbc.Remove(' ');

	if (false == bConn)
	{

		CString alter("数据库连接出错！");
		MessageBox(alter);

		OnClickCancelChange_2();

	}
	if (add_num == "")
	{
		MessageBox(CString("编号不能为空！"));
	}
	if (add_name == "")
	{
		MessageBox(CString("名称不能为空！"));
	}
	if (add_price == "")
	{
		MessageBox(CString("价格不能为空！"));
	}
	if (add_isbn == "")
	{
		MessageBox(CString("ISBN不能为空！"));
	}
	if (!CheckNumInDB_material(add_num))
	{
		MessageBox(CString("该证件号码已经存在"));
	}
	if (add_num != "" && add_name != "" && add_price != "" && add_isbn != "" && CheckNumInDB_material(add_num))
	{
		if (check_number(add_num) && check_float(add_price) && check_isbn(add_isbn) && check_number(add_bbc))
		{
			_RecordsetPtr pRst;
			char sql[255] = { 0 };
			char *temp_num;
			char *temp_name;
			char *temp_author;
			double temp_price;
			char *temp_isbn;
			char *temp_bbc;

			temp_num = T2A(add_num);
			temp_name = T2A(add_name);
			temp_author = T2A(add_author);
			temp_price = _wtof(add_price.GetBuffer(0));
			temp_isbn = T2A(add_isbn);
			temp_bbc = T2A(add_bbc);

			sprintf_s(sql, "insert into SYS_MATERIAL values('%s','%s','%s',%f,'%s','%s')", temp_num, temp_name, temp_author, temp_price, temp_bbc, temp_isbn);
			pRst = dbOper.ExecuteWithResSQL(sql);

			if (pRst == NULL)
			{
				CString alter("添加失败！！");
				MessageBox(alter);
			}

			if (pRst != NULL)
			{
				CString alter("修改成功！！");
				MessageBox(alter);
				int nRow = l_personInf[1]->InsertItem(0, add_num);//插入行
				l_personInf[1]->SetItemText(nRow, 1, add_name);//设置数据
			}
		}
	}
	else
	{
		MessageBox(CString("存在空信息或编号已存在!"));
	}


	OnClickCancelChange_2();

}

void CDialog_manage::OnClickDeleteMaterial()
{
	CString num;
	USES_CONVERSION;
	for (int i = 0; i < l_personInf[1]->GetItemCount(); i++)
	{
		if (l_personInf[1]->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED || l_personInf[1]->GetCheck(i))
		{
			num = l_personInf[1]->GetItemText(i, 0);
			_RecordsetPtr pRst;
			char sql[255] = { 0 };
			char *temp;
			temp = T2A(num);
			sprintf_s(sql, "delete from SYS_MATERIAL where bno = '%s'", temp);
			pRst = dbOper.ExecuteWithResSQL(sql);
			if (pRst == NULL)
			{
				CString alter("删除失败！！");
				MessageBox(alter);
			}

			if (pRst != NULL)
			{
				CString alter("删除成功！！");
				MessageBox(alter);
				l_personInf[1]->DeleteItem(i);
			}
		}
	}
	OnBnClickedButton3();
}

void CDialog_manage::OnBnClickedButton4()
{
	// TODO:  在此添加控件通知处理程序代码
	switchPages();


	////////////////////////

	GetWindowRect(&rc);
	int p;
	int q;
	int t, b;
	p = rc.Width()*0.25;
	q = p + rc.Width()*0.27;;
	t = rc.Height()*0.05;
	b = t + rc.Height()*0.75;
	l_personInf[2] = NewMyListCtrl(IDS_MANAGE_PRESSLIST, CRect(p, t, q, b), 0);
	l_personInf[2]->InsertColumn(0, _T("出版社编号"), LVCFMT_LEFT, 90);
	l_personInf[2]->InsertColumn(1, _T("名称"), LVCFMT_LEFT, 160);



	_RecordsetPtr pRst;
	char sql[255] = { 0 };
	strcpy_s(sql, "select * from SYS_PRESS");
	pRst = dbOper.ExecuteWithResSQL(sql);
	if (NULL == pRst)
	{
		CString alter("查询数据出现错误！");
		MessageBox(alter);
	}
	else if (pRst->adoEOF)
	{
		pRst->Close();

		CString alter("查询数据出现错误！");
		MessageBox(alter);
	}
	else
	{
		pRst->MoveFirst(); //记录集指针移动到查询结果集的前面
		_variant_t vNum, vName;
		while (!pRst->adoEOF)
		{

			vNum = pRst->GetCollect(_variant_t("Pno"));

			vName = pRst->GetCollect(_variant_t("Pname"));

			string pno = (LPCSTR)_bstr_t(vNum);
			string pname = (LPCSTR)_bstr_t(vName);


			CString pno_1;
			CString pname_1;


			pno_1 = pno.c_str();
			pname_1 = pname.c_str();


			pno_1.Remove(' ');
			pname_1.Remove(' ');


			int nRow = l_personInf[2]->InsertItem(0, pno_1);//插入行
			l_personInf[2]->SetItemText(nRow, 1, pname_1);//设置数据

			///////////////////////////////////////////////////列表信息
			pRst->MoveNext();

		}
	}

	p = rc.Width()*0.55;
	q = p + 70;
	t = rc.Height()*0.73;
	b = t + 40;
	b_person_information[0] = NewMyButton(IDS_BUTTON_ADDPRESS, CRect(p, t, q, b), 0);
	p = rc.Width()*0.65;
	q = p + 70;
	t = rc.Height()*0.73;
	b = t + 40;
	b_person_information[1] = NewMyButton(IDS_BUTTON_CHANGEPRESS_INF, CRect(p, t, q, b), 0);
	p = rc.Width()*0.75;
	q = p + 70;
	t = rc.Height()*0.73;
	b = t + 40;
	b_person_information[2] = NewMyButton(IDS_BUTTON_DELETEPRESS, CRect(p, t, q, b), 0);

	GetDlgItem(IDS_BUTTON_CHANGEPRESS_INF)->EnableWindow(false);
	GetDlgItem(IDS_BUTTON_DELETEPRESS)->EnableWindow(false);
}

void CDialog_manage::OnClickInfOfPress(NMHDR* pNMHDR, LRESULT* pResult)
{
	CString str;
	int nId;
	//首先得到点击的位置
	POSITION pos = l_personInf[2]->GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		GetDlgItem(IDS_BUTTON_CHANGEPRESS_INF)->EnableWindow(true);
		GetDlgItem(IDS_BUTTON_DELETEPRESS)->EnableWindow(true);
		//得到行号，通过POSITION转化
		nId = (int)l_personInf[2]->GetNextSelectedItem(pos);
		//得到列中的内容（0表示第一列，同理1,2,3...表示第二，三，四...列）
		str = l_personInf[2]->GetItemText(nId, 0);
		CoutTheDetail_press(str);
	}
	else
	{
		GetDlgItem(IDS_BUTTON_CHANGEPRESS_INF)->EnableWindow(false);
		GetDlgItem(IDS_BUTTON_DELETEPRESS)->EnableWindow(false);

	}
}


void CDialog_manage::CoutTheDetail_press(CString num)
{
	for (int i = 0; i < 12; i++)
	{
		if (s_person_inf[i])
		{
			s_person_inf[i]->DestroyWindow();
			delete s_person_inf[i];
			s_person_inf[i] = NULL;
		}
	}

	CString NAME("名称:");
	CString NUM("编号:");
	CString ADDRESS("地址:");
	CString TEL("联系方式:");

	_RecordsetPtr pRst;
	char sql[255] = { 0 };
	USES_CONVERSION;
	char *temp;
	temp = T2A(num);
	sprintf_s(sql, "select * from SYS_PRESS WHERE PNO = '%s'", temp);
	pRst = dbOper.ExecuteWithResSQL(sql);
	if (NULL == pRst)
	{
		CString alter("查询数据出现错误！");
		MessageBox(alter);
	}
	else if (pRst->adoEOF)
	{
		pRst->Close();

		//CString alter("未查询到结果！");
		//MessageBox(alter);
	}
	else
	{
		pRst->MoveFirst(); //记录集指针移动到查询结果集的前面
		_variant_t vNum, vName, vAddress, vTel;
		GetWindowRect(&rc);
		int p;
		int q;
		int t, b;
		while (!pRst->adoEOF)
		{

			vNum = pRst->GetCollect(_variant_t("pno"));

			vName = pRst->GetCollect(_variant_t("pname"));

			vAddress = pRst->GetCollect(_variant_t("address"));

			vTel = pRst->GetCollect(_variant_t("tel"));

			string pno = (LPCSTR)_bstr_t(vNum);
			string pname = (LPCSTR)_bstr_t(vName);
			string address = (LPCSTR)_bstr_t(vAddress);
			string tel = (LPCSTR)_bstr_t(vTel);

			CString pno_1;
			CString pname_1;
			CString address_1;
			CString tel_1;

			pno_1 = pno.c_str();
			pname_1 = pname.c_str();
			address_1 = address.c_str();
			tel_1 = tel.c_str();

			pno_1.Remove(' ');
			pname_1.Remove(' ');
			address_1.Remove(' ');
			tel_1.Remove(' ');


			p = rc.Width()*0.64;
			q = p + 150;
			t = rc.Height()*0.07;
			b = t + 20;
			s_person_inf[0] = NewMyStatic(IDS_STATIC_MANAGE_INF_1, pno_1, CRect(p, t, q, b), 0);
			p = rc.Width()*0.55;
			q = p + 80;
			t = rc.Height()*0.07;
			b = t + 20;
			s_person_inf[1] = NewMyStatic(IDS_STATIC_MANAGE_INF_2, NUM, CRect(p, t, q, b), 0);

			p = rc.Width()*0.64;
			q = p + 250;
			t = rc.Height()*0.12;
			b = t + 20;
			s_person_inf[2] = NewMyStatic(IDS_STATIC_MANAGE_INF_3, pname_1, CRect(p, t, q, b), 0);
			p = rc.Width()*0.55;
			q = p + 80;
			t = rc.Height()*0.12;
			b = t + 20;
			s_person_inf[3] = NewMyStatic(IDS_STATIC_MANAGE_INF_4, NAME, CRect(p, t, q, b), 0);

			p = rc.Width()*0.64;
			q = p + 150;
			t = rc.Height()*0.17;
			b = t + 60;
			s_person_inf[4] = NewMyStatic(IDS_STATIC_MANAGE_INF_5, address_1, CRect(p, t, q, b), 0);
			p = rc.Width()*0.55;
			q = p + 80;
			t = rc.Height()*0.17;
			b = t + 20;
			s_person_inf[5] = NewMyStatic(IDS_STATIC_MANAGE_INF_6, ADDRESS, CRect(p, t, q, b), 0);

			p = rc.Width()*0.64;
			q = p + 150;
			t = rc.Height()*0.27;
			b = t + 20;
			s_person_inf[6] = NewMyStatic(IDS_STATIC_MANAGE_INF_7, tel_1, CRect(p, t, q, b), 0);
			p = rc.Width()*0.55;
			q = p + 80;
			t = rc.Height()*0.27;
			b = t + 20;
			s_person_inf[7] = NewMyStatic(IDS_STATIC_MANAGE_INF_8, TEL, CRect(p, t, q, b), 0);


			pRst->MoveNext();

		}
	}
}

void CDialog_manage::OnClickChangePress()
{

	CString num;
	CString name;
	CString address;
	CString tel;

	s_person_inf[0]->GetWindowText(num);
	s_person_inf[2]->GetWindowText(name);
	s_person_inf[4]->GetWindowText(address);
	s_person_inf[6]->GetWindowText(tel);

	Special_num = num;
	Special_name = name;
	Special_address = address;
	Special_tel = tel;

	for (int i = 0; i < 12; i++)
	{
		if (s_person_inf[i] && (i % 2 == 0))
		{
			s_person_inf[i]->DestroyWindow();
			delete s_person_inf[i];
			s_person_inf[i] = NULL;
		}
	}

	GetDlgItem(IDC_BUTTON7)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON6)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON8)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(false);

	GetDlgItem(IDS_BUTTON_ADDPRESS)->EnableWindow(false);
	GetDlgItem(IDS_BUTTON_CHANGEPRESS_INF)->EnableWindow(false);
	GetDlgItem(IDS_BUTTON_DELETEPRESS)->EnableWindow(false);

	GetWindowRect(&rc);
	int p;
	int q;
	int t, b;

	p = rc.Width()*0.85;
	q = p + 70;
	t = rc.Height()*0.73;
	b = t + 40;
	b_person_information[3] = NewMyButton(IDS_BUTTON_SAVEPRESSCHANGE, CRect(p, t, q, b), 0);
	p = rc.Width()*0.85;
	q = p + 70;
	t = rc.Height()*0.66;
	b = t + 40;
	b_person_information[4] = NewMyButton(IDS_BUTTON_CANCELCHANGE, CRect(p, t, q, b), 0);

	p = rc.Width()*0.64;
	q = p + 150;
	t = rc.Height()*0.07;
	b = t + 20;
	s_changePerson_inf[0] = NewMyEdit(IDS_EDIT_PERSON_NUM, CRect(p, t, q, b), 0);

	p = rc.Width()*0.64;
	q = p + 150;
	t = rc.Height()*0.12;
	b = t + 20;
	s_changePerson_inf[1] = NewMyEdit(IDS_EDIT_PERSON_NAME, CRect(p, t, q, b), 0);

	p = rc.Width()*0.64;
	q = p + 150;
	t = rc.Height()*0.17;
	b = t + 20;
	s_changePerson_inf[2] = NewMyEdit(IDS_EDIT_PERSON_SEX, CRect(p, t, q, b), 0);

	p = rc.Width()*0.64;
	q = p + 150;
	t = rc.Height()*0.27;
	b = t + 20;
	s_changePerson_inf[3] = NewMyEdit(IDS_EDIT_PERSON_TEL, CRect(p, t, q, b), 0);



	s_changePerson_inf[0]->SetWindowText(num);
	s_changePerson_inf[1]->SetWindowText(name);
	s_changePerson_inf[2]->SetWindowText(address);
	s_changePerson_inf[3]->SetWindowText(tel);


}

bool CDialog_manage::CheckNumInDB_press(CString num)
{
	if (false == bConn)
	{

		CString alter("数据库连接出错！");
		MessageBox(alter);

		OnClickCancelChange_3();

	}
	_RecordsetPtr pRst;
	char sql[255] = { 0 };
	char *temp_1;

	USES_CONVERSION;
	temp_1 = T2A(num);
	sprintf_s(sql, "select * from SYS_PRESS  where pno = '%s'", temp_1);

	pRst = dbOper.ExecuteWithResSQL(sql);

	if (pRst == NULL)
	{
		CString alter("查询失败！！");
		MessageBox(alter);
		return false;
	}
	if (pRst->adoEOF)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void CDialog_manage::OnClickSavePressChange()
{
	if (false == bConn)
	{

		CString alter("数据库连接出错！");
		MessageBox(alter);

		OnClickCancelChange_3();

	}
	_RecordsetPtr pRst;
	char sql[255] = { 0 };
	char *temp_1;
	char *temp_2;



	s_changePerson_inf[0]->GetWindowText(Change_num);
	s_changePerson_inf[1]->GetWindowText(Change_name);
	s_changePerson_inf[2]->GetWindowText(Change_address);
	s_changePerson_inf[3]->GetWindowText(Change_tel);
	//	((CComboBox*)GetDlgItem(IDS_COMBOBOX_ACADEMY))->GetWindowText(Change_academy);
	//	if (Change_academy == "")
	//	{
	//		Change_academy = Special_academy;
	//	}

	Change_name.Remove(' ');
	Change_author.Remove(' ');
	Change_num.Remove(' ');
	Change_price.Remove(' ');
	USES_CONVERSION;
	//	int n_1 = CONTROL.land.returnNumber().GetLength();
	//	int len = WideCharToMultiByte(CP_ACP, 0, CONTROL.land.returnNumber(), CONTROL.land.returnNumber().GetLength(), NULL, 0, NULL, NULL);
	//	temp_2 = new char[len + 1];
	//	WideCharToMultiByte(CP_ACP, 0, CONTROL.land.returnNumber(), n_1, temp_2, len, NULL, NULL);
	//	temp_2[len + 1] = '/0';
	temp_2 = T2A(Special_num);

	if (CheckNumInDB_press(Change_num))          //编号修改
	{
		if (check_number(Change_num))
		{
			//		temp_1 = new char[100];
			//		temp_1 = (LPSTR)(LPCTSTR)Change_name;
			//		temp_2 = (LPSTR)(LPCTSTR)CONTROL.land.returnNumber();
			//		int n = Change_name.GetLength();
			//		int len = WideCharToMultiByte(CP_ACP, 0, Change_name, Change_name.GetLength(), NULL, 0, NULL, NULL);
			//		temp_1 = new char[len + 1];
			//		WideCharToMultiByte(CP_ACP, 0, Change_name, n, temp_1, len, NULL, NULL);
			//		temp_1[len + 1] = '/0';

			temp_1 = T2A(Change_num);
			sprintf_s(sql, "update SYS_PRESS set pno = '%s' where pno = '%s'", temp_1, temp_2);
			pRst = dbOper.ExecuteWithResSQL(sql);

			if (pRst == NULL)
			{
				CString alter("修改失败！！");
				MessageBox(alter);
			}
		}
		else
		{
			MessageBox(CString("存在违法信息!"));
		}
	}
	temp_2 = T2A(Change_num);
	if (Change_name != Special_name)		//姓名
	{
		//		temp_1 = (LPSTR)(LPCTSTR)Change_sex;
		//		temp_2 = (LPSTR)(LPCTSTR)CONTROL.land.returnNumber();
		temp_1 = T2A(Change_name);
		sprintf_s(sql, "update SYS_PRESS set pname = '%s' where pno = '%s'", temp_1, temp_2);
		pRst = dbOper.ExecuteWithResSQL(sql);

		if (pRst == NULL)
		{
			CString alter("修改失败！！");
			MessageBox(alter);
		}
	}
	if (Change_address != Special_address)			//性别
	{
		//		temp_1 = (LPSTR)(LPCTSTR)Change_tel;
		//		temp_2 = (LPSTR)(LPCTSTR)CONTROL.land.returnNumber();
		temp_1 = T2A(Change_address);
		sprintf_s(sql, "update SYS_PRESS set address= '%s' where pno = '%s'", temp_1, temp_2);
		pRst = dbOper.ExecuteWithResSQL(sql);

		if (pRst == NULL)
		{
			CString alter("修改失败！！");
			MessageBox(alter);
		}
	}
	if (Change_tel != Special_tel)			//学院
	{
		if (check_number(Change_tel))
		{
			//		temp_1 = (LPSTR)(LPCTSTR)Change_tel;
			//		temp_2 = (LPSTR)(LPCTSTR)CONTROL.land.returnNumber();
			temp_1 = T2A(Change_tel);
			sprintf_s(sql, "update SYS_PRESS set tel= '%s' where pno = '%s'", temp_1, temp_2);
			pRst = dbOper.ExecuteWithResSQL(sql);

			if (pRst == NULL)
			{
				CString alter("修改失败！！");
				MessageBox(alter);
			}
		}
		else
		{
			MessageBox(CString("存在违法字符！"));
		}
	}


	if (pRst != NULL)
	{
		CString alter("修改成功！！");
		MessageBox(alter);
	}


	for (int i = 0; i < 6; i++)
	{
		if (s_changePerson_inf[i])
		{
			s_changePerson_inf[i]->DestroyWindow();
			delete s_changePerson_inf[i];
			s_changePerson_inf[i] = NULL;
		}
	}

	//	c_changePerson_inf[0]->DestroyWindow();
	//	delete c_changePerson_inf[0];
	//	c_changePerson_inf[0] = NULL;

	b_person_information[3]->DestroyWindow();
	delete b_person_information[3];
	b_person_information[3] = NULL;
	b_person_information[4]->DestroyWindow();
	delete b_person_information[4];
	b_person_information[4] = NULL;

	GetDlgItem(IDC_BUTTON7)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON6)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON8)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(true);

	for (int i = 0; i < 12; i++)
	{
		if (s_person_inf[i] && (i % 2 != 0))
		{
			s_person_inf[i]->DestroyWindow();
			delete s_person_inf[i];
			s_person_inf[i] = NULL;
		}
	}
	OnBnClickedButton4();
}


void CDialog_manage::OnClickCancelChange_3()
{

	CString num("");

	for (int i = 0; i < 12; i++)
	{
		if (s_person_inf[i] && (i % 2 != 0))
		{
			s_person_inf[i]->DestroyWindow();
			delete s_person_inf[i];
			s_person_inf[i] = NULL;
		}
	}

	s_changePerson_inf[0]->GetWindowText(num);

	for (int i = 0; i <6; i++)
	{
		if (s_changePerson_inf[i])
		{
			s_changePerson_inf[i]->DestroyWindow();
			delete s_changePerson_inf[i];
			s_changePerson_inf[i] = NULL;
		}
	}

	for (int i = 0; i <3; i++)
	{
		if (c_changePerson_inf[i])
		{
			c_changePerson_inf[i]->DestroyWindow();
			delete c_changePerson_inf[i];
			c_changePerson_inf[i] = NULL;
		}
	}
	if (b_person_information[3])
	{
		b_person_information[3]->DestroyWindow();
		delete b_person_information[3];
		b_person_information[3] = NULL;
	}
	if (b_person_information[5])
	{
		b_person_information[5]->DestroyWindow();
		delete b_person_information[5];
		b_person_information[5] = NULL;
	}
	b_person_information[4]->DestroyWindow();
	delete b_person_information[4];
	b_person_information[4] = NULL;

	GetDlgItem(IDC_BUTTON7)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON6)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON8)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(true);

	GetDlgItem(IDS_BUTTON_ADDPRESS)->EnableWindow(true);
	GetDlgItem(IDS_BUTTON_CHANGEPRESS_INF)->EnableWindow(true);
	GetDlgItem(IDS_BUTTON_DELETEPRESS)->EnableWindow(true);

	CoutTheDetail_press(num);

}

void CDialog_manage::OnClickAddPress()
{
	for (int i = 0; i < 12; i++)
	{
		if (s_person_inf[i])
		{
			s_person_inf[i]->DestroyWindow();
			delete s_person_inf[i];
			s_person_inf[i] = NULL;
		}
	}

	GetDlgItem(IDC_BUTTON7)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON6)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON8)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(false);

	GetDlgItem(IDS_BUTTON_ADDPRESS)->EnableWindow(false);
	GetDlgItem(IDS_BUTTON_CHANGEPRESS_INF)->EnableWindow(false);
	GetDlgItem(IDS_BUTTON_DELETEPRESS)->EnableWindow(false);

	GetWindowRect(&rc);
	int p;
	int q;
	int t, b;

	CString NAME("名称:");
	CString ADDRESS("地址:");
	CString TEL("联系电话:");
	CString NUM("编号:");

	p = rc.Width()*0.55;
	q = p + 80;
	t = rc.Height()*0.07;
	b = t + 20;
	s_person_inf[1] = NewMyStatic(IDS_STATIC_MANAGE_INF_2, NUM, CRect(p, t, q, b), 0);

	p = rc.Width()*0.55;
	q = p + 80;
	t = rc.Height()*0.12;
	b = t + 20;
	s_person_inf[3] = NewMyStatic(IDS_STATIC_MANAGE_INF_4, NAME, CRect(p, t, q, b), 0);


	p = rc.Width()*0.55;
	q = p + 80;
	t = rc.Height()*0.17;
	b = t + 20;
	s_person_inf[5] = NewMyStatic(IDS_STATIC_MANAGE_INF_6, ADDRESS, CRect(p, t, q, b), 0);


	p = rc.Width()*0.55;
	q = p + 80;
	t = rc.Height()*0.22;
	b = t + 20;
	s_person_inf[7] = NewMyStatic(IDS_STATIC_MANAGE_INF_8, TEL, CRect(p, t, q, b), 0);


	p = rc.Width()*0.85;
	q = p + 70;
	t = rc.Height()*0.73;
	b = t + 40;
	b_person_information[5] = NewMyButton(IDS_BUTTON_SAVEADDPRESS, CRect(p, t, q, b), 0);
	p = rc.Width()*0.85;
	q = p + 70;
	t = rc.Height()*0.66;
	b = t + 40;
	b_person_information[4] = NewMyButton(IDS_BUTTON_CANCELCHANGE, CRect(p, t, q, b), 0);

	p = rc.Width()*0.64;
	q = p + 150;
	t = rc.Height()*0.07;
	b = t + 20;
	s_changePerson_inf[0] = NewMyEdit(IDS_EDIT_PERSON_NUM, CRect(p, t, q, b), 0);

	p = rc.Width()*0.64;
	q = p + 150;
	t = rc.Height()*0.12;
	b = t + 20;
	s_changePerson_inf[1] = NewMyEdit(IDS_EDIT_PERSON_NAME, CRect(p, t, q, b), 0);

	p = rc.Width()*0.64;
	q = p + 150;
	t = rc.Height()*0.17;
	b = t + 20;
	s_changePerson_inf[2] = NewMyEdit(IDS_EDIT_PERSON_SEX, CRect(p, t, q, b), 0);

	p = rc.Width()*0.64;
	q = p + 150;
	t = rc.Height()*0.22;
	b = t + 20;
	s_changePerson_inf[3] = NewMyEdit(IDS_EDIT_PERSON_TEL, CRect(p, t, q, b), 0);


	s_changePerson_inf[0]->SetWindowTextW(CString(""));
}


void CDialog_manage::OnClickSaveAddPress()
{
	USES_CONVERSION;

	CString add_num("");
	CString add_name("");
	CString add_address("");
	CString add_tel("");

	s_changePerson_inf[0]->GetWindowText(add_num);
	s_changePerson_inf[1]->GetWindowText(add_name);
	s_changePerson_inf[2]->GetWindowText(add_address);
	s_changePerson_inf[3]->GetWindowText(add_tel);
	//	((CComboBox*)GetDlgItem(IDS_COMBOBOX_ACADEMY))->GetWindowText(add_academy);


	add_num.Remove(' ');
	add_name.Remove(' ');
	add_address.Remove(' ');
	add_tel.Remove(' ');

	if (false == bConn)
	{

		CString alter("数据库连接出错！");
		MessageBox(alter);

		OnClickCancelChange_3();

	}
	if (add_num == "")
	{
		MessageBox(CString("编号不能为空！"));
	}
	if (add_name == "")
	{
		MessageBox(CString("名称不能为空！"));
	}
	if (!CheckNumInDB_press(add_num))
	{
		MessageBox(CString("该证件号码已经存在"));
	}
	if (add_num != "" && add_name != ""  && CheckNumInDB_press(add_num))
	{
		if (check_number(add_num) && check_number(add_tel))
		{
			_RecordsetPtr pRst;
			char sql[255] = { 0 };
			char *temp_num;
			char *temp_name;
			char *temp_address;
			char *temp_tel;

			temp_num = T2A(add_num);
			temp_name = T2A(add_name);
			temp_address = T2A(add_address);
			temp_tel = T2A(add_tel);

			sprintf_s(sql, "insert into SYS_PRESS values('%s','%s','%s','%s')", temp_num, temp_name, temp_address, temp_tel);
			pRst = dbOper.ExecuteWithResSQL(sql);

			if (pRst == NULL)
			{
				CString alter("添加失败！！");
				MessageBox(alter);
			}

			if (pRst != NULL)
			{
				CString alter("修改成功！！");
				MessageBox(alter);
				int nRow = l_personInf[2]->InsertItem(0, add_num);//插入行
				l_personInf[2]->SetItemText(nRow, 1, add_name);//设置数据
			}
		}
	}
	else
	{
		MessageBox(CString("存在空信息或者编号已存在！"));
	}


	OnClickCancelChange_3();

}


void CDialog_manage::OnClickDeletePress()
{
	CString num;
	USES_CONVERSION;
	for (int i = 0; i < l_personInf[2]->GetItemCount(); i++)
	{
		if (l_personInf[2]->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED || l_personInf[2]->GetCheck(i))
		{
			num = l_personInf[2]->GetItemText(i, 0);
			_RecordsetPtr pRst;
			char sql[255] = { 0 };
			char *temp;
			temp = T2A(num);
			sprintf_s(sql, "delete from SYS_PRESS where pno = '%s'", temp);
			pRst = dbOper.ExecuteWithResSQL(sql);
			if (pRst == NULL)
			{
				CString alter("删除失败！！");
				MessageBox(alter);
			}

			if (pRst != NULL)
			{
				CString alter("删除成功！！");
				MessageBox(alter);
				l_personInf[2]->DeleteItem(i);
			}
		}
	}
	OnBnClickedButton4();
}


void CDialog_manage::OnBnClickedButton6()
{
	// TODO:  在此添加控件通知处理程序代码
	switchPages();


	//////////////////////////////

	GetWindowRect(&rc);
	int p;
	int q;
	int t, b;
	USES_CONVERSION;
	p = rc.Width()*0.25;
	q = p + rc.Width()*0.3;
	t = rc.Height()*0.07;
	b = t + rc.Height()*0.6;
	l_maillist[0] = NewMyListCtrl(IDS_LISTCTRL_NOTICELIST, CRect(p, t, q, b), 0);
	l_maillist[0]->InsertColumn(0, _T("公告编号"), LVCFMT_LEFT, (rc.Width()*0.3)*0.25);
	l_maillist[0]->InsertColumn(1, _T("发布人"), LVCFMT_LEFT, (rc.Width()*0.3)*0.25);
	l_maillist[0]->InsertColumn(2, _T("发布时间"), LVCFMT_LEFT, (rc.Width()*0.3)*0.25);
	l_maillist[0]->InsertColumn(3, _T("标题"), LVCFMT_LEFT, (rc.Width()*0.3)*0.25);
	l_maillist[0]->InsertColumn(4, _T("状态"), LVCFMT_LEFT, (rc.Width()*0.3)*0.25);

	_RecordsetPtr pRst;
	char sql[255] = { 0 };
	char *temp;
	temp = T2A(CONTROL.land.returnNumber());
	sprintf_s(sql, "select * from SYS_NOTICE where sno = '%s'", temp);
	pRst = dbOper.ExecuteWithResSQL(sql);
	if (NULL == pRst)
	{
		CString alter("查询数据出现错误！");
		MessageBox(alter);
	}
	//	else if (pRst->adoEOF)
	//	{
	//		pRst->Close();
	//
	//		CString alter("查询数据出现错误！");
	//		MessageBox(alter);
	//	}
	else if (!pRst->adoEOF)
	{
		pRst->MoveFirst(); //记录集指针移动到查询结果集的前面
		_variant_t vNum, vSno, vDate,vTitle,vStatus;
		while (!pRst->adoEOF)
		{
			vNum = pRst->GetCollect(_variant_t("num"));

			vSno = pRst->GetCollect(_variant_t("sno"));

			vDate = pRst->GetCollect(_variant_t("begindate"));

			vTitle = pRst->GetCollect(_variant_t("title"));

			vStatus = pRst->GetCollect(_variant_t("status"));

			string num = (LPCSTR)_bstr_t(vNum);
			string sno = (LPCSTR)_bstr_t(vSno);
			string date = (LPCSTR)_bstr_t(vDate);
			string title = (LPCSTR)_bstr_t(vTitle);
			string status = (LPCSTR)_bstr_t(vStatus);

			CString num_1;
			CString sno_1;
			CString date_1;
			CString title_1;
			CString status_1;
			num_1 = num.c_str();
			sno_1 = sno.c_str();
			date_1 = date.c_str();
			title_1 = title.c_str();
			status_1 = status.c_str();
			num_1.Remove(' ');
			sno_1.Remove(' ');
			date_1.Remove(' ');
			title_1.Remove(' ');
			status_1.Remove(' ');

			if (status_1 == "1")
			{
				status_1 = "未发布";
			}
			else if (status_1 == "2")
			{
				status_1 = "已发布";
			}

			int nRow = l_maillist[0]->InsertItem(0, num_1);//插入行
			l_maillist[0]->SetItemText(nRow, 1, sno_1);//设置数据
			l_maillist[0]->SetItemText(nRow, 2, date_1);
			l_maillist[0]->SetItemText(nRow, 3, title_1);
			l_maillist[0]->SetItemText(nRow, 4, status_1);

			pRst->MoveNext();

		}
	}

	p = rc.Width()*0.25;
	q = p + rc.Width()*0.09;
	t = rc.Height()*0.69;
	b = t + rc.Height()*0.08;
	b_notice[0] = NewMyButton(IDS_BUTTON_ADDNOTICE, CRect(p, t, q, b), 0);
	p = rc.Width()*0.35;
	q = p + rc.Width()*0.09;
	t = rc.Height()*0.69;
	b = t + rc.Height()*0.08;
	b_notice[1] = NewMyButton(IDS_BUTTON_DELETENOTICE, CRect(p, t, q, b), 0);
	p = rc.Width()*0.45;
	q = p + rc.Width()*0.09;
	t = rc.Height()*0.69;
	b = t + rc.Height()*0.08;
	b_notice[2] = NewMyButton(IDS_BUTTON_PUBLISHNOTICE, CRect(p, t, q, b), 0);
	p = rc.Width()*0.55;
	q = p + rc.Width()*0.09;
	t = rc.Height()*0.69;
	b = t + rc.Height()*0.08;
	b_notice[3] = NewMyButton(IDS_BUTTON_TAKENOTICE, CRect(p, t, q, b), 0);

}

void CDialog_manage::OnClickInfOfNotice(NMHDR* pNMHDR, LRESULT* pResult)
{
	CString str;
	int nId;
	//首先得到点击的位置
	POSITION pos = l_maillist[0]->GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		//		GetDlgItem(IDS_BUTTON_CHANGEMATERIAL_INF)->EnableWindow(true);
		//		GetDlgItem(IDS_BUTTON_DELETEMATERIAL)->EnableWindow(true);
		//得到行号，通过POSITION转化
		nId = (int)l_maillist[0]->GetNextSelectedItem(pos);
		//得到列中的内容（0表示第一列，同理1,2,3...表示第二，三，四...列）
		str = l_maillist[0]->GetItemText(nId, 0);
		//		memory_1 = l_maillist[0]->GetItemText(nId, 0);
		memory = l_maillist[0]->GetItemText(nId, 4);
		CoutTheDetail_notice(str);
	}
	else
	{
		//		GetDlgItem(IDS_BUTTON_CHANGEMATERIAL_INF)->EnableWindow(false);
		//		GetDlgItem(IDS_BUTTON_DELETEMATERIAL)->EnableWindow(false);

	}
}

void CDialog_manage::CoutTheDetail_notice(CString num)
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

	CString TITLE("公告标题:");
	CString CONTENT("公告内容:");

	_RecordsetPtr pRst;
	char sql[255] = { 0 };
	USES_CONVERSION;
	char *temp;
	temp = T2A(num);
	sprintf_s(sql, "select * from SYS_NOTICE WHERE num = '%s'", temp);
	pRst = dbOper.ExecuteWithResSQL(sql);
	if (NULL == pRst)
	{
		CString alter("查询数据出现错误！");
		MessageBox(alter);
	}
	else if (pRst->adoEOF)
	{
		pRst->Close();

		//CString alter("未查询到结果！");
		//MessageBox(alter);
	}
	else
	{
		pRst->MoveFirst(); //记录集指针移动到查询结果集的前面
		_variant_t vTitle, vContent;
		GetWindowRect(&rc);
		int p;
		int q;
		int t, b;
		while (!pRst->adoEOF)
		{

			vTitle = pRst->GetCollect(_variant_t("title"));

			vContent = pRst->GetCollect(_variant_t("content"));


			string title = (LPCSTR)_bstr_t(vTitle);
			string content = (LPCSTR)_bstr_t(vContent);

			CString title_1;;
			CString content_1;

			title_1 = title.c_str();
			content_1 = content.c_str();

			title_1.Remove(' ');
			content_1.Remove(' ');

			p = rc.Width()*0.66;
			q = p + 150;
			t = rc.Height()*0.07;
			b = t + 20;
			s_mail[0] = NewMyStatic(IDS_STATIC_MANAGE_INF_1, title_1, CRect(p, t, q, b), 0);
			p = rc.Width()*0.56;
			q = p + 90;
			t = rc.Height()*0.07;
			b = t + 20;
			s_mail[1] = NewMyStatic(IDS_STATIC_MANAGE_INF_2, TITLE, CRect(p, t, q, b), 0);

			p = rc.Width()*0.66;
			q = p + 200;
			t = rc.Height()*0.14;
			b = t + 100;
			s_mail[4] = NewMyStatic(IDS_STATIC_MANAGE_INF_5, content_1, CRect(p, t, q, b), 0);
			p = rc.Width()*0.56;
			q = p + 80;
			t = rc.Height()*0.14;
			b = t + 20;
			s_mail[5] = NewMyStatic(IDS_STATIC_MANAGE_INF_6, CONTENT, CRect(p, t, q, b), 0);


			pRst->MoveNext();

		}
	}
}

void CDialog_manage::OnClickDelete_notice()
{
	CString num;
	USES_CONVERSION;
	char *temp;
	for (int i = 0; i < l_maillist[0]->GetItemCount(); i++)
	{
		if (l_maillist[0]->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED || l_maillist[0]->GetCheck(i))
		{
			num = l_maillist[0]->GetItemText(i, 2);
			if (memory == "未发布")
			{
				_RecordsetPtr pRst;
				char sql[255] = { 0 };
				CString number;
				number = l_maillist[0]->GetItemText(i, 0);
				temp = T2A(number);
				sprintf_s(sql, "delete from SYS_NOTICE where num = '%s'", temp);
				pRst = dbOper.ExecuteWithResSQL(sql);
				if (pRst == NULL)
				{
					MessageBox(CString("删除失败"));
				}
				else
				{
					MessageBox(CString("删除成功"));
				}

			}
			else
			{
				MessageBox(CString("请先撤下该公告！"));
			}
		}

	}
	OnBnClickedButton6();
}


void CDialog_manage::OnClickAddNotice()
{
	CDialog_notice a;
	a.DoModal();
	OnBnClickedButton6();
}

void CDialog_manage::OnClickPublishNotice()
{
	USES_CONVERSION;
	char *temp;
	_RecordsetPtr pRst;
	char sql[255] = { 0 };
	for (int i = 0; i < l_maillist[0]->GetItemCount(); i++)
	{
		if (l_maillist[0]->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED || l_maillist[0]->GetCheck(i))
		{
			strcpy_s(sql,"update SYS_NOTICE set status = '1' where status = '2'");
			pRst = dbOper.ExecuteWithResSQL(sql);
			if (pRst == NULL)
			{
				MessageBox(CString("数据库通信出错！"));
			}
			else
			{

				if (memory == "未发布")
				{

					CString number;
					number = l_maillist[0]->GetItemText(i, 0);
					temp = T2A(number);
					sprintf_s(sql, "update SYS_NOTICE set status = '2' where num = '%s'", temp);
					pRst = dbOper.ExecuteWithResSQL(sql);
					if (pRst == NULL)
					{
						MessageBox(CString("数据库通信出错"));
					}
					else
					{
						MessageBox(CString("发布成功！"));
						UpdateData(false);
					}

				}
				else
				{
					MessageBox(CString("该公告已经发布！"));
				}
			}
		}

	}
	OnBnClickedButton6();
}


void CDialog_manage::OnClickBackNotice()
{
	USES_CONVERSION;
	char *temp;
	_RecordsetPtr pRst;
	char sql[255] = { 0 };
	for (int i = 0; i < l_maillist[0]->GetItemCount(); i++)
	{
		if (l_maillist[0]->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED || l_maillist[0]->GetCheck(i))
		{

			if (memory == "已发布")
			{

				CString number;
				number = l_maillist[0]->GetItemText(i, 0);
				temp = T2A(number);
				sprintf_s(sql, "update SYS_NOTICE set status = '1' where num = '%s'", temp);
				pRst = dbOper.ExecuteWithResSQL(sql);
				if (pRst == NULL)
				{
					MessageBox(CString("数据库通信出错"));
				}
				else
				{
					MessageBox(CString("撤销成功！"));
					UpdateData(false);
				}

			}
			else
			{
				MessageBox(CString("该公告没有发布哦！"));
			}
			
		}

	}
	OnBnClickedButton6();
}


void CDialog_manage::OnBnClickedButton8()
{
	// TODO:  在此添加控件通知处理程序代码
	switchPages();

	///////////////////////

	GetWindowRect(&rc);
	int p;
	int q;
	int t, b;
	USES_CONVERSION;
	p = rc.Width()*0.24;
	q = p + rc.Width()*0.3;
	t = rc.Height()*0.07;
	b = t + rc.Height()*0.6;
	l_maillist[0] = NewMyListCtrl(IDS_LISTCTRL_USER_MAINLIST, CRect(p, t, q, b), 0);
	l_maillist[0]->InsertColumn(0, _T("信息编号"), LVCFMT_LEFT, (rc.Width()*0.3)*0.33);
	l_maillist[0]->InsertColumn(1, _T("发信人"), LVCFMT_LEFT, (rc.Width()*0.3)*0.33);
	l_maillist[0]->InsertColumn(2, _T("是否已读"), LVCFMT_LEFT, (rc.Width()*0.3)*0.33);

	_RecordsetPtr pRst;
	char sql[255] = { 0 };
	char *temp;
	temp = T2A(CONTROL.land.returnNumber());
	sprintf_s(sql, "select * from SYS_MAIL where receiver = '%s'", temp);
	pRst = dbOper.ExecuteWithResSQL(sql);
	if (NULL == pRst)
	{
		CString alter("查询数据出现错误！");
		MessageBox(alter);
	}
	//	else if (pRst->adoEOF)
	//	{
	//		pRst->Close();
	//
	//		CString alter("查询数据出现错误！");
	//		MessageBox(alter);
	//	}
	else if (!pRst->adoEOF)
	{
		pRst->MoveFirst(); //记录集指针移动到查询结果集的前面
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
				ifread_1 = "未查看";
			else if (ifread_1 == "2")
				ifread_1 = "已查看";

			int nRow = l_maillist[0]->InsertItem(0, mno_1);//插入行
			l_maillist[0]->SetItemText(nRow, 1, name_1);//设置数据
			l_maillist[0]->SetItemText(nRow, 2, ifread_1);

			pRst->MoveNext();

		}
	}

	p = rc.Width()*0.24;
	q = p + rc.Width()*0.09;
	t = rc.Height()*0.69;
	b = t + rc.Height()*0.08;
	b_mail[0] = NewMyButton(IDS_BUTTON_SENDMAIL_USER, CRect(p, t, q, b), 0);
	p = rc.Width()*0.35;
	q = p + rc.Width()*0.09;
	t = rc.Height()*0.69;
	b = t + rc.Height()*0.08;
	b_mail[1] = NewMyButton(IDS_BUTTON_DELETEMAIL_USER, CRect(p, t, q, b), 0);
}


void CDialog_manage::OnClickInfOfMail(NMHDR* pNMHDR, LRESULT* pResult)
{
	CString str;
	int nId;
	//首先得到点击的位置
	POSITION pos = l_maillist[0]->GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		//		GetDlgItem(IDS_BUTTON_CHANGEMATERIAL_INF)->EnableWindow(true);
		//		GetDlgItem(IDS_BUTTON_DELETEMATERIAL)->EnableWindow(true);
		//得到行号，通过POSITION转化
		nId = (int)l_maillist[0]->GetNextSelectedItem(pos);
		//得到列中的内容（0表示第一列，同理1,2,3...表示第二，三，四...列）
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
			CString alter("数据操作出现错误！");
			MessageBox(alter);
		}
		//		memory_1 = l_maillist[0]->GetItemText(nId, 0);
		CString a("已查看");
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


void CDialog_manage::CoutTheDetail_mail(CString num)
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

	CString TITLE("信息内容:");
	CString SENDER("发件人编号:");
	CString SENDER_NAME("发件人:");

	_RecordsetPtr pRst;
	char sql[255] = { 0 };
	USES_CONVERSION;
	char *temp;
	temp = T2A(num);
	sprintf_s(sql, "select * from SYS_MAIL WHERE mno = '%s'", temp);
	pRst = dbOper.ExecuteWithResSQL(sql);
	if (NULL == pRst)
	{
		CString alter("查询数据出现错误！");
		MessageBox(alter);
	}
	else if (pRst->adoEOF)
	{
		pRst->Close();

		//CString alter("未查询到结果！");
		//MessageBox(alter);
	}
	else
	{
		pRst->MoveFirst(); //记录集指针移动到查询结果集的前面
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

void CDialog_manage::OnClickDelete_mail()
{
	CString num;
	USES_CONVERSION;
	char *temp;
	for (int i = 0; i < l_maillist[0]->GetItemCount(); i++)
	{
		if (l_maillist[0]->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED || l_maillist[0]->GetCheck(i))
		{
			num = l_maillist[0]->GetItemText(i, 2);
			if (memory == "已查看")
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
					MessageBox(CString("删除失败"));
				}
				else
				{
					MessageBox(CString("删除成功"));
				}

			}
			else
			{
				MessageBox(CString("该信息还没有看过哦！"));
			}
		}

	}
	OnBnClickedButton8();
}


void CDialog_manage::OnClickSendMail()
{
	CDialog_sendMail send;
	send.DoModal();
}


void CDialog_manage::OnBnClickedButton5()
{
	// TODO:  在此添加控件通知处理程序代码
	switchPages();

	///////////////////////////////////

	GetWindowRect(&rc);
	int p;
	int q;
	int t, b;

	p = rc.Width()*0.24;
	q = p + rc.Width()*0.58;
	t = rc.Height()*0.07;
	b = t + rc.Height()*0.27;
	l_order_c[0] = NewMyListCtrl(IDS_LISTCRTL_ADMIN_ORDERCHECK, CRect(p, t, q, b), 0);
	l_order_c[0]->InsertColumn(0, _T("订单编号:"), LVCFMT_LEFT, 100);
	l_order_c[0]->InsertColumn(1, _T("开始时间:"), LVCFMT_LEFT, 100);
	l_order_c[0]->InsertColumn(2, _T("结束时间:"), LVCFMT_LEFT, 70);
	l_order_c[0]->InsertColumn(3, _T("订单用户:"), LVCFMT_LEFT, 100);
	l_order_c[0]->InsertColumn(4, _T("订单总价:"), LVCFMT_LEFT, 110);

	p = rc.Width()*0.24;
	q = p + rc.Width()*0.58;
	t = rc.Height()*0.36;
	b = t + rc.Height()*0.23;
	l_order_c[2] = NewMyListCtrl(IDS_LISTCTRL_ORDEROWNER_ADMIN, CRect(p, t, q, b), 0);
	l_order_c[2]->InsertColumn(0, _T("订单编号:"), LVCFMT_LEFT, 100);
	l_order_c[2]->InsertColumn(1, _T("开始时间:"), LVCFMT_LEFT, 100);
	l_order_c[2]->InsertColumn(2, _T("结束时间:"), LVCFMT_LEFT, 70);
	l_order_c[2]->InsertColumn(3, _T("订单用户:"), LVCFMT_LEFT, 100);
	l_order_c[2]->InsertColumn(4, _T("订单总价:"), LVCFMT_LEFT, 110);

	p = rc.Width()*0.24;
	q = p + rc.Width()*0.58;
	t = rc.Height()*0.62;
	b = t + rc.Height()*0.2;
	l_order_c[1] = NewMyListCtrl(IDS_LISTCRTL_ADMIN_ORDER_M, CRect(p, t, q, b), 0);
	l_order_c[1]->InsertColumn(0, _T("教材编号:"), LVCFMT_LEFT, 100);
	l_order_c[1]->InsertColumn(1, _T("教材名称:"), LVCFMT_LEFT, 200);
	l_order_c[1]->InsertColumn(2, _T("订购数量:"), LVCFMT_LEFT, 100);


	_RecordsetPtr pRst;
	char sql[255] = { 0 };

	USES_CONVERSION;
	char* temp;

	strcpy_s(sql, "select * from SYS_ORDER where status = '3'");
	pRst = dbOper.ExecuteWithResSQL(sql);

	if (pRst == NULL)
	{
		CString alter("查找失败！！");
		MessageBox(alter);
	}

	//	if (pRst->adoEOF)
	//	{
	//		CString alter("没有订单哦！！");
	//		MessageBox(alter);
	//	}
	else if (!pRst->adoEOF)
	{

		pRst->MoveFirst(); //记录集指针移动到查询结果集的前面
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
				sno_1 = "未生效";
			}
			else if (sno_1 == "2")
			{
				sno_1 = "等待学院审批";
			}
			else if (sno_1 == "3")
			{
				sno_1 = "等待教材科审批";
			}
			else if (sno_1 == "4")
			{
				sno_1 = "教材已开始分配";
			}
			else if (sno_1 == "5")
			{
				sno_1 = "学院审批未通过";
			}
			else if (sno_1 == "6")
			{
				sno_1 = "教材科审批未通过";
			}
			else if (sno_1 == "7")
			{
				sno_1 = "订单已完成";
			}

			nRow = l_order_c[0]->InsertItem(0, num_1);//插入行
			l_order_c[0]->SetItemText(nRow, 1, begindate_1);//设置数据
			l_order_c[0]->SetItemText(nRow, 2, enddate_1);//设置数据
			l_order_c[0]->SetItemText(nRow, 3, sno_1);
			l_order_c[0]->SetItemText(nRow, 4, sum_1);
			pRst->MoveNext();
		}

			////////////////////////////////////////////			
	}

	_RecordsetPtr pRst_1;
	char sql_1[255] = { 0 };


	strcpy_s(sql_1, "select * from SYS_ORDER where status = '4'");
	pRst_1 = dbOper.ExecuteWithResSQL(sql_1);

	if (pRst_1 == NULL)
	{
		CString alter("查找失败！！");
		MessageBox(alter);
	}

	//	if (pRst->adoEOF)
	//	{
	//		CString alter("没有订单哦！！");
	//		MessageBox(alter);
	//	}
	else if (!pRst_1->adoEOF)
	{

		pRst_1->MoveFirst(); //记录集指针移动到查询结果集的前面
		_variant_t vNum, vBegindate, vEnddate, vSno, vSum;
		int nRow;
		while (!pRst_1->adoEOF)
		{

			vNum = pRst_1->GetCollect(_variant_t("num"));
			vBegindate = pRst_1->GetCollect(_variant_t("begindate"));
			vEnddate = pRst_1->GetCollect(_variant_t("enddate"));
			vSno = pRst_1->GetCollect(_variant_t("sno"));
			vSum = pRst_1->GetCollect(_variant_t("sum"));


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
				sno_1 = "未生效";
			}
			else if (sno_1 == "2")
			{
				sno_1 = "等待学院审批";
			}
			else if (sno_1 == "3")
			{
				sno_1 = "等待教材科审批";
			}
			else if (sno_1 == "4")
			{
				sno_1 = "教材已开始分配";
			}
			else if (sno_1 == "5")
			{
				sno_1 = "学院审批未通过";
			}
			else if (sno_1 == "6")
			{
				sno_1 = "教材科审批未通过";
			}
			else if (sno_1 == "7")
			{
				sno_1 = "订单已完成";
			}
			else if (sno_1 == "8")
			{
				sno_1 = "订单分配完成";
			}

			nRow = l_order_c[2]->InsertItem(0, num_1);//插入行
			l_order_c[2]->SetItemText(nRow, 1, begindate_1);//设置数据
			l_order_c[2]->SetItemText(nRow, 2, enddate_1);//设置数据
			l_order_c[2]->SetItemText(nRow, 3, sno_1);
			l_order_c[2]->SetItemText(nRow, 4, sum_1);

			/////////////////////////////////////////////////
			pRst_1->MoveNext();
		}
	}

	p = rc.Width()*0.83;
	q = p + rc.Width()*0.1;
	t = rc.Height()*0.22;
	b = t + 40;
	b_orderCheck[0] = NewMyButton(IDS_BUTTON_ORDERCHECK_ADMIN, CRect(p, t, q, b), 0);
	p = rc.Width()*0.83;
	q = p + rc.Width()*0.1;
	t = rc.Height()*0.29;
	b = t + 40;
	b_orderCheck[1] = NewMyButton(IDS_BUTTON_ORDERCHECK_ADMIN_NO, CRect(p, t, q, b), 0);
	p = rc.Width()*0.83;
	q = p + rc.Width()*0.1;
	t = rc.Height()*0.53;
	b = t + 40;
	b_orderCheck[2] = NewMyButton(IDS_BUTTON_ACCOMPLISH_DIS, CRect(p, t, q, b), 0);
}


void CDialog_manage::OnClickInfOfOrder(NMHDR* pNMHDR, LRESULT* pResult)
{
	CString str;
	int nId;
	//首先得到点击的位置
	POSITION pos = l_order_c[0]->GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		GetDlgItem(IDS_BUTTON_ORDERCHECK_ADMIN)->EnableWindow(true);
		GetDlgItem(IDS_BUTTON_ORDERCHECK_ADMIN_NO)->EnableWindow(true);
		//得到行号，通过POSITION转化
		nId = (int)l_order_c[0]->GetNextSelectedItem(pos);
		//得到列中的内容（0表示第一列，同理1,2,3...表示第二，三，四...列）
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

void CDialog_manage::OnClickInfOfOrder_accomplish(NMHDR* pNMHDR, LRESULT* pResult)
{
	CString str;
	int nId;
	//首先得到点击的位置
	POSITION pos = l_order_c[2]->GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		GetDlgItem(IDS_BUTTON_ACCOMPLISH_DIS)->EnableWindow(true);
		//得到行号，通过POSITION转化
		nId = (int)l_order_c[2]->GetNextSelectedItem(pos);
		//得到列中的内容（0表示第一列，同理1,2,3...表示第二，三，四...列）
		str = l_order_c[2]->GetItemText(nId, 0);
		memory_1 = l_order_c[2]->GetItemText(nId, 0);
		memory = l_order_c[2]->GetItemText(nId, 3);
		CoutTheDetail_Order(str);
	}
	else
	{
		GetDlgItem(IDS_BUTTON_ACCOMPLISH_DIS)->EnableWindow(false);

	}
}

void CDialog_manage::CoutTheDetail_Order(CString num)      //显示教材详细信息
{
	l_order_c[1]->DeleteAllItems();

	USES_CONVERSION;
	_RecordsetPtr pRst_1;
	char sql_1[255] = { 0 };
	char* temp_1;
	temp_1 = T2A(num);

	sprintf_s(sql_1, "select * from SYS_ORDER_M where num = '%s'", temp_1);
	pRst_1 = dbOper.ExecuteWithResSQL(sql_1);

	if (pRst_1 == NULL)
	{
		CString alter("查找失败！！");
		MessageBox(alter);
	}

//	if (pRst_1->adoEOF)
//	{
//		CString alter("没有订单哦！！");
//		MessageBox(alter);
//	}
	else if (!pRst_1->adoEOF)
	{

		pRst_1->MoveFirst(); //记录集指针移动到查询结果集的前面
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

			nRow_1 = l_order_c[1]->InsertItem(0, bno_1);//插入行
			l_order_c[1]->SetItemText(nRow_1, 1, bname_1);//设置数据
			l_order_c[1]->SetItemText(nRow_1, 2, qua_1);//设置数据


			pRst_1->MoveNext();
		}
	}

	
}


void CDialog_manage::OnClickAgreeOrder()
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
			sprintf_s(sql, "update SYS_ORDER set status = '4' where num = '%s'", temp);
			pRst = dbOper.ExecuteWithResSQL(sql);
			if (pRst == NULL)
			{
				MessageBox(CString("修改失败"));
			}
			else
			{
				MessageBox(CString("审批成功！"));
			}
		}

	}
	OnBnClickedButton5();
}

void CDialog_manage::OnClickdisagreeOrder()
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
					CString alter("查询数据出现错误！");
					CDialog_manage a;
					a.MessageBox(alter);
				}
				else if (pRst->adoEOF)
				{
					pRst->Close();
					CDialog_manage a;
					CString alter("未查询到结果！");
					a.MessageBox(alter);
				}
				else
				{
					pRst->MoveFirst(); //记录集指针移动到查询结果集的前面
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
								MessageBox(CString("查询出错！"));
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
				CString system("您订单号为");
				CString num_1;
				num_1 = l_order_c[0]->GetItemText(i, 0);
				CString system_1("的订单未通过教材科的审批，原因是：");
				system = system + num_1 + system_1 + contain;
				sender = T2A(CONTROL.land.returnNumber());
				sender_name = T2A(CONTROL.land.returnUsername());
				receiver = T2A(rec);
				content = T2A(system);
				mno = T2A(num);
				sprintf_s(sql, "insert into SYS_MAIL(mno,sender,receiver,content,sender_name,ifread) values('%s','%s','%s','%s','%s','1')", mno, sender, receiver, content, sender_name);
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
					MessageBox(CString("审批失败"));
				}
			}

		}

	}
	OnBnClickedButton5();
}

void CDialog_manage::OnClickAccomplishDis()
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
	for (int i = 0; i < l_order_c[2]->GetItemCount(); i++)
	{
		if (l_order_c[2]->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED || l_order_c[2]->GetCheck(i))
		{
			_RecordsetPtr pRst;
			char sql[255] = { 0 };
			CString number;
			rec = l_order_c[2]->GetItemText(i, 3);
			CString contain;
			if (true)
			{

				CString count_1;
				strcpy_s(sql, "select count(mno) count from SYS_MAIL");
				pRst = dbOper.ExecuteWithResSQL(sql);
				if (NULL == pRst)
				{
					CString alter("查询数据出现错误！");
					CDialog_manage a;
					a.MessageBox(alter);
				}
				else if (pRst->adoEOF)
				{
					pRst->Close();
					CDialog_manage a;
					CString alter("未查询到结果！");
					a.MessageBox(alter);
				}
				else
				{
					pRst->MoveFirst(); //记录集指针移动到查询结果集的前面
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
								MessageBox(CString("查询出错！"));
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

				CString system("您订单号为");
				CString num_1;
				num_1 = l_order_c[2]->GetItemText(i, 0);
				CString system_1("的订单已经完成分配，请联系教材科进行领取！");
				system = system + num_1 + system_1;
				sender = T2A(CONTROL.land.returnNumber());
				sender_name = T2A(CONTROL.land.returnUsername());
				receiver = T2A(rec);
				content = T2A(system);
				mno = T2A(num);
				sprintf_s(sql, "insert into SYS_MAIL(mno,sender,receiver,content,sender_name,ifread) values('%s','%s','%s','%s','%s','1')", mno, sender, receiver, content, sender_name);
				pRst = dbOper.ExecuteWithResSQL(sql);

				if (pRst != NULL)
				{
					number = l_order_c[2]->GetItemText(i, 0);
					temp_1 = T2A(number);
					sprintf_s(sql, "update SYS_ORDER set status = '8' where num = '%s'", temp_1);
					pRst = dbOper.ExecuteWithResSQL(sql);
					if (pRst != NULL)
					{
						MessageBox(CString("已通知订单用户进行领取!")); 
					}
					if (pRst == NULL)
					{
						MessageBox(CString("状态修改失败！"));
					}
				}
				else
				{
					MessageBox(CString("信息发送失败"));
				}
			}

		}

	}
	OnBnClickedButton5();
}

void CDialog_manage::switchPages()
{
	//m_person_static.ShowWindow(SW_HIDE);
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

	for (int i = 0; i < 12; i++)
	{
		if (s_person_inf[i])
		{
			s_person_inf[i]->DestroyWindow();
			delete s_person_inf[i];
			s_person_inf[i] = NULL;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		if (b_person_information[i])
		{
			b_person_information[i]->DestroyWindow();
			delete b_person_information[i];
			b_person_information[i] = NULL;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (l_personInf[i])
		{
			l_personInf[i]->DestroyWindow();
			delete l_personInf[i];
			l_personInf[i] = NULL;
		}
	}

	for (int i = 0; i <3; i++)
	{
		if (c_changePerson_inf[i])
		{
			c_changePerson_inf[i]->DestroyWindow();
			delete c_changePerson_inf[i];
			c_changePerson_inf[i] = NULL;
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

	for (int i = 0; i < 3; i++)
	{
		if (l_order_c[i])
		{
			l_order_c[i]->DestroyWindow();
			delete l_order_c[i];
			l_order_c[i] = NULL;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (b_orderCheck[i])
		{
			b_orderCheck[i]->DestroyWindow();
			delete b_orderCheck[i];
			b_orderCheck[i] = NULL;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		if (b_notice[i])
		{
			b_notice[i]->DestroyWindow();
			delete b_notice[i];
			b_notice[i] = NULL;
		}
	}
}


BOOL CDialog_manage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	OnBnClickedButton1();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CDialog_manage::OnBnClickedButton9()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialog_changePassword a;
	a.DoModal();
}
