// Dialog_user.cpp : 实现文件
//

#include "stdafx.h"
#include "TUMMS.h"
#include "Dialog_user.h"
#include "afxdialogex.h"
#include "TUMMSDlg.h"
#include "DBOperation.h"
#include<stdio.h>
#include<string.h>
#include<iostream>
#include "Function.h"
#include "Dialog_sendMail.h"
#include "Dialog_changePassword.h"
using namespace std;

extern control CONTROL;
extern CDBOperation dbOper;
extern bool bConn;
extern CRect rc;
extern CString n_title;
extern CString n_content;

CString NOTICE;
CString str;

// CDialog_user 对话框

IMPLEMENT_DYNAMIC(CDialog_user, CDialogEx)

CDialog_user::CDialog_user(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialog_user::IDD, pParent)
	, cstrItemTextEdit(_T(""))
	, user_notice(_T(""))
{
	head = NULL;
	
}

CDialog_user::~CDialog_user()
{
}

//BOOL CDialog_user::OnInitDialog()
//{
//	CDialog_user::OnInitDialog();
//
//	m_SubItemEdit.ShowWindow(SW_HIDE);
//	return TRUE;
//}

void CDialog_user::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_SubItemEdit);
	DDX_Text(pDX, IDC_EDIT1, cstrItemTextEdit);
	DDX_Text(pDX, IDC_NOTICE_2, user_notice);
	DDV_MaxChars(pDX, user_notice, 140);
}


BEGIN_MESSAGE_MAP(CDialog_user, CDialogEx)
	ON_BN_CLICKED(IDC_BACK_TO_LAND, &CDialog_user::OnBnClickedBackToLand)
	ON_BN_CLICKED(IDC_PERSONAL_INFORMATION_NORMAL, &CDialog_user::OnBnClickedPersonalInformationNormal)
	ON_BN_CLICKED(IDC_MATERIAL_PURCHASE, &CDialog_user::OnBnClickedMaterialPurchase)
	ON_BN_CLICKED(IDC_ORDER_FORM_CHECK, &CDialog_user::OnBnClickedOrderFormCheck)
	ON_BN_CLICKED(IDC_MAIL_CASE_NORMAL, &CDialog_user::OnBnClickedMailCaseNormal)
	ON_BN_CLICKED(IDS_BUTTON_CHANGEPERSON_1, &CDialog_user::OnBnClickChangeMessage)
	ON_BN_CLICKED(IDS_BUTTON_CHANGEPERSON_2, &CDialog_user::OnClickSaveChange)
	ON_BN_CLICKED(IDS_BUTTON_CHANGEPERSON_3, &CDialog_user::OnClickCancelChange)
	ON_NOTIFY(NM_CLICK, IDS_USER_MATERIALLIST, OnClickInfOfMaterial)
	ON_BN_CLICKED(IDS_BUTTON_ADDTOSHOPCAR, &CDialog_user::OnClickAddShopCar)
	ON_NOTIFY(NM_DBLCLK, IDS_LISTCRTL_BUYLIST, &CDialog_user::OnDBClickShopCar)
	ON_BN_CLICKED(IDS_BUTTON_DELETEFROMSHOPCAR, &CDialog_user::OnClickDeleteShopCar)
	ON_EN_KILLFOCUS(IDC_EDIT1, &CDialog_user::OnKillfocusEdit1)
	ON_BN_CLICKED(IDS_BUTTON_COMMITSHOPCAR, &CDialog_user::OnClickCommitOrder)
	ON_BN_CLICKED(IDS_BUTTON_ORDER_MAKESURE, &CDialog_user::OnClickMakesureOrder)
	ON_BN_CLICKED(IDS_BUTTON_ORDER_CANCEL, &CDialog_user::OnClickCancelOrder)
	ON_NOTIFY(NM_CLICK, IDS_LISTCRTL_CHECKORDER, OnClickInfOfOrder)
	ON_BN_CLICKED(IDS_BUTTON_DELETEORDER, &CDialog_user::OnClickDeleteOrder)
	ON_BN_CLICKED(IDS_BUTTON_DELETEORDER_MATERIAL, &CDialog_user::OnClickDeleteOrder_m)
	ON_NOTIFY(NM_CLICK, IDS_LISTCTRL_USER_MAINLIST, OnClickInfOfMail)
	ON_BN_CLICKED(IDS_BUTTON_DELETEMAIL_USER, &CDialog_user::OnClickDelete_mail)
	ON_BN_CLICKED(IDS_BUTTON_SENDMAIL_USER, &CDialog_user::OnClickSendMail)
	ON_BN_CLICKED(IDS_BUTTON_ACCOMPLISH_ORDER, &CDialog_user::OnClickAccomplishOrder)
	ON_BN_CLICKED(IDC_ChangePassword, &CDialog_user::OnBnClickedChangepassword)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CDialog_user 消息处理程序

