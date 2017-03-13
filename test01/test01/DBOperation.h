#pragma once
#import "c:/Program Files/Common Files/System/ado/msado15.dll" no_namespace rename("EOF","adoEOF")

#include<stdio.h>
#include<windows.h>

class CDBOperation
{
public:
	CDBOperation(void);
	~CDBOperation(void);
	bool ConnToDB(char *ConnectionString, char *UserID, char *Password);

	_RecordsetPtr ExecuteWithResSQL(const char *);
	//bool ExecuteNoResSQL(const char *); // delete and add

private:
	void PrintErrorInfo(_com_error &);

private:
	_ConnectionPtr CreateConnPtr();
	_CommandPtr CreateCommPtr();
	_RecordsetPtr CreateRecsetPtr();

private:
	_ConnectionPtr m_pConnection;
	_CommandPtr m_pCommand;
};