// Dialog_changePassword.cpp : 实现文件
//

#include "stdafx.h"
#include "TUMMS.h"
#include "Dialog_changePassword.h"
#include "afxdialogex.h"
#include<string>
using namespace std;

extern control CONTROL;
extern CDBOperation dbOper;
extern bool bConn;
extern CRect rc;

// CDialog_changePassword 对话框

IMPLEMENT_DYNAMIC(CDialog_changePassword, CDialogEx)

CDialog_changePassword::CDialog_changePassword(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialog_changePassword::IDD, pParent)
	, old_password(_T(""))
	, new_password(_T(""))
	, makesure_password(_T(""))
{

}

CDialog_changePassword::~CDialog_changePassword()
{
}

void CDialog_changePassword::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, old_password);
	DDV_MaxChars(pDX, old_password, 100);
	DDX_Text(pDX, IDC_EDIT2, new_password);
	DDV_MaxChars(pDX, new_password, 100);
	DDX_Text(pDX, IDC_EDIT3, makesure_password);
	DDV_MaxChars(pDX, makesure_password, 100);
}


BEGIN_MESSAGE_MAP(CDialog_changePassword, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialog_changePassword::OnBnClickedButton1)
END_MESSAGE_MAP()




// CDialog_changePassword 消息处理程序


void CDialog_changePassword::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	if (old_password != "" || new_password != "" || makesure_password != "")
	{
		USES_CONVERSION;
		_RecordsetPtr pRst;
		char sql[255] = { 0 };
		char *temp;
		temp = T2A(CONTROL.land.returnNumber());
		if (CONTROL.land.returnTag() == "1")
		{
			sprintf_s(sql, "select * from SYS_USER where sno = '%s'", temp);
			pRst = dbOper.ExecuteWithResSQL(sql);
			if (pRst == NULL)
			{
				MessageBox(CString("数据库查询错误！"));
				CDialog_changePassword::OnCancel();
			}
			else
			{
				_variant_t vPassword;
				pRst->MoveFirst();
				while(!pRst->adoEOF)
				{
					vPassword = pRst->GetCollect(_variant_t("password"));

					string password = (LPCSTR)_bstr_t(vPassword);

					CString password_1;

					password_1 = password.c_str();

					password_1.Remove(' ');

					if (password_1 == old_password)
					{
						char* temp_2;
						temp_2 = T2A(new_password);
						if (check())
						{
							_RecordsetPtr pRst_1;
							sprintf_s(sql, "update SYS_USER set password = '%s' where sno = '%s'", temp_2,temp);
							pRst_1 = dbOper.ExecuteWithResSQL(sql);
							if (pRst_1 == NULL)
							{
								MessageBox(CString("数据库修改失败！"));
								CDialog_changePassword::OnCancel();
							}
							else
							{
								MessageBox(CString("修改成功！"));
								CDialog_changePassword::OnOK();
							}
						}
						else
						{
							MessageBox(CString("新密码与确认密码不一致！"));
						}
					}
					else
					{
						MessageBox(CString("旧密码输入错误!"));
					}
					pRst->MoveNext();
				}
			}
		}
		else if (CONTROL.land.returnTag() == "2")
		{
			sprintf_s(sql, "select * from SYS_ADMIN where mno = '%s'", temp);
			pRst = dbOper.ExecuteWithResSQL(sql);
			if (pRst == NULL)
			{
				MessageBox(CString("数据库查询错误！"));
				CDialog_changePassword::OnCancel();
			}
			else
			{
				_variant_t vPassword;
				pRst->MoveFirst();
				while (!pRst->adoEOF)
				{
					vPassword = pRst->GetCollect(_variant_t("mpassword"));

					string password = (LPCSTR)_bstr_t(vPassword);

					CString password_1;

					password_1 = password.c_str();

					password_1.Remove(' ');

					if (password_1 == old_password)
					{
						char* temp_2;
						temp_2 = T2A(new_password);
						if (check())
						{
							_RecordsetPtr pRst_1;
							sprintf_s(sql, "update SYS_ADMIN set mpassword = '%s' where mno = '%s'", temp_2, temp);
							pRst_1 = dbOper.ExecuteWithResSQL(sql);
							if (pRst_1 == NULL)
							{
								MessageBox(CString("数据库修改失败！"));
								CDialog_changePassword::OnCancel();
							}
							else
							{
								MessageBox(CString("修改成功！"));
								CDialog_changePassword::OnOK();
							}
						}
						else
						{
							MessageBox(CString("新密码与确认密码不一致！"));
						}
					}
					else
					{
						MessageBox(CString("旧密码输入错误!"));
					}
					pRst->MoveNext();
				}
			}
		}
		else if (CONTROL.land.returnTag() == "3")
		{
			sprintf_s(sql, "select * from SYS_MANAGE where bmno = '%s'", temp);
			pRst = dbOper.ExecuteWithResSQL(sql);
			if (pRst == NULL)
			{
				MessageBox(CString("数据库查询错误！"));
				CDialog_changePassword::OnCancel();
			}
			else
			{
				_variant_t vPassword;
				pRst->MoveFirst();
				while (!pRst->adoEOF)
				{
					vPassword = pRst->GetCollect(_variant_t("bmpassword"));

					string password = (LPCSTR)_bstr_t(vPassword);

					CString password_1;

					password_1 = password.c_str();

					password_1.Remove(' ');

					if (password_1 == old_password)
					{
						char* temp_2;
						temp_2 = T2A(new_password);
						if (check())
						{
							_RecordsetPtr pRst_1;
							sprintf_s(sql, "update SYS_MANAGE set bmpassword = '%s' where bmno = '%s'", temp_2, temp);
							pRst_1 = dbOper.ExecuteWithResSQL(sql);
							if (pRst_1 == NULL)
							{
								MessageBox(CString("数据库修改失败！"));
								CDialog_changePassword::OnCancel();
							}
							else
							{
								MessageBox(CString("修改成功！"));
								CDialog_changePassword::OnOK();
							}
						}
						else
						{
							MessageBox(CString("新密码与确认密码不一致！"));
						}
					}
					else
					{
						MessageBox(CString("旧密码输入错误!"));
					}
					pRst->MoveNext();
				}
			}
		}
	}
}

bool CDialog_changePassword::check()
{
	UpdateData(true);
	if (makesure_password == new_password)
		return true;
	else return false;
}
