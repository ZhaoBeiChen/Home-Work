#include "DBOperation.h"
#include<iostream>
#include<stdio.h>
#include<string>
using namespace std;

void main(){
	CDBOperation dbOper;
	bool bConn = dbOper.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=localhost)", "zzz", "123456");
	if (false == bConn)

	{

		printf("�������ݿ���ִ���\n");

		system("PAUSE");

		return;

	}

	_RecordsetPtr pRst;

	char sql[255] = { 0 };

	strcpy_s(sql, "select * from SYS_USER");

	pRst = dbOper.ExecuteWithResSQL(sql);

	if (NULL == pRst)

	{

		printf("��ѯ���ݳ��ִ���\n");

		system("PAUSE");

		return;

	}
	if (pRst->adoEOF)

	{

		pRst->Close();

		printf("There is no records in this table\n");

		return;

	}
	else
	{

		_variant_t vSno, vName;
		while (!pRst->adoEOF)

		{

			//pRst->MoveFirst(); //��¼��ָ���ƶ�����ѯ�������ǰ��

			vSno = pRst->GetCollect(_variant_t("sno"));

			vName = pRst->GetCollect(_variant_t("sname"));

			//vDno = pRst->GetCollect("dno");

			//vDname = pRst->GetCollect("dname");

			//vCname = pRst->GetCollect("cname");

			string sno = (LPCSTR)_bstr_t(vSno);
			string name = (LPCSTR)_bstr_t(vName);


			cout << "." << sno << "." << name << ".";


			pRst->MoveNext();

		}
	}

}
