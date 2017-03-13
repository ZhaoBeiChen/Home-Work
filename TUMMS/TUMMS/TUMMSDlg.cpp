
// TUMMSDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TUMMS.h"
#include "TUMMSDlg.h"
#include "afxdialogex.h"
#include "Dialog_user.h"
#include "Dialog_manage.h"
#include "Dialog_admin.h"
#include<string>
#include<stdio.h>
using namespace std;

extern control CONTROL;
extern CDBOperation dbOper;
extern bool bConn;
extern CRect rc;
extern CString n_title;
extern CString n_content;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTUMMSDlg 对话框



CTUMMSDlg::CTUMMSDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTUMMSDlg::IDD, pParent)
	, userName(_T(""))
	, passWord(_T(""))
	, the_notice_title(_T(""))
	, the_notice_content(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	USER_ID = 0;
	userName = "";
	passWord = "";

}

void CTUMMSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_USERNAME, userName);
	DDV_MaxChars(pDX, userName, 100);
	DDX_Text(pDX, IDC_PASSWORD, passWord);
	DDV_MaxChars(pDX, passWord, 100);
	DDX_Text(pDX, IDC_STATIC_TITLE, the_notice_title);
	DDV_MaxChars(pDX, the_notice_title, 30);
	DDX_Text(pDX, IDC_NOTICE_1, the_notice_content);
	DDV_MaxChars(pDX, the_notice_content, 420);
}

BEGIN_MESSAGE_MAP(CTUMMSDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_NORMAL_USER, &CTUMMSDlg::OnBnClickedNormalUser)
	ON_BN_CLICKED(IDC_RADIO3, &CTUMMSDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_MANAGE_USER, &CTUMMSDlg::OnBnClickedManageUser)
	ON_BN_CLICKED(IDC_LAND_BUTTON, &CTUMMSDlg::OnBnClickedLandButton)
	ON_EN_CHANGE(IDC_PASSWORD, &CTUMMSDlg::OnEnChangePassword)
	ON_EN_CHANGE(IDC_USERNAME, &CTUMMSDlg::OnEnChangeUsername)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CTUMMSDlg 消息处理程序

BOOL CTUMMSDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	_RecordsetPtr pRst;
	char sql[255] = { 0 };
	strcpy_s(sql,"select * from SYS_NOTICE where status = '2'");
	pRst = dbOper.ExecuteWithResSQL(sql);

	if (pRst == NULL)
	{
		MessageBox(CString("公告显示错误！"));
	}
	else if (pRst->adoEOF)
	{
		the_notice_title = "无公告";
		the_notice_content = "无公告";
		n_title = the_notice_title;
		n_content = the_notice_content;
		UpdateData(false);
	}
	else
	{
		pRst->MoveFirst(); //记录集指针移动到查询结果集的前面
		_variant_t vTitle, vContent;
		while (!pRst->adoEOF)
		{

			vTitle = pRst->GetCollect(_variant_t("title"));

			vContent = pRst->GetCollect(_variant_t("content"));

			string title = (LPCSTR)_bstr_t(vTitle);
			string content = (LPCSTR)_bstr_t(vContent);

			CString title_1;
			CString content_1;

			title_1 = title.c_str();
			content_1 = content.c_str();

			title_1.Remove(' ');
			content_1.Remove(' ');

			the_notice_title = title_1;
			the_notice_content = content_1;
			n_title = the_notice_title;
			n_content = the_notice_content;
			UpdateData(false);
			pRst->MoveNext();

		}
	}

//	the_notice_title = n_title;
//	the_notice_content = n_content;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


void CTUMMSDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTUMMSDlg::OnPaint()
{
	CRect rect;
	CPaintDC dc(this);
	if (IsIconic())
	{
//		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}

	GetClientRect(&rect);
	CDC   dcMem;
	dcMem.CreateCompatibleDC(&dc);
	CBitmap   bmpBackground;
	bmpBackground.LoadBitmap(IDB_BITMAP2);


	BITMAP   bitmap;
	bmpBackground.GetBitmap(&bitmap);
	CBitmap   *pbmpOld = dcMem.SelectObject(&bmpBackground);
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0,
		bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);


}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTUMMSDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTUMMSDlg::OnBnClickedNormalUser()
{
	// TODO:  在此添加控件通知处理程序代码
	USER_ID = 1;
}


