#pragma once
#include "afxwin.h"


// CSetPara �Ի���

class CSetPara : public CDialogEx
{
	DECLARE_DYNAMIC(CSetPara)

public:
	CSetPara(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetPara();

// �Ի�������
	enum { IDD = IDD_SET_PARA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ����ʱ��
	double Test_time;
	// ��������
	int Test_num;
	// ��Ƶ��ʽ
	CString Music_format;
	// ���¼���ٶ�
	double Max_speed;
	// ׼ȷ��Ȩ��
	double Accrucy_weight;
	// �ٶ�Ȩ��
	double Speed_weight;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	// Control_of_MF
	CComboBox Music_format_con;
};
