
// 0141121830_zhaobeichenDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "Testers.h"


// CMy0141121830_zhaobeichenDlg 对话框
class CMy0141121830_zhaobeichenDlg : public CDialogEx
{
// 构造
public:
	CMy0141121830_zhaobeichenDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY0141121830_ZHAOBEICHEN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedPrintScorePaper();
	//考生
	Testers Person;
	// 准考证号
	CString Admissino_number;
	afx_msg void OnBnClickedStartTest();
	// 身份证号
	CString IDcard_number;
	// 考题编号
	CString Question_number;
	afx_msg void OnCbnSelchangeTestNumber();
	CComboBox Control_testNumber_combobox;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	// 考试信息显示
	CString Test_info;
	//计时器函数
	void Timer();
	//时间
	int times;
	//音频播放
	void OnPlay();
	//获取音频文件时长
	DWORD getinfo(UINT wDeviceID, DWORD item);
	//音频播放停止
	void OnStop();
	//参数初始化
	void InitInfo();
	//考题个数
	int QuestionNum;
	//音频文件的格式
	CString MusicFormat;
	//最大录入速度
	double MAXspeed;
	//录入速度权重
	double SpeedWeight;
	//准确率权重
	double AccuracyWeight;
	//音频路径变量
	CString MusicPath;
	//获取消耗时间
	int UseTime;
	// 测试内容
	CString TestContent;
	afx_msg void OnBnClickedLock();
	//错误标志位
	bool error;
};
