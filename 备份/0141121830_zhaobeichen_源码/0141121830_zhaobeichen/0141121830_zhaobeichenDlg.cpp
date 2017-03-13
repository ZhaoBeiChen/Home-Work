
// 0141121830_zhaobeichenDlg.cpp : ʵ���ļ�
//������
#pragma   comment(lib, "winmm.lib")
#include "stdafx.h"
#include "0141121830_zhaobeichen.h"
#include "0141121830_zhaobeichenDlg.h"
#include "afxdialogex.h"
#include "Testers.h"
#include "checkIDcardNum.h"
#include "Function.h"
#include<Mmsystem.h>
#include "CalScore.h"
#include "Encryption.h"
#include "PDFout.h"
#include "EncryptionDialog.h"
#include "Set.h"
#include "Alert_01.h"
#include "Alert_02.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

MCI_OPEN_PARMS Music = { 0 };
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
	
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMy0141121830_zhaobeichenDlg �Ի���



CMy0141121830_zhaobeichenDlg::CMy0141121830_zhaobeichenDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy0141121830_zhaobeichenDlg::IDD, pParent)
	, Admissino_number(_T(""))
	, IDcard_number(_T(""))
	, Question_number(_T(""))
	, Test_info(_T(""))
	, TestContent(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy0141121830_zhaobeichenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ADMISSION_NUMBER, Admissino_number);
	DDX_Text(pDX, IDC_IDCARD_NUMBER, IDcard_number);
	DDX_Text(pDX, IDC_TEST_NUMBER, Question_number);
	DDX_Control(pDX, IDC_TEST_NUMBER, Control_testNumber_combobox);
	DDX_Text(pDX, IDC_MESSAGEOFTEST, Test_info);
	DDX_Text(pDX, IDC_THESTRINGOFTEST, TestContent);
}

BEGIN_MESSAGE_MAP(CMy0141121830_zhaobeichenDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMy0141121830_zhaobeichenDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMy0141121830_zhaobeichenDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_StartTest, &CMy0141121830_zhaobeichenDlg::OnBnClickedStartTest)
	ON_CBN_SELCHANGE(IDC_TEST_NUMBER, &CMy0141121830_zhaobeichenDlg::OnCbnSelchangeTestNumber)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_PRINT_SCORE_PAPER, &CMy0141121830_zhaobeichenDlg::OnBnClickedPrintScorePaper)
	ON_BN_CLICKED(IDC_LOCK, &CMy0141121830_zhaobeichenDlg::OnBnClickedLock)
END_MESSAGE_MAP()


// CMy0141121830_zhaobeichenDlg ��Ϣ�������

BOOL CMy0141121830_zhaobeichenDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	InitInfo();
	GetDlgItem(IDOK)->EnableWindow(false);
	GetDlgItem(IDC_PRINT_SCORE_PAPER)->EnableWindow(false);
	GetDlgItem(IDC_LOCK)->EnableWindow(false);
	GetDlgItem(IDC_THESTRINGOFTEST)->EnableWindow(false);
	error = true;
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMy0141121830_zhaobeichenDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMy0141121830_zhaobeichenDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMy0141121830_zhaobeichenDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMy0141121830_zhaobeichenDlg::InitInfo(){

	//��ȡ�����ļ�����
	CString minutes;
	CString MS;
	CString PA;
	CString PS;
	GetPrivateProfileString(_T("ExamInfo"), _T("total_minutes"), NULL, minutes.GetBuffer(MAX_PATH), MAX_PATH, _T("..\\conf\\SET.ini"));
	minutes.ReleaseBuffer();

	double tim = atof(minutes);

	times = tim * 60.0;

	QuestionNum = GetPrivateProfileInt(_T("ExamInfo"), _T("total_question"), 0, _T("..\\conf\\SET.ini"));

	GetPrivateProfileString(_T("ExamInfo"), _T("audio_format"), NULL, MusicFormat.GetBuffer(MAX_PATH) ,MAX_PATH , _T("..\\conf\\SET.ini"));
	MusicFormat.ReleaseBuffer();

	GetPrivateProfileString(_T("ExamInfo"), _T("max_speed"), NULL, MS.GetBuffer(MAX_PATH), MAX_PATH, _T("..\\conf\\SET.ini"));
	MS.ReleaseBuffer();
	MAXspeed = _ttol(MS);

	GetPrivateProfileString(_T("ExamInfo"), _T("percentage_accuracy"), NULL, PA.GetBuffer(MAX_PATH), MAX_PATH, _T("..\\conf\\SET.ini"));
	PA.ReleaseBuffer();
	AccuracyWeight = atof(PA);

	GetPrivateProfileString(_T("ExamInfo"), _T("percentage_speed"), NULL, PS.GetBuffer(MAX_PATH), MAX_PATH, _T("..\\conf\\SET.ini"));
	PS.ReleaseBuffer();
	SpeedWeight = atof(PS);

	//��ʼ���ؼ��Ͳ��ֱ���
	for (int i = 1; i <= QuestionNum; i++)
	{
		CString d;
		d.Format("%d",i);
		Control_testNumber_combobox.AddString(d);
	}
	Test_info = "��������ȷ�Ŀ�����Ϣ��ѡ���⣬�������ʼ���ԡ���ʼ������";
	if (MusicFormat == "mp3"){
		MusicPath = "..\\re\\mp3\\";
	}
	else if (MusicFormat == "wma"){
	
		MusicPath = "..\\re\\wma\\";
	}
	Admissino_number = "";
	IDcard_number = "";
	Question_number = "";
	UseTime = times;
	UpdateData(false);
}