CButton* CDialog_user::NewMyButton(int nID, CRect rect, int nStyle)
{
	CString m_Caption;
	m_Caption.LoadString( nID ); //取按钮标题
	CButton *p_Button = new CButton();
	ASSERT_VALID(p_Button);
	p_Button->Create( m_Caption, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | nStyle, rect, this, nID ); //创建按钮
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

CStatic* CDialog_user::NewMyStatic(int nID,CString text, CRect rect, int nStyle)
{
	LPCTSTR P = (LPCTSTR)text;
	CStatic *p_static = new CStatic();
	ASSERT_VALID(p_static);
	p_static->Create(P, WS_CHILD | WS_VISIBLE | SS_LEFT |   nStyle, rect, this, nID);  //创建静态文本
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

CEdit* CDialog_user::NewMyEdit(int nID, CRect rect, int nStyle)
{
	CEdit *p_edit = new CEdit();
	ASSERT_VALID(p_edit);
	p_edit->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY | nStyle, rect, this, nID);  //创建静态文本
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

CListCtrl* CDialog_user::NewMyListCtrl(int nID, CRect rect, int nStyle)
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

void CDialog_user::OnBnClickedBackToLand()
{
	// TODO:  在此添加控件通知处理程序代码
	CTUMMSDlg land;
	CDialog_user::OnOK();
	land.DoModal();
}


void CDialog_user::OnBnClickedPersonalInformationNormal()
{

	switchPages();

	GetWindowRect(&rc);
	int p ;
	int q ;
	int t, b;
	// TODO:  在此添加控件通知处理程序代码
	CString name("姓名:");
	CString sex("性别:");
	CString tel("电话:");
	CString num("教师证号:");
	p = rc.Width()*0.7;
	q = p + 150;
	t = rc.Height()*0.65;
	b = t + 50;
	b_personalInformation[0] = NewMyButton(IDS_BUTTON_CHANGEPERSON_1, CRect(p, t, q, b), 0);

	p = rc.Width()*0.43;
	q = p + 100;
	t = rc.Height()*0.14;
	b = t + 20;
	s_personalInformation[6] = NewMyStatic(IDS_STATIC_INFORMATION_7, CONTROL.land.returnNumber(), CRect(p, t, q, b), 0);
	p = rc.Width()*0.29;
	q = p + 70;
	t = rc.Height()*0.14;
	b = t + 20;
	s_personalInformation[7] = NewMyStatic(IDS_STATIC_INFORMATION_8, num, CRect(p, t, q, b), 0);
	p = rc.Width()*0.42;
	q = p + 100;
	t = rc.Height()*0.24;
	b = t + 20;
	s_personalInformation[0] = NewMyStatic(IDS_STATIC_INFORMATION_1, CONTROL.land.returnUsername(), CRect(p, t, q, b), 0);
	p = rc.Width()*0.3;
	q = p + 50;
	t = rc.Height()*0.24;
	b = t + 20;
	s_personalInformation[1] = NewMyStatic(IDS_STATIC_INFORMATION_2, name, CRect(p, t, q, b), 0);
	p = rc.Width()*0.42;
	q = p + 100;
	t = rc.Height()*0.34;
	b = t + 20;
	s_personalInformation[2] = NewMyStatic(IDS_STATIC_INFORMATION_3, CONTROL.land.returnSex(), CRect(p, t, q, b), 0);
	p = rc.Width()*0.3;
	q = p + 50;
	t = rc.Height()*0.34;
	b = t + 20;
	s_personalInformation[3] = NewMyStatic(IDS_STATIC_INFORMATION_4, sex, CRect(p, t, q, b), 0);
	p = rc.Width()*0.42;
	q = p + 100;
	t = rc.Height()*0.44;
	b = t + 20;
	s_personalInformation[4] = NewMyStatic(IDS_STATIC_INFORMATION_5, CONTROL.land.returnTel(), CRect(p, t, q, b), 0);
	p = rc.Width()*0.3;
	q = p + 50;
	t = rc.Height()*0.44;
	b = t + 20;
	s_personalInformation[5] = NewMyStatic(IDS_STATIC_INFORMATION_6, tel, CRect(p, t, q, b), 0);
}


void CDialog_user::OnBnClickedMaterialPurchase()
{
	// TODO:  在此添加控件通知处理程序代码
	switchPages();

	////////////////////////////////
	GetWindowRect(&rc);
	int p;
	int q;
	int t, b;
	p = rc.Width()*0.23;
	q = p + rc.Width()*0.3;
	t = rc.Height()*0.07;
	b = t + rc.Height()*0.7;
	l_materialInf[0] = NewMyListCtrl(IDS_USER_MATERIALLIST,CRect(p,t,q,b),0);
	l_materialInf[0]->InsertColumn(0, _T("教材编号"), LVCFMT_LEFT, (rc.Width()*0.3)*0.37);
	l_materialInf[0]->InsertColumn(1, _T("教材名称"), LVCFMT_LEFT, (rc.Width()*0.3)*0.63);

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


			string sno = (LPCSTR)_bstr_t(vNum);
			string name = (LPCSTR)_bstr_t(vName);

			CString sno_1;
			CString name_1;
			sno_1 = sno.c_str();
			name_1 = name.c_str();
			sno_1.Remove(' ');
			name_1.Remove(' ');

			int nRow = l_materialInf[0]->InsertItem(0, sno_1);//插入行
			l_materialInf[0]->SetItemText(nRow, 1, name_1);//设置数据

			pRst->MoveNext();

		}
	}

	/////////////////////////////////////////////////////////////教材列表
	p = rc.Width()*0.55;
	q = p + rc.Width()*0.09;
	t = rc.Height()*0.40;
	b = t + 40;
	b_materialBuy[0] = NewMyButton(IDS_BUTTON_ADDTOSHOPCAR, CRect(p, t, q, b), 0);
	p = rc.Width()*0.55;
	q = p + rc.Width()*0.09;
	t = rc.Height()*0.50;
	b = t + 40;
	b_materialBuy[1] = NewMyButton(IDS_BUTTON_DELETEFROMSHOPCAR, CRect(p, t, q, b), 0);
	p = rc.Width()*0.55;
	q = p + rc.Width()*0.09;
	t = rc.Height()*0.60;
	b = t + 40;
	b_materialBuy[2] = NewMyButton(IDS_BUTTON_COMMITSHOPCAR, CRect(p, t, q, b), 0);

	p = rc.Width()*0.66;
	q = p + rc.Width()*0.27;
	t = rc.Height()*0.37;
	b = t + rc.Height()*0.4;
	l_materialInf[1] = NewMyListCtrl(IDS_LISTCRTL_BUYLIST, CRect(p, t, q, b), 0);
	l_materialInf[1]->InsertColumn(0, _T("教材编号"), LVCFMT_LEFT, 150);
	l_materialInf[1]->InsertColumn(1, _T("数量"), LVCFMT_LEFT, 50);



}

