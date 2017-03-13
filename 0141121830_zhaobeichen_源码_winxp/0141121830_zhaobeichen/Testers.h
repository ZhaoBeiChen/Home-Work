#pragma once
class Testers
{
	CString testNumber;				//准考证号码
	CString IDcardNumber;			//身份证号码
	int questionNumber;				//问题数
	CString stringOfTest;			//测试文本
	double accuracy;				//准确率
	double speed;					//速度
	double score;					//score
public:
	Testers();
	~Testers();
	//功能函数

	bool checkIDcardNumber();

	//以下是getter和setter函数的声明
	void setTestNumber(CString number);
	CString getTestNumber();

	void setIDcardNumber(CString number);
	CString getIDcardNumber();

	void setQuestionNumber(int number);
	int getQuestionNumber();

	void setStringOfTest(CString number);
	CString getStringOfTest();

	void setAccuracy(double number);
	double getAccuracy();

	void setSpeed(double number);
	double getSpeed();

	void setScore(double number);
	double getScore();
};

