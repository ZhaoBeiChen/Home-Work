#pragma once
#include<bitset>
using std::bitset;
class Encryption
{
public:
	Encryption();
	~Encryption();

	void OnEncryption(CString path,CString,CString);
	CString UnEncryption(char *);
	char MakecodeChar(char, int);
	char CutcodeChar(char, int);
	void Makecode(char *, int *);
	void Cutecode(char *, int *);
};