void CDialog_user::CoutTheDetail(CString num)      //显示教材详细信息
{
	for (int i = 0; i < 5; i++)
	{
		if (s_materialInf[i])
		{
			s_materialInf[i]->DestroyWindow();
			delete s_materialInf[i];
			s_materialInf[i] = NULL;
		}
	}
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

		CString alter("未查询到结果！");
		MessageBox(alter);
	}
	else
	{
		pRst->MoveFirst(); //记录集指针移动到查询结果集的前面
		_variant_t vNum, vName,vAuthor, vPrice, vBc;
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

			vBc = pRst->GetCollect(_variant_t("bbc"));

			string sno = (LPCSTR)_bstr_t(vNum);
			string name = (LPCSTR)_bstr_t(vName);
			string author = (LPCSTR)_bstr_t(vAuthor);
			string price = (LPCSTR)_bstr_t(vPrice);
			string bc = (LPCSTR)_bstr_t(vBc);

			CString sno_1;
			CString name_1;
			CString author_1;
			CString price_1;
			CString bc_1;
			sno_1 = sno.c_str();
			name_1 = name.c_str();
			author_1 = author.c_str();
			price_1 = price.c_str();
			bc_1 = bc.c_str();
			sno_1.Remove(' ');
			name_1.Remove(' ');
			author_1.Remove(' ');
			price_1.Remove(' ');
			bc_1.Remove(' ');

			CString SNO("编号：");
			CString NAME("名称：");
			CString AUTHOR("作者：");
			CString PRICE("价格(本)：");
			CString BC("版次：");

			SNO += sno_1;
			NAME += name_1;
			AUTHOR += author_1;
			PRICE += price_1;
			BC += bc_1;

			p = rc.Width()*0.57;
			q = p + 200;
			t = rc.Height()*0.07;
			b = t + 20;
			s_materialInf[0] = NewMyStatic(IDS_STATIC_INF_MATERIAL_1, SNO, CRect(p, t, q, b), 0);
			p = rc.Width()*0.57;
			q = p + 250;
			t = rc.Height()*0.12;
			b = t + 20;
			s_materialInf[1] = NewMyStatic(IDS_STATIC_INF_MATERIAL_2, NAME, CRect(p, t, q, b), 0);
			p = rc.Width()*0.57;
			q = p + 200;
			t = rc.Height()*0.17;
			b = t + 20;
			s_materialInf[2] = NewMyStatic(IDS_STATIC_INF_MATERIAL_3, AUTHOR, CRect(p, t, q, b), 0);
			p = rc.Width()*0.57;
			q = p + 200;
			t = rc.Height()*0.22;
			b = t + 20;
			s_materialInf[3] = NewMyStatic(IDS_STATIC_INF_MATERIAL_4, PRICE, CRect(p, t, q, b), 0);
			p = rc.Width()*0.57;
			q = p + 100;
			t = rc.Height()*0.27;
			b = t + 20;
			s_materialInf[4] = NewMyStatic(IDS_STATIC_INF_MATERIAL_5, BC, CRect(p, t, q, b), 0);

			pRst->MoveNext();

		}
	}
}

void CDialog_user::OnClickInfOfMaterial(NMHDR* pNMHDR, LRESULT* pResult)
{
	CString str;
	int nId;
	//首先得到点击的位置
	POSITION pos = l_materialInf[0]->GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		//得到行号，通过POSITION转化
		nId = (int)l_materialInf[0]->GetNextSelectedItem(pos);
		//得到列中的内容（0表示第一列，同理1,2,3...表示第二，三，四...列）
		str = l_materialInf[0]->GetItemText(nId, 0);
		CoutTheDetail(str);
	}
	
}

void CDialog_user::OnBnClickedOrderFormCheck()
{
	// TODO:  在此添加控件通知处理程序代码
	switchPages();

	////////////////////////////////////////

	GetWindowRect(&rc);
	int p;
	int q;
	int t, b;

	p = rc.Width()*0.23;
	q = p + rc.Width()*0.58;
	t = rc.Height()*0.07;
	b = t + rc.Height()*0.35;
	l_order = NewMyListCtrl(IDS_LISTCRTL_CHECKORDER, CRect(p, t, q, b), 0);
	l_order->InsertColumn(0, _T("订单编号:"), LVCFMT_LEFT, (rc.Width()*0.58)*0.2);
	l_order->InsertColumn(1, _T("开始时间:"), LVCFMT_LEFT, (rc.Width()*0.58)*0.2);
	l_order->InsertColumn(2, _T("结束时间:"), LVCFMT_LEFT, (rc.Width()*0.58)*0.2);
	l_order->InsertColumn(3, _T("订单状态:"), LVCFMT_LEFT, (rc.Width()*0.58)*0.2);
	l_order->InsertColumn(4, _T("订单总价:"), LVCFMT_LEFT, (rc.Width()*0.58)*0.2);

	p = rc.Width()*0.23;
	q = p + rc.Width()*0.58;
	t = rc.Height()*0.45;
	b = t + rc.Height()*0.32;
	l_order_m = NewMyListCtrl(IDS_LISTCRTL_ORDERMATERIAL, CRect(p, t, q, b), 0);
	l_order_m->InsertColumn(0, _T("教材编号:"), LVCFMT_LEFT, 150);
	l_order_m->InsertColumn(1, _T("教材名称:"), LVCFMT_LEFT, 200);
	l_order_m->InsertColumn(2, _T("订购数量:"), LVCFMT_LEFT, 100);


	_RecordsetPtr pRst;
	char sql[255] = { 0 };

	USES_CONVERSION;
	char* temp;
	temp = T2A(CONTROL.land.returnNumber());

	sprintf_s(sql, "select * from SYS_ORDER where sno = '%s'", temp);
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
		_variant_t vNum, vBegindate, vEnddate, vStatus, vSum;
		int nRow;
		while (!pRst->adoEOF)
		{
			
			vNum = pRst->GetCollect(_variant_t("num"));
			vBegindate = pRst->GetCollect(_variant_t("begindate"));
			vEnddate = pRst->GetCollect(_variant_t("enddate"));
			vStatus = pRst->GetCollect(_variant_t("status"));
			vSum = pRst->GetCollect(_variant_t("sum"));


			string num = (LPCSTR)_bstr_t(vNum);
			string begindate = (LPCSTR)_bstr_t(vBegindate);
			string enddate = (LPCSTR)_bstr_t(vEnddate);
			string status = (LPCSTR)_bstr_t(vStatus);
			string sum = (LPCSTR)_bstr_t(vSum);

			CString num_1;
			CString begindate_1;
			CString enddate_1;
			CString status_1;
			CString sum_1;

			num_1 = num.c_str();
			begindate_1 = begindate.c_str();
			enddate_1 = enddate.c_str();
			status_1 = status.c_str();
			sum_1 = sum.c_str();

			num_1.Remove(' ');
			begindate_1.Remove(' ');
			enddate_1.Remove(' ');
			status_1.Remove(' ');
			sum_1.Remove(' ');

			if (status_1 == "1")
			{
				status_1 = "未生效";
			}
			else if (status_1 == "2")
			{
				status_1 = "等待学院审批";
			}
			else if (status_1 == "3")
			{
				status_1 = "等待教材科审批";
			}
			else if (status_1 == "4")
			{
				status_1 = "教材已开始分配";
			}
			else if (status_1 == "5")
			{
				status_1 = "学院审批未通过";
			}
			else if (status_1 == "6")
			{
				status_1 = "教材科审批未通过";
			}
			else if (status_1 == "7")
			{
				status_1 = "订单已完成";
			}
			else if (status_1 == "8")
			{
				status_1 = "订单分配完成";
			}

			nRow = l_order->InsertItem(0, num_1);//插入行
			l_order->SetItemText(nRow, 1, begindate_1);//设置数据
			l_order->SetItemText(nRow, 2, enddate_1);//设置数据
			l_order->SetItemText(nRow, 3, status_1);
			l_order->SetItemText(nRow, 4, sum_1);

			////////////////////////////////////////////


			
			/////////////////////////////////////////////////
			pRst->MoveNext();
		}
	}

	p = rc.Width()*0.83;
	q = p + 80;
	t = rc.Height()*0.33;
	b = t + 40;
	b_order[0] = NewMyButton(IDS_BUTTON_DELETEORDER, CRect(p, t, q, b), 0);
	p = rc.Width()*0.83;
	q = p + 80;
	t = rc.Height()*0.67;
	b = t + 40;
	b_order[1] = NewMyButton(IDS_BUTTON_DELETEORDER_MATERIAL, CRect(p, t, q, b), 0);
	p = rc.Width()*0.83;
	q = p + 80;
	t = rc.Height()*0.24;
	b = t + 40;
	b_order[2] = NewMyButton(IDS_BUTTON_ACCOMPLISH_ORDER, CRect(p, t, q, b), 0);

}


