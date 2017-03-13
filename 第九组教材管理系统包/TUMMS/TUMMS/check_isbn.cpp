#include "stdafx.h"
#include "Function.h"
#include <afx.h>


bool check_isbn(CString temp)
{
	int n = 0;
	int m = 0;
	for (int i = 0; i < temp.GetLength(); i++)
	{
		int code = (int)temp.GetAt(i);
		if (code >= '0' && code <= '9')
		{
			n = n + 1;
		}
		if (code == '-')
		{
			m = m + 1;
		}
	}
	if (n == temp.GetLength()-4 && m == 4)
		return true;
	else return false;
}