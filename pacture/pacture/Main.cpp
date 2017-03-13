#include<iostream>
#include<ctime>
using namespace std;

void Makecode(char *pstr, int *pkey);
void Cutecode(char *pstr, int *pkey);

char MakecodeChar(char c, int key){
	return c = c^key;
}

char CutcodeChar(char c, int key){
	return c^key;
}
void Makecode(char *pstr, int *pkey){
	int len = strlen(pstr);//获取长度
	for (int i = 0; i<len; i++)
		*(pstr + i) = MakecodeChar(*(pstr + i), pkey[i % 5]);
}

void Cutecode(char *pstr, int *pkey){
	int len = strlen(pstr);
	for (int i = 0; i<len; i++)
		*(pstr + i) = CutcodeChar(*(pstr + i), pkey[i % 5]);
}



int main()
{
	/*
	int key[] = { 1, 2, 3, 4, 5 };//加密字符
	char s[] = "超级加密3000有超快和最强的文件、文件夹加密功能、数据保护功能，文件夹、文件的粉碎删除以及文件夹伪装等功能。";
	char *p = s;
	cout << "加密前:" << p << endl;
	Makecode(s, key);//加密
	cout << "加密后:" << p << endl;
	Cutecode(s, key);//解密
	cout << "解密后:" << p << endl;
	*/


}