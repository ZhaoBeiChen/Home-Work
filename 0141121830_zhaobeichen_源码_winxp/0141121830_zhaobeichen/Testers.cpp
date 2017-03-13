#include "stdafx.h"
#include "Testers.h"
#include "checkIDcardNum.h"
//用户类
Testers::Testers()
{
	testNumber = "";
	IDcardNumber = "";
	questionNumber = 0;
	stringOfTest = "";
	accuracy = 0.0;
	speed = 0.0;
	score = 0.0;
}


Testers::~Testers()
{
}

//以下是功能函数

bool Testers::checkIDcardNumber(){

	checkIDcardNum check;
	return check.getValidateCode(IDcardNumber) && check.IfID18(IDcardNumber) && check.IfTID18(testNumber);
}

//以下是所有属性的getter和setter函数
void Testers::setTestNumber(CString number){

	testNumber = number;
}
CString Testers::getTestNumber(){

	return testNumber;
}

void Testers::setIDcardNumber(CString number){

	IDcardNumber = number;
}
CString Testers::getIDcardNumber(){

	return IDcardNumber;
}

void Testers::setQuestionNumber(int number){

	questionNumber = number;
}
int  Testers::getQuestionNumber(){

	return questionNumber;
}

void Testers::setStringOfTest(CString test_string){

	stringOfTest = test_string;
}
CString Testers::getStringOfTest(){

	return stringOfTest;
}

void Testers::setAccuracy(double number){

	accuracy = number;
}
double Testers::getAccuracy(){

	return accuracy;
}

void Testers::setSpeed(double spd){

	speed = spd;
}
double Testers::getSpeed(){

	return speed;
}

void Testers::setScore(double sco){

	score = sco;
}
double Testers::getScore(){

	return score;
}
