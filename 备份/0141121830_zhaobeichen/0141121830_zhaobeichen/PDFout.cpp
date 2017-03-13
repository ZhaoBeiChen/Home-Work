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

//PDF���
int PDFout::CreatePDF(Testers Person,CString testContext,CString testNum)
{
	PDF *p = PDF_new();
	PDF_set_parameter(p, "license", "X600605-009100-4E7661-329E0C");//ȥ��ˮӡ����ע���д�롣
	int font_ch;
	CString fileName("Score\\Score_");
	CString _pdf(".pdf");
	fileName = fileName + testNum + _pdf;//f�ļ������֣��Լ�·��
	PDF_begin_document(p, fileName, 0, "");
	PDF_set_parameter(p, "hypertextencoding", "host");
	PDF_set_info(p, "Creator", "0141121830");
	PDF_set_info(p, "Author", "TestPDF");
	PDF_set_info(p, "Title", "Score");
	PDF_begin_page_ext(p, a4_width, a4_height, "");
	font_ch = PDF_load_font(p, "STSong-Light", 0, "GB-EUC-H", "");
	PDF_setfont(p, font_ch, 8);
	PDF_set_text_pos(p, 50, 700);

	CString snum("׼��֤�ţ�");
	CString sID("���֤�ţ�");
	CString sc;
	CString st;
	CString fuhao;


	fuhao = "%";
	snum = snum + Person.getTestNumber();
	sID = sID + Person.getIDcardNumber();
	sc.Format("׼ȷ���ǣ�%.2f%s,�ٶ���:%.2f����/����,���ο��Եĳɼ���%.2f",Person.getAccuracy() * 100, fuhao, Person.getSpeed(), Person.getScore());
	st = "�����������ο���¼������ݣ�";
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
			b1 += testContext.Mid(k, 2);//ÿ�ζ���һ������
			k = k + 2;
		}
		PDF_set_text_pos(p, 50, len);//��PDF����ʾ��λ��
		PDF_show(p, (_bstr_t)b1);//��ʾ
		int o = b1.GetLength();//��������
		if (o>70) //����70������������
		{
			len -= 20; b1.Empty();
		}
	}
	PDF_end_page_ext(p, "");
	PDF_end_document(p, "");
	PDF_delete(p);
	return 0;
}
