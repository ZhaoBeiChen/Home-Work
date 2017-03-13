#include "stdafx.h"
#include "CalScore.h"
#include "afxwin.h"
#include<iostream>
#include "Encryption.h"

CalScore::CalScore()
{
}


CalScore::~CalScore()
{
}
//将答案解密并赋给成员变量
void CalScore::InitAnswer(CString Question_number,CString format){

	CString path;
	if (format == "mp3"){
		path = "..\\answer\\mp3\\";
	}
	else if (format == "wma"){
	
		path = "..\\answer\\wma\\";
	}
	CString _txt(".txt");
	path = path + Question_number + _txt;
	CFile file;
	file.Open(path, CFile::modeRead);
	int size;
	size = file.GetLength();
	char *buf = new char[size + 1];
	buf[size] = 0;
	file.Read(buf,size);

	Encryption lock;
	Answer = lock.UnEncryption(buf);

	delete buf;
	file.Close();
}
//计算准确率
void CalScore::ChenkAccurcy(CString testStr){


	int strA = Answer.GetLength();
	int strT = testStr.GetLength();

	int **dif = new int*[strA+1];
	for (int i = 0; i < strA + 1; i++)
		dif[i] = new int[strT+1];

	for (int a = 0; a <= strA; a++)
		dif[a][0] = a;
	for (int a = 0l; a <= strT; a++)
		dif[0][a] = a;

	int temp;
	for (int i = 1; i <= strA; i++){
	
		for (int j = 1; j <= strT; j++){
		
			if (Answer.GetAt(i - 1) == testStr.GetAt(j - 1)){
			
				temp = 0;
			}
			else{
			
				temp = 1;
			}

			dif[i][j] = min(min(dif[i - 1][j - 1] + temp, dif[i][j - 1] + 1), dif[i - 1][j] + 1);

		}
	}

	Accuracy = 1 - (float)dif[strA][strT] / max(strA,strT);
}

//计算速度
void CalScore::CalSpeed(CString testStr, double MAXspeed, int UseTime){


	CStringW str(testStr);
	int Len = str.GetLength();
	double Minutes = (double)UseTime / 60.000;
	double m = (double)(Len / Minutes);
	if (m < MAXspeed){
	
		Speed = Len / Minutes;
	}
	else Speed = MAXspeed;
}
//计算得分
void CalScore::Calscore( double SpeedWeight, double AccuracyWeight){

	
	Score = (AccuracyWeight * Accuracy * 100.00) + SpeedWeight * Speed;
}
//输出成绩
void CalScore::OutScore(Testers & one){

	one.setAccuracy(Accuracy);
	one.setSpeed(Speed);
	one.setScore(Score);
}