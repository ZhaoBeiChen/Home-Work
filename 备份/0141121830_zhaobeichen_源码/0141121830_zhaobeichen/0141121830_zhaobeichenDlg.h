
// 0141121830_zhaobeichenDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "Testers.h"


// CMy0141121830_zhaobeichenDlg �Ի���
class CMy0141121830_zhaobeichenDlg : public CDialogEx
{
// ����
public:
	CMy0141121830_zhaobeichenDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY0141121830_ZHAOBEICHEN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedPrintScorePaper();
	//����
	Testers Person;
	// ׼��֤��
	CString Admissino_number;
	afx_msg void OnBnClickedStartTest();
	// ���֤��
	CString IDcard_number;
	// ������
	CString Question_number;
	afx_msg void OnCbnSelchangeTestNumber();
	CComboBox Control_testNumber_combobox;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	// ������Ϣ��ʾ
	CString Test_info;
	//��ʱ������
	void Timer();
	//ʱ��
	int times;
	//��Ƶ����
	void OnPlay();
	//��ȡ��Ƶ�ļ�ʱ��
	DWORD getinfo(UINT wDeviceID, DWORD item);
	//��Ƶ����ֹͣ
	void OnStop();
	//������ʼ��
	void InitInfo();
	//�������
	int QuestionNum;
	//��Ƶ�ļ��ĸ�ʽ
	CString MusicFormat;
	//���¼���ٶ�
	double MAXspeed;
	//¼���ٶ�Ȩ��
	double SpeedWeight;
	//׼ȷ��Ȩ��
	double AccuracyWeight;
	//��Ƶ·������
	CString MusicPath;
	//��ȡ����ʱ��
	int UseTime;
	// ��������
	CString TestContent;
	afx_msg void OnBnClickedLock();
	//�����־λ
	bool error;
};