void CMy0141121830_zhaobeichenDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (times != 0){
		CAlert_02 alert;
		alert.DoModal();
		if (!alert.returnChose()){
		
			return;
		}
	}
	if (TestContent != "")
	{
		Test_info = "���ύ��������ӡ�ɼ�������ɼ����ɼ��ļ��ڳ���Ŀ¼�µ�Score�ļ�����";
		UpdateData(false);
		OnStop();
		UpdateData(true);
		GetDlgItem(IDCANCEL)->EnableWindow(true);
		GetDlgItem(IDC_PRINT_SCORE_PAPER)->EnableWindow(true);
		GetDlgItem(IDC_THESTRINGOFTEST)->EnableWindow(false);
		GetDlgItem(IDOK)->EnableWindow(false);
		KillTimer(1);
		UseTime = UseTime - times - 1;
		CalScore check;
		check.InitAnswer(Question_number, MusicFormat);  //��ʼ��CalScore����
		check.ChenkAccurcy(TestContent);  //����׼ȷ��
		check.CalSpeed(TestContent, MAXspeed, UseTime);
		check.Calscore(SpeedWeight, AccuracyWeight);
		check.OutScore(Person);
	}
	else{
	
		Test_info = "δ��⵽���룬���������˳�ϵͳ�������ϵͳ������֪ͨ������Ա";
		UpdateData(false);
		KillTimer(1);
		OnStop();
		GetDlgItem(IDCANCEL)->EnableWindow(true);
		GetDlgItem(IDC_THESTRINGOFTEST)->EnableWindow(false);
	}
	

//	CDialogEx::OnOK();
}


void CMy0141121830_zhaobeichenDlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	OnStop();
	CDialogEx::OnCancel();
}


void CMy0141121830_zhaobeichenDlg::OnBnClickedStartTest()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//�����������󣬲���ȡ��Ϣ
	CAlert_01 alert;
	alert.DoModal();
	if (alert.returnChose())
	{
		UpdateData(true);
		Person.setTestNumber(Admissino_number);
		Person.setIDcardNumber(IDcard_number);
		int i = _ttoi(Question_number);
		Person.setQuestionNumber(i);

		if (Admissino_number != "" && IDcard_number != "" && Question_number != "")
		{
			if (MusicFormat == "mp3")
			{
				CString f(".mp3");
				MusicPath = MusicPath + Question_number + f;
			}
			else if (MusicFormat == "wma")
			{
				CString f(".wma");
				MusicPath = MusicPath + Question_number + f;
			}

			if (Person.checkIDcardNumber()){

				GetDlgItem(IDC_ADMISSION_NUMBER)->EnableWindow(false);
				GetDlgItem(IDC_IDCARD_NUMBER)->EnableWindow(false);
				GetDlgItem(IDC_StartTest)->EnableWindow(false);
				GetDlgItem(IDCANCEL)->EnableWindow(false);
				GetDlgItem(IDC_TEST_NUMBER)->EnableWindow(false);
				GetDlgItem(IDOK)->EnableWindow(true);
				GetDlgItem(IDC_THESTRINGOFTEST)->EnableWindow(true);
				OnPlay();
				if (error){
					Timer();
				}
				else return;

			}
			else if (Person.getIDcardNumber() == "000000")
			{
				GetDlgItem(IDC_LOCK)->EnableWindow(true);
			}
			else
			{
				MessageBox(CString("������Ϣ��ʽ�������飡"));
				if (MusicFormat == "mp3"){
					MusicPath = "..\\re\\mp3\\";
				}
				else if (MusicFormat == "wma"){

					MusicPath = "..\\re\\wma\\";
				}
			}
		}
		else {

			MessageBox(CString("��������Ϊ�գ������Ƿ���û����д��ѡ�����Ϣ"));
			if (MusicFormat == "mp3"){
				MusicPath = "..\\re\\mp3\\";
			}
			else if (MusicFormat == "wma"){

				MusicPath = "..\\re\\wma\\";
			}
		}
	}
}


