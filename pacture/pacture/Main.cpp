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
	int len = strlen(pstr);//��ȡ����
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
	int key[] = { 1, 2, 3, 4, 5 };//�����ַ�
	char s[] = "��������3000�г������ǿ���ļ����ļ��м��ܹ��ܡ����ݱ������ܣ��ļ��С��ļ��ķ���ɾ���Լ��ļ���αװ�ȹ��ܡ�";
	char *p = s;
	cout << "����ǰ:" << p << endl;
	Makecode(s, key);//����
	cout << "���ܺ�:" << p << endl;
	Cutecode(s, key);//����
	cout << "���ܺ�:" << p << endl;
	*/


}