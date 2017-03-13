#pragma comment(lib, "PDFlib\pdflib.lib")
#include "stdafx.h"
#include "PDFout.h"
#include "PDFlib\pdflib.h"
#include "afxdialogex.h"
#include<string>
#include "Testers.h"
PDFout::PDFout()
{
}


PDFout::~PDFout()
{
}

//PDF输出
int PDFout::CreatePDF(Testers Person,CString testContext,CString testNum)
{
	PDF *p = PDF_new();
	PDF_set_parameter(p, "license", "X600605-009100-4E7661-329E0C");//去除水印。将注册号写入。
	int font_ch;
	CString fileName("Score\\Score_");
	CString _pdf(".pdf");
	fileName = fileName + testNum + _pdf;//f文件的名字，以及路径
	PDF_begin_document(p, fileName, 0, "");
	PDF_set_parameter(p, "hypertextencoding", "host");
	PDF_set_info(p, "Creator", "0141121830");
	PDF_set_info(p, "Author", "TestPDF");
	PDF_set_info(p, "Title", "Score");
	PDF_begin_page_ext(p, a4_width, a4_height, "");
	font_ch = PDF_load_font(p, "STSong-Light", 0, "GB-EUC-H", "");
	PDF_setfont(p, font_ch, 8);
	PDF_set_text_pos(p, 50, 700);

	CString snum("准考证号：");
	CString sID("身份证号：");
	CString sc;
	CString st;
	CString fuhao;


	fuhao = "%";
	snum = snum + Person.getTestNumber();
	sID = sID + Person.getIDcardNumber();
	sc.Format("准确率是：%.2f%s,速度是:%.2f个字/分钟,本次考试的成绩是%.2f",Person.getAccuracy() * 100, fuhao, Person.getSpeed(), Person.getScore());
	st = "以下是您本次考试录入的内容：";
	PDF_show(p, snum);
	PDF_continue_text(p, sID);
	PDF_continue_text(p, sc);
	PDF_continue_text(p, st);

	int m = testContext.GetLength();
	int k, j = 0, len = 660;
	CString b1 = "";
	for (k = 0; k<m;)
	{
		char unicode = testContext.GetAt(k);
		if (unicode >= '!'&&unicode <= '~')
		{
			b1 += testContext.GetAt(k);
			k++;
		}
		else
		{
			b1 += testContext.Mid(k, 2);//每次读进一个汉字
			k = k + 2;
		}
		PDF_set_text_pos(p, 50, len);//在PDF中显示的位置
		PDF_show(p, (_bstr_t)b1);//显示
		int o = b1.GetLength();//读出长度
		if (o>70) //大于70换行重新输入
		{
			len -= 20; b1.Empty();
		}
	}
	PDF_end_page_ext(p, "");
	PDF_end_document(p, "");
	PDF_delete(p);
	return 0;
}
