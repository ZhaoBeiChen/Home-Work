// SetPara.cpp : 实现文件
//参数设置

#include "stdafx.h"
#include "0141121830_zhaobeichen.h"
#include "SetPara.h"
#include "afxdialogex.h"


// CSetPara 对话框

IMPLEMENT_DYNAMIC(CSetPara, CDialogEx)

CSetPara::CSetPara(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetPara::IDD, pParent)
	, Test_time(0)
	, Test_num(0)
	, Music_format(_T(""))
	, Max_speed(0)
	, Accrucy_weight(0)
	, Speed_weight(0)
{

}

CSetPara::~CSetPara()
{
}

void CSetPara::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TESTTIME, Test_time);
	DDV_MinMaxDouble(pDX, Test_time, 0.1, 100.0);
	DDX_Text(pDX, IDC_TESTNUM, Test_num);
	DDV_MinMaxInt(pDX, Test_num, 1, 100);
	DDX_CBString(pDX, IDC_MUSICFORMAT, Music_format);
	DDX_Text(pDX, IDC_MAXSPEED, Max_speed);
	DDV_MinMaxDouble(pDX, Max_speed, 1.0, 200.0);
	DDX_Text(pDX, IDC_ACCRUCYWEIGHT, Accrucy_weight);
	DDV_MinMaxDouble(pDX, Accrucy_weight, 0.0, 1.0);
	DDX_Text(pDX, IDC_SPEEDWEIGHT, Speed_weight);
	DDV_MinMaxDouble(pDX, Speed_weight, 0.0, 1.0);
	DDX_Control(pDX, IDC_MUSICFORMAT, Music_format_con);
}


BEGIN_MESSAGE_MAP(CSetPara, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSetPara::OnBnClickedOk)
END_MESSAGE_MAP()


// CSetPara 消息处理程序


BOOL CSetPara::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	Music_format_con.AddString("mp3");
	Music_format_con.AddString("wma");

	CString MS;
	CString PA;
	CString PS;
	CString TT;
	GetPrivateProfileString(_T("ExamInfo"), _T("total_minutes"), NULL, TT.GetBuffer(MAX_PATH), MAX_PATH, _T("..\\conf\\SET.ini"));
	MS.ReleaseBuffer();
	Test_time = atof(TT);


	Test_num = GetPrivateProfileInt(_T("ExamInfo"), _T("total_question"), 0, _T("..\\conf\\SET.ini"));

	GetPrivateProfileString(_T("ExamInfo"), _T("audio_format"), NULL, Music_format.GetBuffer(MAX_PATH), MAX_PATH, _T("..\\conf\\SET.ini"));
	Music_format.ReleaseBuffer();

	GetPrivateProfileString(_T("ExamInfo"), _T("max_speed"), NULL, MS.GetBuffer(MAX_PATH), MAX_PATH, _T("..\\conf\\SET.ini"));
	MS.ReleaseBuffer();
	Max_speed = _ttol(MS);

	GetPrivateProfileString(_T("ExamInfo"), _T("percentage_accuracy"), NULL, PA.GetBuffer(MAX_PATH), MAX_PATH, _T("..\\conf\\SET.ini"));
	PA.ReleaseBuffer();
	Accrucy_weight = atof(PA);

	GetPrivateProfileString(_T("ExamInfo"), _T("percentage_speed"), NULL, PS.GetBuffer(MAX_PATH), MAX_PATH, _T("..\\conf\\SET.ini"));
	PS.ReleaseBuffer();
	Speed_weight = atof(PS);

	UpdateData(FALSE);
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CSetPara::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (Accrucy_weight + Speed_weight == 1.0){
		CString temp;
		temp.Format("%f", Test_time);
		WritePrivateProfileString(_T("ExamInfo"), _T("total_minutes"), temp, _T("..\\conf\\SET.ini"));
		temp.Format("%d", Test_num);
		WritePrivateProfileString(_T("ExamInfo"), _T("total_question"), temp, _T("..\\conf\\SET.ini"));

		WritePrivateProfileString(_T("ExamInfo"), _T("audio_format"), Music_format, _T("..\\conf\\SET.ini"));
		temp.Format("%f", Max_speed);
		WritePrivateProfileString(_T("ExamInfo"), _T("max_speed"), temp, _T("..\\conf\\SET.ini"));
		temp.Format("%f", Accrucy_weight);
		WritePrivateProfileString(_T("ExamInfo"), _T("percentage_accuracy"), temp, _T("..\\conf\\SET.ini"));
		temp.Format("%f", Speed_weight);
		WritePrivateProfileString(_T("ExamInfo"), _T("percentage_speed"), temp, _T("..\\conf\\SET.ini"));
		MessageBox(CString("修改成功！！"));
	}
	else{
	
		MessageBox(CString("权重之和必须等于1！"));
	}
}
