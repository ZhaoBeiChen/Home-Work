// Dialog_sendMail.cpp : 实现文件
//

#include "stdafx.h"
#include "TUMMS.h"
#include "Dialog_sendMail.h"
#include "afxdialogex.h"
#include<string>
using namespace std;

extern control CONTROL;
extern CDBOperation dbOper;
extern bool bConn;

// CDialog_sendMail 对话框

IMPLEMENT_DYNAMIC(CDialog_sendMail, CDialogEx)

CDialog_sendMail::CDialog_sendMail(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialog_sendMail::IDD, pParent)
	, Sender_num(_T(""))
	, Send_content(_T(""))
{

}

CDialog_sendMail::~CDialog_sendMail()
{
}

void CDialog_sendMail::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Sender_num);
	DDV_MaxChars(pDX, Sender_num, 30);
	DDX_Text(pDX, IDC_EDIT2, Send_content);
	DDV_MaxChars(pDX, Send_content, 420);
}


BEGIN_MESSAGE_MAP(CDialog_sendMail, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialog_sendMail::OnBnClickedButton1)
	ON_BN_CLICKED(IDCANCEL, &CDialog_sendMail::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDialog_sendMail 消息处理程序


void CDialog_sendMail::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	USES_CONVERSION;
	_RecordsetPtr pRst;
	char sql[255] = { 0 };
	char* temp;
	CString num;
	temp = T2A(Sender_num);

	sprintf_s(sql,"select * from SYS_USER where sno = '%s'", temp);

	pRst = dbOper.ExecuteWithResSQL(sql);

	if (pRst == NULL)
	{
		MessageBox(CString("数据库查询出错！"));
		CDialog_sendMail::OnCancel();
	}

	else if (pRst->adoEOF)
	{
		sprintf_s(sql, "select * from SYS_ADMIN where MNO = '%s'", temp);
		pRst = dbOper.ExecuteWithResSQL(sql);
		if (pRst == NULL)
		{
			MessageBox(CString("数据库查询出错！"));
			CDialog_sendMail::OnCancel();
		}
		if (pRst->adoEOF)
		{
			sprintf_s(sql, "select * from SYS_MANAGE where BMNO = '%s'", temp);
			pRst = dbOper.ExecuteWithResSQL(sql);
			if (pRst == NULL)
			{
				MessageBox(CString("数据库查询出错！"));
				CDialog_sendMail::OnCancel();
			}
			if (pRst->adoEOF)
			{
				MessageBox(CString("该联系人不存在！"));
			}
			else
			{
				CString count_1;
				strcpy_s(sql, "select count(mno) count from SYS_MAIL");
				pRst = dbOper.ExecuteWithResSQL(sql);
				if (NULL == pRst)
				{
					CString alter("查询数据出现错误！");
					CDialog_sendMail a;
					a.MessageBox(alter);
				}
				else if (pRst->adoEOF)
				{
					pRst->Close();
					CDialog_sendMail a;
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


				char* temp_1;
				char* temp_2;
				char* temp_3;
				char* temp_4;
				temp_1 = T2A(CONTROL.land.returnNumber());
				temp_2 = T2A(CONTROL.land.returnUsername());
				temp_3 = T2A(num);
				temp_4 = T2A(Send_content);
				sprintf_s(sql, "insert into SYS_MAIL(mno,sender,receiver,content,sender_name,ifread) values('%s','%s','%s','%s','%s','1')", temp_3, temp_1, temp, temp_4, temp_2);
				pRst = dbOper.ExecuteWithResSQL(sql);

				if (pRst != NULL)
				{
					MessageBox(CString("发送成功！"));
					CDialog_sendMail::OnOK();
				}
				else
				{
					MessageBox(CString("发送失败"));
					CDialog_sendMail::OnCancel();
				}
			}
		}
		else
		{
			CString count_1;
			strcpy_s(sql, "select count(mno) count from SYS_MAIL");
			pRst = dbOper.ExecuteWithResSQL(sql);
			if (NULL == pRst)
			{
				CString alter("查询数据出现错误！");
				CDialog_sendMail a;
				a.MessageBox(alter);
			}
			else if (pRst->adoEOF)
			{
				pRst->Close();
				CDialog_sendMail a;
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


			char* temp_1;
			char* temp_2;
			char* temp_3;
			char* temp_4;
			temp_1 = T2A(CONTROL.land.returnNumber());
			temp_2 = T2A(CONTROL.land.returnUsername());
			temp_3 = T2A(num);
			temp_4 = T2A(Send_content);
			sprintf_s(sql, "insert into SYS_MAIL(mno,sender,receiver,content,sender_name,ifread) values('%s','%s','%s','%s','%s','1')", temp_3, temp_1, temp, temp_4, temp_2);
			pRst = dbOper.ExecuteWithResSQL(sql);

			if (pRst != NULL)
			{
				MessageBox(CString("发送成功！"));
				CDialog_sendMail::OnOK();
			}
			else
			{
				MessageBox(CString("发送失败"));
				CDialog_sendMail::OnCancel();
			}
		}
	}
	else
	{
		
		CString count_1;
		strcpy_s(sql, "select count(mno) count from SYS_MAIL");
		pRst = dbOper.ExecuteWithResSQL(sql);
		if (NULL == pRst)
		{
			CString alter("查询数据出现错误！");
			CDialog_sendMail a;
			a.MessageBox(alter);
		}
		else if (pRst->adoEOF)
		{
			pRst->Close();
			CDialog_sendMail a;
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


		char* temp_1;
		char* temp_2;
		char* temp_3;
		char* temp_4;
		temp_1 = T2A(CONTROL.land.returnNumber());
		temp_2 = T2A(CONTROL.land.returnUsername());
		temp_3 = T2A(num);
		temp_4 = T2A(Send_content);
		sprintf_s(sql, "insert into SYS_MAIL(mno,sender,receiver,content,sender_name,ifread) values('%s','%s','%s','%s','%s','1')", temp_3,temp_1,temp,temp_4,temp_2);
		pRst = dbOper.ExecuteWithResSQL(sql);

		if (pRst != NULL)
		{
			MessageBox(CString("发送成功！"));
			CDialog_sendMail::OnOK();
		}
		else
		{
			MessageBox(CString("发送失败"));
			CDialog_sendMail::OnCancel();
		}
	}

}


void CDialog_sendMail::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
