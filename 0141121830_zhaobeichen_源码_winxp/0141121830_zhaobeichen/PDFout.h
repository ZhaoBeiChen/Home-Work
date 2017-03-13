#pragma once
#include "stdafx.h"
#include "PDFout.h"
#include "Testers.h"
class PDFout
{
public:
	PDFout();
	~PDFout();
	int CreatePDF(Testers,CString);
};