void CTUMMSDlg::OnBnClickedRadio3()
{
	// TODO:  在此添加控件通知处理程序代码
	USER_ID = 2;
}


void CTUMMSDlg::OnBnClickedManageUser()
{
	// TODO:  在此添加控件通知处理程序代码
	USER_ID = 3;
}


void CTUMMSDlg::OnBnClickedLandButton()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	if (USER_ID == 1)
	{
		if (userName == "" || passWord == "")
		{
			CString alter("请输入用户名或密码");
			MessageBox(alter);
		}
		else
		{
			Land land;
			if (land.check(userName, passWord, USER_ID))
			{
				CString a("1");
				CONTROL.land.Input_tag(a);
				CTUMMSDlg::OnOK();
				CDialog_user user;
				user.DoModal();
			}
			else
			{
				if (bConn == false)
				{
					CString alter_1("请检查网络连接！！");
					MessageBox(alter_1);
				}
				else
				{
					CString alter_1("用户名或密码错误！");
					MessageBox(alter_1);
				}
				CString p("");
				passWord = p;
				UpdateData(false);
			}
		}
	}
	else if (USER_ID == 3)
	{
		if (userName == "" || passWord == "")
		{
			CString alter("请输入用户名或密码");
			MessageBox(alter);
		}
		else
		{
			Land land;
			UpdateData(true);
			if (land.check(userName, passWord, USER_ID))
			{
				CString a("3");
				CONTROL.land.Input_tag(a);
				CTUMMSDlg::OnOK();
				CDialog_manage manage;
				manage.DoModal();
			}
			else
			{
				if (bConn == false)
				{
					CString alter_1("请检查网络连接！！");
					MessageBox(alter_1);
				}
				else
				{
					CString alter_1("用户名或密码错误！");
					MessageBox(alter_1);
				}
				CString p("");
				passWord = p;
				UpdateData(false);
			}
		}
	}
	else if (USER_ID == 2)
	{
		if (userName == "" || passWord == "")
		{
			CString alter("请输入用户名或密码");
			MessageBox(alter);
		}
		else
		{
			Land land;
			if (land.check(userName, passWord, USER_ID))
			{
				CString a("2");
				CONTROL.land.Input_tag(a);
				CTUMMSDlg::OnOK();
				CDialog_admin admin;
				admin.DoModal();
			}
			else
			{
				if (bConn == false)
				{
					CString alter_1("请检查网络连接！！");
					MessageBox(alter_1);
				}
				else
				{
					CString alter_1("用户名或密码错误！");
					MessageBox(alter_1);
				}
				CString p("");
				passWord = p;
				UpdateData(false);
			}
		}
	}
	else if (USER_ID == 0)
	{
		CString alter("请选择登陆身份！");
		MessageBox(alter);
	}
}





void CTUMMSDlg::OnEnChangePassword()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
//	CString hide("");
//	CString hides("*");
//	CString input;
//	input = passWord.Left(1);
//	password_hide = password_hide + input;
//	if (i > passWord.GetLength())
//	{
//		int i = passWord.GetLength();
//		for (int j = 0; j < i; j++)
//		{
//			hide = hide + hides;
//		}
//	}
//	passWord = hide;
	//MessageBox(password_hide);
//	UpdateData(false);
}

void Land::Input(CString userName, CString sex, CString tel, CString number)
{
	UserName = userName;
	Sex = sex;
	Tel = tel;
	Number = number;
}

void Land::Input_tag(CString TAG)
{
	tag = TAG;
}

