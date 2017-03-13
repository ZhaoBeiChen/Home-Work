
// encryptionDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "encryption.h"
#include "encryptionDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CencryptionDlg �Ի���



CencryptionDlg::CencryptionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CencryptionDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CencryptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CencryptionDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_encryption, &CencryptionDlg::OnBnClickedencryption)
	ON_BN_CLICKED(IDC_JIEMI, &CencryptionDlg::OnBnClickedJiemi)
END_MESSAGE_MAP()


// CencryptionDlg ��Ϣ�������

BOOL CencryptionDlg::OnInitDialog()
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CencryptionDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CencryptionDlg::OnPaint()
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
HCURSOR CencryptionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CencryptionDlg::OnBnClickedencryption()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CFile file;

	file.Open(_T("..\\answer\\2.txt"), CFile::modeRead);
	int size;
	size = file.GetLength();
	char *buf = new char[size + 1];
	buf[size] = 0;
	file.Read(buf, size);
	CString Answer(buf);
	MessageBox(Answer);
	delete buf;
	file.Close();
	/*
	for (int i = 0; i < Answer.GetLength(); i++)
	{
		CString d;
		d = buf[i];
		MessageBox(d);
	}*/
	
	

//	file.Open(_T("..\\answer\\1.txt"), CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate, NULL);
//	file.Write(Answer, Answer.GetLength());
}


void CencryptionDlg::OnBnClickedJiemi()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CFile file;
	CString Answer;
	file.Open(_T("..\\answer\\2.txt"), CFile::modeRead);
	int size;
	size = file.GetLength();
	char *buf = new char[size + 1];
	buf[size] = 0;
	file.Read(buf, size);
	file.Close();

	for (int i = 0; i < Answer.GetLength(); i++)
	{
		buf[i] = buf[i] - 5;
	}
	Answer = buf;

	file.Open(_T("..\\answer\\1.txt"), CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate, NULL);
	file.Write(Answer, Answer.GetLength());
}