void CDialog_user::OnClickInfOfOrder(NMHDR* pNMHDR, LRESULT* pResult)
{
	CString str;
	int nId;
	//首先得到点击的位置
	POSITION pos = l_order->GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
//		GetDlgItem(IDS_BUTTON_CHANGEMATERIAL_INF)->EnableWindow(true);
//		GetDlgItem(IDS_BUTTON_DELETEMATERIAL)->EnableWindow(true);
		//得到行号，通过POSITION转化
		nId = (int)l_order->GetNextSelectedItem(pos);
		//得到列中的内容（0表示第一列，同理1,2,3...表示第二，三，四...列）
		str = l_order->GetItemText(nId, 0);
		memory_1 = l_order->GetItemText(nId, 0);
		memory = l_order->GetItemText(nId,3);
		CoutTheDetail_Order(str);
	}
	else
	{
//		GetDlgItem(IDS_BUTTON_CHANGEMATERIAL_INF)->EnableWindow(false);
//		GetDlgItem(IDS_BUTTON_DELETEMATERIAL)->EnableWindow(false);

	}
}

void CDialog_user::CoutTheDetail_Order(CString num)      //显示教材详细信息
{
	l_order_m->DeleteAllItems();

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

	if (pRst_1->adoEOF)
	{
		CString alter("没有订单哦！！");
		MessageBox(alter);
	}
	else
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

			nRow_1 = l_order_m->InsertItem(0, bno_1);//插入行
			l_order_m->SetItemText(nRow_1, 1, bname_1);//设置数据
			l_order_m->SetItemText(nRow_1, 2, qua_1);//设置数据


			pRst_1->MoveNext();
		}
	}
}



void CDialog_user::OnClickDeleteOrder()
{
	CString num;
	USES_CONVERSION;
	char *temp;
	for (int i = 0; i < l_order->GetItemCount(); i++)
	{
		if (l_order->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED || l_order->GetCheck(i))
		{
			num = l_order->GetItemText(i, 3);
			if (memory == "等待学院审批" || memory == "等待教材科审批" || memory == "教材科审批未通过" || memory == "学院审批未通过" || memory == "订单已完成")
			{
				_RecordsetPtr pRst;
				char sql[255] = { 0 };
				CString number;
				number = l_order->GetItemText(i,0);
				temp = T2A(number);
				sprintf_s(sql,"delete from SYS_ORDER_M where num = '%s'",temp);
				pRst = dbOper.ExecuteWithResSQL(sql);
				if (pRst == NULL)
				{
					MessageBox(CString("删除失败"));
				}
				else
				{
					sprintf_s(sql,"delete from SYS_ORDER where num = '%s'",temp);
					pRst = dbOper.ExecuteWithResSQL(sql);
					if (pRst == NULL)
					{
						MessageBox(CString("删除失败！"));
					}
					else
					{
						MessageBox(CString("删除成功！"));
						l_order->DeleteItem(i);
						
					}
				}
				
			}
			else
			{
				MessageBox(CString("该订单订购的教材已经开始分配，不能删除！"));
			}
		}

	}
	OnBnClickedOrderFormCheck();
}

void CDialog_user::OnClickAccomplishOrder()
{
	if (memory == "订单分配完成" )
	{
		CString bno;
		CString time;
		time = GetTime();
		USES_CONVERSION;
		char sql[255] = { 0 };
		_RecordsetPtr pRst;
		char *temp;
		char *temp_1;
		for (int i = 0; i < l_order->GetItemCount(); i++)
		{
			if (l_order->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED || l_order->GetCheck(i))
			{
				bno = l_order->GetItemText(i, 0);
				temp = T2A(bno);
				sprintf_s(sql, "update SYS_ORDER set status = '7' where num = '%s'", temp);
				pRst = dbOper.ExecuteWithResSQL(sql);

				temp_1 = T2A(time);
				sprintf_s(sql, "update SYS_ORDER set enddate = '%s' where num = '%s'", temp_1,temp);
				pRst = dbOper.ExecuteWithResSQL(sql);
				if (pRst == NULL)
				{
					MessageBox(CString("修改失败！"));
				}
				else
				{
					MessageBox(CString("已完成订单！"));
				}
			}

		}
		OnBnClickedOrderFormCheck();
	}
	else
	{
		MessageBox(CString("该订单已经完成了哦！！"));
	}
}

void CDialog_user::OnClickDeleteOrder_m()
{
	if (memory == "等待学院审批" || memory == "等待教材科审批" || memory == "教材科审批未通过" || memory == "学院审批未通过" || memory == "订单已完成")
	{
		CString bno;
		USES_CONVERSION;
		char sql[255] = { 0 };
		_RecordsetPtr pRst;
		char *temp;
		char *temp_1;
		for (int i = 0; i < l_order_m->GetItemCount(); i++)
		{
			if (l_order_m->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED || l_order_m->GetCheck(i))
			{
				bno = l_order_m->GetItemText(i,0);
				temp = T2A(bno);
				temp_1 = T2A(memory_1);
				sprintf_s(sql, "delete from SYS_ORDER_M where bno = '%s' and num = '%s'", temp,temp_1);
				pRst = dbOper.ExecuteWithResSQL(sql);
				if (pRst == NULL)
				{
					MessageBox(CString("删除失败！"));
				}
				else
				{
					MessageBox(CString("删除成功！"));
					l_order_m->DeleteItem(i);
					sprintf_s(sql, "select * from SYS_ORDER_M where num = '%s'", temp_1);
					pRst = dbOper.ExecuteWithResSQL(sql);
					if (pRst->adoEOF)
					{
						sprintf_s(sql, "delete from SYS_ORDER where num = '%s'", temp_1);
						pRst = dbOper.ExecuteWithResSQL(sql);
					}
				}
			}

		}
		OnBnClickedOrderFormCheck();
	}
	else
	{
		MessageBox(CString("该订单已经开始分配，不能删除内容！"));
	}
}

