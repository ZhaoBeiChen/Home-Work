#pragma once
#include<string>
using namespace std;
class checkIDcardNum
{
public:
	checkIDcardNum();
	~checkIDcardNum();

	bool getValidateCode(CString id17);
	bool IfID18(CString id18);
	bool IfTID18(CString Tid10);
};

