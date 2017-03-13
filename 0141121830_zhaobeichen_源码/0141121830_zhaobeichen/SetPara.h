#pragma once
#include "afxwin.h"


// CSetPara 对话框

class CSetPara : public CDialogEx
{
	DECLARE_DYNAMIC(CSetPara)

public:
	CSetPara(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetPara();

// 对话框数据
	enum { IDD = IDD_SET_PARA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 考试时间
	double Test_time;
	// 考题数量
	int Test_num;
	// 音频格式
	CString Music_format;
	// 最大录入速度
	double Max_speed;
	// 准确率权重
	double Accrucy_weight;
	// 速度权重
	double Speed_weight;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	// Control_of_MF
	CComboBox Music_format_con;
};