void CDialog_user::OnBnClickedMailCaseNormal()
{
	// TODO:  在此添加控件通知处理程序代码
	switchPages();

	////////////////////////////

	GetWindowRect(&rc);
	int p;
	int q;
	int t, b;

	p = rc.Width()*0.23;
	q = p + rc.Width()*0.3;
	t = rc.Height()*0.07;
	b = t + rc.Height()*0.6;
	l_maillist[0] = NewMyListCtrl(IDS_LISTCTRL_USER_MAINLIST, CRect(p, t, q, b), 0);
	l_maillist[0]->InsertColumn(0, _T("信息编号"), LVCFMT_LEFT, (rc.Width()*0.3)*0.33);
	l_maillist[0]->InsertColumn(1, _T("发信人"), LVCFMT_LEFT, (rc.Width()*0.3)*0.33);
	l_maillist[0]->InsertColumn(2, _T("是否已读"), LVCFMT_LEFT, (rc.Width()*0.3)*0.33);
	USES_CONVERSION;
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

void CDialog_user::OnClickInfOfMail(NMHDR* pNMHDR, LRESULT* pResult)
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

void CDialog_user::CoutTheDetail_mail(CString num)
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


void CDialog_user::OnClickDelete_mail()
{
	CString num;
	USES_CONVERSION;
	char *temp;
	for (int i = 0; i < l_maillist[0]->GetItemCount(); i++)
	{
		if (l_maillist[0]->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED || l_maillist[0]->GetCheck(i))
		{
			num = l_maillist[0]->GetItemText(i, 2);
			if (memory == "已查看" )
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
	OnBnClickedMailCaseNormal();
}


void CDialog_user::OnClickSendMail()
{
	CDialog_sendMail send;
	send.DoModal();
}


void CDialog_user::OnBnClickChangeMessage()
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

	GetDlgItem(IDC_PERSONAL_INFORMATION_NORMAL)->EnableWindow(false);
	GetDlgItem(IDC_MATERIAL_PURCHASE)->EnableWindow(false);
	GetDlgItem(IDC_ORDER_FORM_CHECK)->EnableWindow(false);
	GetDlgItem(IDC_MAIL_CASE_NORMAL)->EnableWindow(false);

	GetWindowRect(&rc);
	int p;
	int q;
	int t, b;

	p = rc.Width()*0.42;
	q = p + 150;
	t = rc.Height()*0.24;
	b = t + 20;
	s_changeinformation[0] = NewMyEdit(IDS_EDIT_CHANGEINFORMATION_NAME, CRect(p, t, q, b),0);
	p = rc.Width()*0.42;
	q = p + 150;
	t = rc.Height()*0.34;
	b = t + 20;
	s_changeinformation[1] = NewMyEdit(IDS_EDIT_CHANGEINFORMATION_SEX, CRect(p, t, q, b), 0);
	p = rc.Width()*0.42;
	q = p + 150;
	t = rc.Height()*0.44;
	b = t + 20;
	s_changeinformation[2] = NewMyEdit(IDS_EDIT_CHANGEINFORMATION_TEL, CRect(p, t, q, b), 0);
	
	s_changeinformation[0]->SetWindowText(CONTROL.land.returnUsername());
	s_changeinformation[1]->SetWindowText(CONTROL.land.returnSex());
	s_changeinformation[2]->SetWindowText(CONTROL.land.returnTel());

	p = rc.Width()*0.7;
	q = p + 150;
	t = rc.Height()*0.65;
	b = t + 50;
	b_personalInformation[1] = NewMyButton(IDS_BUTTON_CHANGEPERSON_2, CRect(p, t, q, b), 0);
	p = rc.Width()*0.4;
	q = p + 150;
	t = rc.Height()*0.65;
	b = t + 50;
	b_personalInformation[2] = NewMyButton(IDS_BUTTON_CHANGEPERSON_3, CRect(p, t, q, b), 0);
}



void CDialog_user::OnClickSaveChange()
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
		sprintf_s(sql, "update SYS_USER set sname = '%s' where sno = '%s'", temp_1, temp_2);
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
		sprintf_s(sql, "update SYS_USER set sex = '%s' where sno = '%s'", temp_1, temp_2);
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
		sprintf_s(sql, "update SYS_USER set tel = '%s' where sno = '%s'", temp_1, temp_2);
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

	GetDlgItem(IDC_PERSONAL_INFORMATION_NORMAL)->EnableWindow(true);
	GetDlgItem(IDC_MATERIAL_PURCHASE)->EnableWindow(true);
	GetDlgItem(IDC_ORDER_FORM_CHECK)->EnableWindow(true);
	GetDlgItem(IDC_MAIL_CASE_NORMAL)->EnableWindow(true);

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

	OnBnClickedPersonalInformationNormal();
}


void CDialog_user::OnClickCancelChange()
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

	GetDlgItem(IDC_PERSONAL_INFORMATION_NORMAL)->EnableWindow(true);
	GetDlgItem(IDC_MATERIAL_PURCHASE)->EnableWindow(true);
	GetDlgItem(IDC_ORDER_FORM_CHECK)->EnableWindow(true);
	GetDlgItem(IDC_MAIL_CASE_NORMAL)->EnableWindow(true);

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

	OnBnClickedPersonalInformationNormal();
}


void CDialog_user::OnClickAddShopCar()
{
	CString num;
	CString count("1");
	int nRow;
	for (int i = 0; i < l_materialInf[0]->GetItemCount(); i++)
	{
		if (l_materialInf[0]->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED || l_materialInf[0]->GetCheck(i))
		{
			num = l_materialInf[0]->GetItemText(i,0);		
			if (!head->check(num, head))
			{
				head->add(num, head);
				nRow = l_materialInf[1]->InsertItem(0, num);//插入行
				l_materialInf[1]->SetItemText(nRow, 1, count);//设置数据
			}
		}
		num = "";
	}
}

void CDialog_user::OnClickDeleteShopCar()
{
	CString num;
	for (int i = 0; i < l_materialInf[1]->GetItemCount(); i++)
	{
		if (l_materialInf[1]->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED || l_materialInf[1]->GetCheck(i))
		{
			num = l_materialInf[1]->GetItemText(i, 0);
			head->deleted(num,head);
			l_materialInf[1]->DeleteItem(i);
		}
		
	}
}






