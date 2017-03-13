#include "stdafx.h"
#include "Encryption.h"
#include<iostream>
#include<bitset>
#include<fstream>
using std::bitset;
using namespace std;
extern CString workPath;

Encryption::Encryption()
{
}


Encryption::~Encryption()
{
}


char Encryption::MakecodeChar(char c, int key){
	return c = c^key;
}

char Encryption::CutcodeChar(char c, int key){
	return c^key;
}
void Encryption::Makecode(char *pstr, int *pkey){
	int len = strlen(pstr);//获取长度
	for (int i = 0; i<len; i++)
		*(pstr + i) = MakecodeChar(*(pstr + i), pkey[i % 5]);
}

void Encryption::Cutecode(char *pstr, int *pkey){
	int len = strlen(pstr);
	for (int i = 0; i<len; i++)
		*(pstr + i) = CutcodeChar(*(pstr + i), pkey[i % 5]);
}

//加密
void Encryption::OnEncryption(CString path,CString newFileName, CString Format){

	int key[] = { 1, 2, 3, 4, 5 };
	CFile file;
	file.Open(path, CFile::modeRead);
	int size;
	size = file.GetLength();
	char *buf = new char[size + 1];
	buf[size] = 0;
	file.Read(buf, size);
	file.Close();

	Makecode(buf,key);
	
	CString len;
	len = buf;
	CString p;
	p = workPath;
	CString _mp3("\\mp3\\");
	CString _wma("\\wma\\");

	if (Format == "mp3"){
		p = p + _mp3;
	}
	else if(Format == "wma"){
	
		p = p + _wma;
	}
	CString _txt(".txt");
	newFileName = p + newFileName + _txt;

	CFile newFile;
	newFile.Open(newFileName, CFile::modeCreate | CFile::modeWrite);
	newFile.Write(buf,len.GetLength());
	newFile.Close();


}
//解密
CString Encryption::UnEncryption(char * buf){

	int key[] = { 1, 2, 3, 4, 5 };
	Cutecode(buf,key);

	CString answer;
	answer = buf;
	return answer;
}