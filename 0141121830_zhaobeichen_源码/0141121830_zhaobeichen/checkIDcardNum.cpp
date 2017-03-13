#include "stdafx.h"
#include "checkIDcardNum.h"


checkIDcardNum::checkIDcardNum()
{
	
}


checkIDcardNum::~checkIDcardNum()
{
}
//��֤���֤��
bool checkIDcardNum::getValidateCode(CString id18){

	int weight[17] = { 7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2 };   //ʮ��λ���ֱ�����Ȩ��
	char validate[11] = { '1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2' };    //mod11,��ӦУ�����ַ�ֵ 

	CString id17 = id18.Left(17);
	CString Check = id18.Right(1);
	int sum = 0;
	int mode = 0;
	for (int i = 0; i < id17.GetLength(); i++){
	
		char a = id17.GetAt(i);
		int temp = a - 48;
		sum = sum + temp * weight[i];
	}
	mode = sum % 11;
	return (validate[mode] == Check.GetAt(0));
}
//��֤���֤��18λ
bool checkIDcardNum::IfID18(CString id18){

	if (id18.GetLength() == 18){
	
		return true;
	}
	else return false;
}
//��֤׼��֤��10λ
bool checkIDcardNum::IfTID18(CString tid10){

	if (tid10.GetLength() == 10){

		return true;
	}
	else return false;
}