void shop::add(CString num, shop * &head)
{
	_RecordsetPtr pRst;
	char sql[255] = { 0 };
	USES_CONVERSION;
	char *temp;
	CString name_1;
	CString price_1;
	double price_2;
	temp = T2A(num);
	sprintf_s(sql, "select * from SYS_MATERIAL WHERE BNO = '%s'", temp);
	pRst = dbOper.ExecuteWithResSQL(sql);
	if (NULL == pRst)
	{
		CString alter("查询数据出现错误！");
		CDialog_user a;
		a.MessageBox(alter);
	}
	else if (pRst->adoEOF)
	{
		pRst->Close();
		CDialog_user a;
		CString alter("未查询到结果！");
		a.MessageBox(alter);
	}
	else
	{
		pRst->MoveFirst(); //记录集指针移动到查询结果集的前面
		_variant_t  vName, vPrice;
		while (!pRst->adoEOF)
		{

			vName = pRst->GetCollect(_variant_t("bname"));

			vPrice = pRst->GetCollect(_variant_t("bprice"));

			string name = (LPCSTR)_bstr_t(vName);
			string price = (LPCSTR)_bstr_t(vPrice);

			name_1 = name.c_str();
			price_1 = price.c_str();

			name_1.Remove(' ');
			price_1.Remove(' ');


			price_2 = _wtof(price_1.GetBuffer(0));

			pRst->MoveNext();

		}

		///////////////////////

		shop* s;
		s = new shop();
		s->m_name = name_1;
		s->m_num = num;
		s->price = price_2;
		s->count = 1;
		s->next = NULL;

		if (head == NULL)
		{
			head = s;
		}
		else
		{
			shop *p = head;
			while (p)
			{
				if (p->next == NULL)
				{
					p->next = s;
					break;
				}
				p = p->next;
			}
		}
	}
}

void shop::deleted(CString num, shop * &head)
{
	shop *p = NULL;
	shop *q = NULL;
	if (head->m_num == num)
	{
		p = head;
		head = p->next;
		delete p;
		p = NULL;
	}
	else
	{
		p = head;
		q = p->next;
		while(q)
		{
			if (q->m_num == num)
			{
				p->next = q->next;
				delete q;
				q = NULL;
				break;
			}
			p = q;
			q = q->next;
		}
	}
}


void shop::change(CString num, int count, shop * &head)
{
	shop *p = head;
	while (p)
	{
		if (p->m_num == num)
		{
			p->count = count;
			break;
		}
		p = p->next;
	}
}

bool shop::check(CString num, shop * &head)
{
	shop *p = head;
	while (p)
	{
		if (p->m_num == num)
		{
			return true;
		}
		p = p->next;
	}
	return false;
}

void shop::empty(shop * &head)
{
	shop *p = head;
	shop *q = p->next;
	while (p)
	{
		delete p;
		p = q;
		if (q)
			q = q->next;
	}
	head = NULL;
}

void CDialog_user::OnDBClickShopCar(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<NMITEMACTIVATE>(pNMHDR);   
	// TODO: 在此添加控件通知处理程序代码   
	NM_LISTVIEW *pNMListCtrl = (NM_LISTVIEW *)pNMHDR;
	if (pNMListCtrl->iItem != -1 && pNMListCtrl->iSubItem != 0)
	{
		CRect rect, dlgRect;
		//获得当前列的宽度以适应如果用户调整宽度   
		//此处不用获得的子项rect矩形框来设置宽度   
		//是因第一列时返回的宽度是整行的宽度，我也不知道为啥   
		int width = l_materialInf[1]->GetColumnWidth(pNMListCtrl->iSubItem);
		l_materialInf[1]->GetSubItemRect(pNMListCtrl->iItem, pNMListCtrl->iSubItem, LVIR_BOUNDS, rect);
		//保存选择的列表项索引   
		//这个因为我是用了两个列表控件一个CEdit   
		//所以需要保存列表的索引   
		//以及子项相对应的行列号索引   
//		listSelFlag[0] = 1;//列表1   
		listSelFlag[0] = pNMListCtrl->iItem;
		listSelFlag[1] = pNMListCtrl->iSubItem;
		//获得listctrl矩形框   
		//获得父对话框的位置以调整CEdit的显示位置，具体见下面代码   
		l_materialInf[1]->GetWindowRect(&dlgRect);
		//调整与父窗口对应   
		ScreenToClient(&dlgRect);
		int height = rect.Height();
		rect.top += (dlgRect.top + 1);
		rect.left += (dlgRect.left + 1);
		rect.bottom = rect.top + height + 2;
		rect.right = rect.left + width + 2;
		m_SubItemEdit.MoveWindow(&rect);
		m_SubItemEdit.ShowWindow(SW_SHOW);
		m_SubItemEdit.SetFocus();
	}
	//*pResult = 0;   
}




BOOL CDialog_user::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetTimer(1, 500, NULL);

	// TODO:  在此添加额外的初始化
	USES_CONVERSION;
	m_SubItemEdit.ShowWindow(SW_HIDE);
	OnBnClickedPersonalInformationNormal();
	_RecordsetPtr pRst;
	char sql[255] = { 0 };
	char* temp;
	temp = T2A(CONTROL.land.returnNumber());
	sprintf_s(sql, "select * from SYS_MAIL where receiver = '%s'",temp);
	pRst = dbOper.ExecuteWithResSQL(sql);
	if (pRst == NULL)
	{
		MessageBox(CString("查询出错！"));
	}
	else if (!pRst->adoEOF)
	{
		pRst->MoveFirst();
		_variant_t vIfread;
		while (!pRst->adoEOF)
		{
			vIfread = pRst->GetCollect(_variant_t("ifread"));

			string ifread = (LPCSTR)_bstr_t(vIfread);

			CString ifread_1;

			ifread_1 = ifread.c_str();

			ifread_1.Remove(' ');

			if (ifread_1 == "1")
			{
				MessageBox(CString("您有未阅读的消息！"));
				break;
			}

			pRst->MoveNext();
		}
	}

	CString a("[");
	CString b("]");
	CString notice;
	notice = a + n_title + b + n_content;
	NOTICE = notice;
	str = notice;
//	user_notice = notice;
//	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CDialog_user::SetListItemText()
{
	UpdateData(TRUE);
	//AfxMessageBox(cstrItemTextEdit);   
	//此处的cstrItemTextEdit是CEdit控件的字符串关联变量   
	l_materialInf[1]->SetItemText(listSelFlag[0], listSelFlag[1], cstrItemTextEdit);
	CString num;
	num = l_materialInf[1]->GetItemText(listSelFlag[0], 0);
	int count = _ttoi(cstrItemTextEdit);
	head->change(num,count,head);
	//重置编辑框文本   
	m_SubItemEdit.SetWindowText(L"");
	//隐藏编辑框   
	m_SubItemEdit.ShowWindow(SW_HIDE);
	l_materialInf[1]->Invalidate();
}