void CMy0141121830_zhaobeichenDlg::OnCbnSelchangeTestNumber()            //���ѡ��
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
}


void CMy0141121830_zhaobeichenDlg::OnTimer(UINT_PTR nIDEvent)    //��ʱ��
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	UpdateData(true);
	if (times != 0){
	
		Test_info = "����ʱ�仹ʣ��";
		Test_info = Test_info + GetTime(times);
		GetDlgItem(IDC_MESSAGEOFTEST)->SetWindowTextA(Test_info);
		times--;
	}
	else{
	
		Test_info = "ʱ�䵽��";
		UpdateData(true);
		GetDlgItem(IDCANCEL)->EnableWindow(true);
		GetDlgItem(IDC_PRINT_SCORE_PAPER)->EnableWindow(true);
		GetDlgItem(IDC_THESTRINGOFTEST)->EnableWindow(false);
		GetDlgItem(IDOK)->EnableWindow(true);
		KillTimer(1);
		UseTime = UseTime - times - 1;
		OnBnClickedOk();
	}


//	UpdateData(false);
	CDialogEx::OnTimer(nIDEvent);
}
//��ʱ��
void CMy0141121830_zhaobeichenDlg::Timer(){

	SetTimer(1,1000,NULL);
	UpdateData(false);
}


void CMy0141121830_zhaobeichenDlg::OnPlay(){

	DWORD MusicLen;
	Music.dwCallback = NULL;
	Music.lpstrAlias = NULL;
	Music.lpstrDeviceType = _T("MPEGAudio");
	Music.lpstrElementName = MusicPath;
	Music.wDeviceID = NULL;
	UINT rs;
	rs = mciSendCommand(NULL,MCI_OPEN,MCI_OPEN_ELEMENT,(DWORD)&Music);
	mciSendCommand(NULL,MCI_SET,MCI_SET_DOOR_OPEN,NULL);
	MusicLen = getinfo(Music.wDeviceID,MCI_STATUS_LENGTH);
	if (rs == 0){
		MCI_PLAY_PARMS pp;
		pp.dwCallback = NULL;
		pp.dwFrom = 0;
		mciSendCommand(Music.wDeviceID,MCI_PLAY,MCI_NOTIFY,(DWORD)&pp);
	}
	else{
	
		CString d;
		d.Format(_T("%d"),rs);
		if (d == "275")
		{
			error = false;
			MessageBox(CString("�޷��ҵ����ļ���"));
			GetDlgItem(IDCANCEL)->EnableWindow(true);
			return;
		}
		else if (d == "277")
		{
			error = false;
			MessageBox(CString("���ļ������ã�"));
			GetDlgItem(IDCANCEL)->EnableWindow(true);
			return;
		}
		OnBnClickedOk();
	}
	
}

DWORD CMy0141121830_zhaobeichenDlg::getinfo(UINT wDeviceID, DWORD item){

	MCI_STATUS_PARMS mcistatusparms;
	mcistatusparms.dwCallback = (DWORD)GetSafeHwnd();
	mcistatusparms.dwItem = item;
	mcistatusparms.dwReturn = 0;
	mciSendCommand(wDeviceID,MCI_STATUS,MCI_STATUS_ITEM,(DWORD)&mcistatusparms);
	return mcistatusparms.dwReturn;
}

void CMy0141121830_zhaobeichenDlg::OnStop(){

	MCI_GENERIC_PARMS gp;
	gp.dwCallback = NULL;
	mciSendCommand(Music.wDeviceID,MCI_CLOSE,MCI_WAIT,(DWORD)&gp);
}



void CMy0141121830_zhaobeichenDlg::OnBnClickedPrintScorePaper()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	PDFout temp;
	temp.CreatePDF(Person,TestContent);
	ShellExecute(NULL, "open", "..\\Score\\Score.pdf", NULL, NULL, SW_SHOWNORMAL);

}


void CMy0141121830_zhaobeichenDlg::OnBnClickedLock()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CSet dia;
	dia.DoModal();
}
