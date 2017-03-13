

#include "stdafx.h"
#include "Function.h"
#include <afx.h>


bool check_number(CString temp)
{
	int n = 0;
	for (int i = 0; i < temp.GetLength(); i++)
	{
		int code = (int)temp.GetAt(i);
		if (code >= '0' && code <= '9')
		{
			n = n + 1;
		}
	}
	if (n == temp.GetLength())
		return true;
	else return false;
}