void CDialog_user::OnKillfocusEdit1()
{
	// TODO:  在此添加控件通知处理程序代码
	SetListItemText();
}


BOOL CDialog_user::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类   
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		if (GetFocus()->GetDlgCtrlID() == IDC_EDIT1)
		{
				l_materialInf[1]->SetFocus();//使列表控件获得焦点，则CEdit会自动失去焦点，触发EN_KILLFOCUS消息   
		}
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CDialog_user::OnClickCommitOrder()
{
	switchPages();

	///////////////////
	if (head == NULL)
	{
		MessageBox(CString("购买列表为空，请添加要订购的教材！"));
		OnBnClickedMaterialPurchase();
		return;
	}
	///////////////////
	GetDlgItem(IDC_PERSONAL_INFORMATION_NORMAL)->EnableWindow(false);
	GetDlgItem(IDC_MATERIAL_PURCHASE)->EnableWindow(false);
	GetDlgItem(IDC_ORDER_FORM_CHECK)->EnableWindow(false);
	GetDlgItem(IDC_MAIL_CASE_NORMAL)->EnableWindow(false);

	GetWindowRect(&rc);
	int p;
	int q;
	int t, b;
	
	CString NUM("订单编号：");
	CString DATE("订单生成时间：");
	CString SNO("订单用户：");
	CString STATUS("订单状态：");
	CString SUM("总价：");
	CString TITLE("订单信息：");

	CString num;
	USES_CONVERSION;
	_RecordsetPtr pRst;
	char sql[255] = { 0 };
	CString count_1;
	strcpy_s(sql, "select count(num) count from SYS_ORDER");
	pRst = dbOper.ExecuteWithResSQL(sql);
	if (NULL == pRst)
	{
		CString alter("查询数据出现错误！");
		CDialog_user a;
		a.MessageBox(alter);
	}
	else if (pRst->adoEOF)
	{
		pRst->Close();
		CDialog_user a;
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
			count_1.Format(_T("%d"),i);
			if (i < 10)
			{
				CString a("000000000");
				num = a + count_1;
			}
			else if (i < 100)
			{
				CString a("00000000");
				num = a + count_1;
			}
			else if (i < 1000)
			{
				CString a("0000000");
				num = a + count_1;
			}
			else if (i < 10000)
			{
				CString a("000000");
				num = a + count_1;
			}
			else if (i < 100000)
			{
				CString a("00000");
				num = a + count_1;
			}
			else if (i < 1000000)
			{
				CString a("0000");
				num = a + count_1;
			}
			else if (i < 10000000)
			{
				CString a("000");
				num = a + count_1;
			}
			else if (i < 100000000)
			{
				CString a("00");
				num = a + count_1;
			}
			else if (i < 1000000000)
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
				sprintf_s(sql_1, "select * from SYS_ORDER where num = '%s'", temp);
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
						CString a("000000000");
						num = a + count_1;
					}
					else if (i < 100)
					{
						CString a("00000000");
						num = a + count_1;
					}
					else if (i < 1000)
					{
						CString a("0000000");
						num = a + count_1;
					}
					else if (i < 10000)
					{
						CString a("000000");
						num = a + count_1;
					}
					else if (i < 100000)
					{
						CString a("00000");
						num = a + count_1;
					}
					else if (i < 1000000)
					{
						CString a("0000");
						num = a + count_1;
					}
					else if (i < 10000000)
					{
						CString a("000");
						num = a + count_1;
					}
					else if (i < 100000000)
					{
						CString a("00");
						num = a + count_1;
					}
					else if (i < 1000000000)
					{
						CString a("0");
						num = a + count_1;
					}
				}
			}

			
			pRst->MoveNext();
		}
	}

	CString time;
	time = GetTime();

	CString users;
	users = CONTROL.land.returnNumber();

	CString status("未生效");

	p = rc.Width()*0.25;
	q = p + 100;
	t = rc.Height()*0.08;
	b = t + 20;
	s_order[10] = NewMyStatic(IDS_STATIC_ORDER_INF_12, TITLE, CRect(p, t, q, b), 0);
	p = rc.Width()*0.43;
	q = p + 100;
	t = rc.Height()*0.14;
	b = t + 20;
	s_order[0] = NewMyStatic(IDS_STATIC_ORDER_INF_1, num, CRect(p, t, q, b), 0);
	p = rc.Width()*0.29;
	q = p + 100;
	t = rc.Height()*0.14;
	b = t + 20;
	s_order[1] = NewMyStatic(IDS_STATIC_ORDER_INF_2, NUM, CRect(p, t, q, b), 0);

	p = rc.Width()*0.43;
	q = p + 150;
	t = rc.Height()*0.19;
	b = t + 20;
	s_order[2] = NewMyStatic(IDS_STATIC_ORDER_INF_3, time, CRect(p, t, q, b), 0);
	p = rc.Width()*0.29;
	q = p + 120;
	t = rc.Height()*0.19;
	b = t + 20;
	s_order[3] = NewMyStatic(IDS_STATIC_ORDER_INF_4, DATE, CRect(p, t, q, b), 0);

	p = rc.Width()*0.43;
	q = p + 100;
	t = rc.Height()*0.24;
	b = t + 20;
	s_order[4] = NewMyStatic(IDS_STATIC_ORDER_INF_5, users, CRect(p, t, q, b), 0);
	p = rc.Width()*0.29;
	q = p + 100;
	t = rc.Height()*0.24;
	b = t + 20;
	s_order[5] = NewMyStatic(IDS_STATIC_ORDER_INF_6, SNO, CRect(p, t, q, b), 0);

	p = rc.Width()*0.43;
	q = p + 100;
	t = rc.Height()*0.29;
	b = t + 20;
	s_order[6] = NewMyStatic(IDS_STATIC_ORDER_INF_7, status, CRect(p, t, q, b), 0);
	p = rc.Width()*0.29;
	q = p + 100;
	t = rc.Height()*0.29;
	b = t + 20;
	s_order[7] = NewMyStatic(IDS_STATIC_ORDER_INF_8, STATUS, CRect(p, t, q, b), 0);

	p = rc.Width()*0.29;
	q = p + 320;
	t = rc.Height()*0.34;
	b = t + 200;
	l_order = NewMyListCtrl(IDS_STATIC_ORDER_INF_9, CRect(p, t, q, b), 0);

	l_order->InsertColumn(0, _T("教材编号"), LVCFMT_LEFT, 100);
	l_order->InsertColumn(1, _T("名称"), LVCFMT_LEFT, 150);
	l_order->InsertColumn(2, _T("数量"), LVCFMT_LEFT, 70);

	int nRow;
	CString count;
	shop *pi = head;
	while (pi)
	{
		nRow = l_order->InsertItem(0, pi->m_num);//插入行
		l_order->SetItemText(nRow, 1, pi->m_name);//设置数据
		count.Format(_T("%d"),pi->count);
		l_order->SetItemText(nRow, 2, count);//设置数据
		pi = pi->next;
	}

	double sum = 0;
	pi = head;
	while (pi)
	{
		sum = sum + pi->price * pi->count;
		pi = pi->next;
	}
	CString sum_1;
	CString yuan("元");
	sum_1.Format(_T("%f"),sum);
	sum_1 = sum_1 + yuan;
	p = rc.Width()*0.79;
	q = p + 100;
	t = rc.Height()*0.34;
	b = t + 20;
	s_order[8] = NewMyStatic(IDS_STATIC_ORDER_INF_10, sum_1, CRect(p, t, q, b), 0);
	p = rc.Width()*0.73;
	q = p + 100;
	t = rc.Height()*0.34;
	b = t + 50;
	s_order[9] = NewMyStatic(IDS_STATIC_ORDER_INF_11, SUM, CRect(p, t, q, b), 0);

	p = rc.Width()*0.74;
	q = p + 100;
	t = rc.Height()*0.55;
	b = t + 40;
	b_order[0] = NewMyButton(IDS_BUTTON_ORDER_MAKESURE, CRect(p, t, q, b), 0);
	p = rc.Width()*0.74;
	q = p + 100;
	t = rc.Height()*0.65;
	b = t + 40;
	b_order[1] = NewMyButton(IDS_BUTTON_ORDER_CANCEL, CRect(p, t, q, b), 0);

}

