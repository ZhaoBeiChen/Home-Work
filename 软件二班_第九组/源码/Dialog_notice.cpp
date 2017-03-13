// Dialog_notice.cpp : 实现文件
//

#include "stdafx.h"
#include "TUMMS.h"
#include "Dialog_notice.h"
#include "afxdialogex.h"
#include "DBOperation.h"
#include "Function.h"

extern control CONTROL;
extern CDBOperation dbOper;
extern bool bConn;
extern CRect rc;


// CDialog_notice 对话框

IMPLEMENT_DYNAMIC(CDialog_notice, CDialogEx)

CDialog_notice::CDialog_notice(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialog_notice::IDD, pParent)
	, notice_title(_T(""))
	, notice_content(_T(""))
{

}

CDialog_notice::~CDialog_notice()
{
}

void CDialog_notice::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, notice_title);
	DDV_MaxChars(pDX, notice_title, 30);
	DDX_Text(pDX, IDC_EDIT2, notice_content);
	DDV_MaxChars(pDX, notice_content, 420);
}


BEGIN_MESSAGE_MAP(CDialog_notice, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialog_notice::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDialog_notice 消息处理程序


void CDialog_notice::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	USES_CONVERSION;
	CString num;
	_RecordsetPtr pRst;
	char sql[255] = { 0 };
	if (notice_title != "" && notice_content != "")
	{
		CString count_1;
		strcpy_s(sql, "select count(num) count from SYS_NOTICE");
		pRst = dbOper.ExecuteWithResSQL(sql);
		if (NULL == pRst)
		{
			CString alter("查询数据出现错误！");
			CDialog_notice a;
			a.MessageBox(alter);
		}
		else if (pRst->adoEOF)
		{
			pRst->Close();
			CDialog_notice a;
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
					sprintf_s(sql_1, "select * from SYS_NOTICE where num = '%s'", temp);
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

		
		char* temp;
		char* temp_1;
		char* temp_2;
		char* temp_3;
		char* temp_4;
		CString time;
		time = GetTime();
		temp = T2A(num);
		temp_1 = T2A(CONTROL.land.returnNumber());
		temp_2 = T2A(time);
		temp_3 = T2A(notice_title);
		temp_4 = T2A(notice_content);
		sprintf_s(sql, "insert into SYS_NOTICE(num,sno,begindate,title,status,content) values('%s','%s','%s','%s','1','%s')", temp,temp_1,temp_2,temp_3,temp_4);
		pRst = dbOper.ExecuteWithResSQL(sql);

		if (pRst == NULL)
		{
			MessageBox(CString("添加失败，请检查数据库连接"));
		}
		else if (pRst != NULL)
		{
			MessageBox(CString("添加成功！"));
			CDialog_notice::OnOK();
		}
	}
	else
	{
		MessageBox(CString("标题或内容不能为空哦！"));
	}

}