bool Land::check(CString userName, CString passWord,int USER_ID)
{
//	CDBOperation dbOper;
//	bool bConn = dbOper.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "zbc", "666666");
	if (false == bConn)

	{

		//CString alter("数据库连接出错！");
		//MessageBox();

		return false;

	}

	_RecordsetPtr pRst;

	char sql[255] = { 0 };
	if (USER_ID == 1)
	{
		strcpy_s(sql, "select * from SYS_USER");
	}
	else if (USER_ID == 2)
	{
		strcpy_s(sql, "select * from SYS_ADMIN");
	}
	else if (USER_ID == 3)
	{
		strcpy_s(sql, "select * from SYS_MANAGE");
	}

	pRst = dbOper.ExecuteWithResSQL(sql);

	if (NULL == pRst)

	{


		//CString alter("查询数据出现错误！");
		//MessageBox();
		return false;

	}
	if (pRst->adoEOF)

	{

		pRst->Close();

		//CString alter("查询数据出现错误！");
		//MessageBox();

		return false;

	}

	pRst->MoveFirst(); //记录集指针移动到查询结果集的前面
	_variant_t vName, vPassword, vSex, vTel,vSno;
	while (!pRst->adoEOF)
	{

		

		if (USER_ID == 1)
		{
			vSno = pRst->GetCollect(_variant_t("sno"));

			vName = pRst->GetCollect(_variant_t("sname"));

			vPassword = pRst->GetCollect(_variant_t("password"));

			vSex = pRst->GetCollect(_variant_t("sex"));

			vTel = pRst->GetCollect(_variant_t("tel"));
		}
		else if (USER_ID == 3)
		{
			vSno = pRst->GetCollect(_variant_t("bmno"));

			vName = pRst->GetCollect(_variant_t("bmname"));

			vPassword = pRst->GetCollect(_variant_t("bmpassword"));

			vSex = pRst->GetCollect(_variant_t("bmsex"));

			vTel = pRst->GetCollect(_variant_t("bmtel"));
		}
		else if (USER_ID == 2)
		{
			vSno = pRst->GetCollect(_variant_t("mno"));

			vName = pRst->GetCollect(_variant_t("mname"));

			vPassword = pRst->GetCollect(_variant_t("mpassword"));

			vSex = pRst->GetCollect(_variant_t("msex"));

			vTel = pRst->GetCollect(_variant_t("mtel"));
		}

		//vDno = pRst->GetCollect("dno");

		//vDname = pRst->GetCollect("dname");

		//vCname = pRst->GetCollect("cname");

		string sno = (LPCSTR)_bstr_t(vSno);
		string name = (LPCSTR)_bstr_t(vName);
		string password = (LPCSTR)_bstr_t(vPassword);
		string sex = (LPCSTR)_bstr_t(vSex);
		string tel = (LPCSTR)_bstr_t(vTel);

		CString sno_1;
		CString name_1;
		CString password_1;
		CString sex_1;
		CString tel_1;
		sno_1 = sno.c_str();
		name_1 = name.c_str();
		password_1 = password.c_str();
		sex_1 = sex.c_str();
		tel_1 = tel.c_str();
		sno_1.Remove(' ');
		name_1.Remove(' ');
		password_1.Remove(' ');
		sex_1.Remove(' ');
		tel_1.Remove(' ');
		if (sno_1 == userName && passWord == password_1)
		{
			Number = sno_1;
			UserName = name_1;
			Sex = sex_1;
			Tel = tel_1;
			CONTROL.land.Input(UserName,Sex,Tel,Number);
			userName = "";
			passWord = "";
			return true;
		}

		pRst->MoveNext();

	}
	return false;
}


CString Land::returnUsername()
{
	return UserName;
}

CString Land::returnSex()
{
	return Sex;
}

CString Land::returnTel()
{
	return Tel;
}

CString Land::returnNumber()
{
	return Number;
}

CString Land::returnTag()
{
	return tag;
}


void CTUMMSDlg::OnEnChangeUsername()
{
	UpdateData(true);
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

HBRUSH CTUMMSDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH   hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		return   (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	return hBrush;
}
