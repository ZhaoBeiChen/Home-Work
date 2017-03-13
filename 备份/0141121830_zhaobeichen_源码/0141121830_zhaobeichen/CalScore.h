#pragma once
#include "afxwin.h"
#include "stdafx.h"
#include "Testers.h"
class CalScore
{
	CString Answer;
	double Accuracy;
	double Speed;
	double Score;
public:
	CalScore();
	~CalScore();
	void InitAnswer(CString,CString);
	void ChenkAccurcy(CString testStr);
	void CalSpeed(CString testStr, double MAXspeed, int UseTime);
	void Calscore(double SpeedWeight, double AccuracyWeight);
	void  OutScore(Testers &one);
};