void CDialog_user::OnClickMakesureOrder()
{
	_RecordsetPtr pRst;
	_RecordsetPtr pRst_1;
	char sql[255] = { 0 };
	char sql_1[255] = { 0 };
	USES_CONVERSION;

	if (false == bConn)
	{

		CString alter("数据库连接出错！");
		MessageBox(alter);

		OnClickCancelOrder();

	}

	CString num;
	CString sno;
	CString sum;

	s_order[0]->GetWindowText(num);
	s_order[4]->GetWindowText(sno);
	s_order[8]->GetWindowText(sum);

	num.Remove(' ');
	sno.Remove(' ');
	sum.Remove(' ');
//	sum.Right(4);
	CString time;
	time = GetTime();
	CString end("未结束");
	char *temp_1;
	char *temp_2;
	char *temp_3;
	char *temp_4;
	char *temp_5;
	temp_1 = T2A(num);
	temp_2 = T2A(sno);
	temp_3 = T2A(sum);
	temp_4 = T2A(time);
	temp_5 = T2A(end);
	sprintf_s(sql, "insert into SYS_ORDER(num,begindate,enddate,sno,status,sum) values('%s','%s','%s','%s','2','%s')", temp_1,temp_4,temp_5,temp_2,temp_3);
	pRst = dbOper.ExecuteWithResSQL(sql);

	char *temp_6;

	shop *p = head;
	CString m_num;
	CString m_name;
	while (p)
	{
		m_num = p->m_num;
		m_name = p->m_name;
		m_num.Remove(' ');
		m_name.Remove(' ');

		temp_2 = T2A(m_num);
		temp_6 = T2A(m_name);



		sprintf_s(sql_1, "insert into SYS_ORDER_M(num,bno,bname,qua) values('%s','%s','%s',%d)", temp_1, temp_2, temp_6, p->count);
		pRst_1 = dbOper.ExecuteWithResSQL(sql_1);
		p = p->next;
	}

	if (pRst == NULL)
		MessageBox(CString("1"));
	if (pRst_1 == NULL)
		MessageBox(CString("2"));

	if (pRst == NULL || pRst_1 == NULL)
	{
		CString alter("提交失败！！");
		MessageBox(alter);
	}
	if (pRst != NULL && pRst_1 != NULL)
	{
		MessageBox(CString("提交成功！！"));
		switchPages();
		head->empty(head);
		GetDlgItem(IDC_PERSONAL_INFORMATION_NORMAL)->EnableWindow(true);
		GetDlgItem(IDC_MATERIAL_PURCHASE)->EnableWindow(true);
		GetDlgItem(IDC_ORDER_FORM_CHECK)->EnableWindow(true);
		GetDlgItem(IDC_MAIL_CASE_NORMAL)->EnableWindow(true);
		OnBnClickedMaterialPurchase();

	}
}

void CDialog_user::OnClickCancelOrder()
{
	switchPages();
	head->empty(head);
	GetDlgItem(IDC_PERSONAL_INFORMATION_NORMAL)->EnableWindow(true);
	GetDlgItem(IDC_MATERIAL_PURCHASE)->EnableWindow(true);
	GetDlgItem(IDC_ORDER_FORM_CHECK)->EnableWindow(true);
	GetDlgItem(IDC_MAIL_CASE_NORMAL)->EnableWindow(true);
	OnBnClickedMaterialPurchase();
}

void CDialog_user::switchPages()
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
		if (l_materialInf[i])
		{
			l_materialInf[i]->DestroyWindow();
			delete l_materialInf[i];
			l_materialInf[i] = NULL;
		}
	}

	for (int i = 0; i < 5; i++)
	{
		if (s_materialInf[i])
		{
			s_materialInf[i]->DestroyWindow();
			delete s_materialInf[i];
			s_materialInf[i] = NULL;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (b_materialBuy[i])
		{
			b_materialBuy[i]->DestroyWindow();
			delete b_materialBuy[i];
			b_materialBuy[i] = NULL;
		}
	}

	for (int i = 0; i < 11; i++)
	{
		if (s_order[i])
		{
			s_order[i]->DestroyWindow();
			delete s_order[i];
			s_order[i] = NULL;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (b_order[i])
		{
			b_order[i]->DestroyWindow();
			delete b_order[i];
			b_order[i] = NULL;
		}
	}

	if (l_order)
	{
		l_order->DestroyWindow();
		delete l_order;
		l_order = NULL;
	}

	if (l_order_m)
	{
		l_order_m->DestroyWindow();
		delete l_order_m;
		l_order_m = NULL;
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


void CDialog_user::OnBnClickedChangepassword()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialog_changePassword a;
	a.DoModal();
}


void CDialog_user::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CString str_temp;

	str_temp = str;
	switch (nIDEvent)
	{
	case 1:
		if (!str.IsEmpty())
		{
			SetDlgItemText(IDC_NOTICE_2, str_temp);
			str_temp = str.Right(str.GetLength() - 2);
			str = str_temp;
		}
		else
		{
			str = NOTICE;
		}
		break;
	}

	CDialogEx::OnTimer(nIDEvent);

}
