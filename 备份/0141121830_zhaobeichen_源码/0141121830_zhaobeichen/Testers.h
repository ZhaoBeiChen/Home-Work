#pragma once
class Testers
{
	CString testNumber;				//׼��֤����
	CString IDcardNumber;			//���֤����
	int questionNumber;				//������
	CString stringOfTest;			//�����ı�
	double accuracy;				//׼ȷ��
	double speed;					//�ٶ�
	double score;					//score
public:
	Testers();
	~Testers();
	//���ܺ���

	bool checkIDcardNumber();

	//������getter��setter����������
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

