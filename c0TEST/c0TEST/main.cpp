#include<stdio.h>
#include"c0.h"
#include"string.h"
void init()
{
	int i;
	for (i = 0; i <= 255; i++)
	{
		ssym[i] = nul; //ssym�����ַ��ķ���ֵ  
	}
	err = 0;                                           //�����������0 
	cc = cx = ll = 0;
	ch = ' ';
	ptx = 0;
	pdx = 0;
	cx = 0;
	ls = 1;
	ssym['+'] = plus;
	ssym['-'] = minus;
	ssym['*'] = times;
	ssym['/'] = slash;
	ssym['('] = lparen;
	ssym['='] = becomes;
	ssym[')'] = rparen;
	ssym[','] = comma;
	ssym['{'] = lbrace;
	ssym['}'] = rbrace;
	ssym[';'] = semicolon;
	/*���ñ���������,������ĸ˳��,�����۰����*/

	strcpy_s(&(word[0][0]),10, "else");
	strcpy_s(&(word[1][0]),10, "if");
	strcpy_s(&(word[2][0]),10, "int");
	strcpy_s(&(word[3][0]),10, "main");
	strcpy_s(&(word[4][0]),10, "printf");
	strcpy_s(&(word[5][0]),10, "return");
	strcpy_s(&(word[6][0]),10, "scanf");
	strcpy_s(&(word[7][0]),10, "void");
	strcpy_s(&(word[8][0]),10, "while");
	/*���ñ����ַ���*/
	wsym[0] = elsesym;
	wsym[1] = ifsym;
	wsym[2] = intsym;
	wsym[3] = mainsym;
	wsym[4] = printfsym;
	wsym[5] = returnsym;
	wsym[6] = scanfsym;
	wsym[7] = voidsym;
	wsym[8] = whilesym;

	/*����ָ������*/
	strcpy_s(&(mnemonic[lit][0]),5, "lit");
	strcpy_s(&(mnemonic[ret][0]),5, "ret");
	strcpy_s(&(mnemonic[lod][0]),5, "lod");
	strcpy_s(&(mnemonic[sto][0]),5, "sto");
	strcpy_s(&(mnemonic[cal][0]),5, "cal");
	strcpy_s(&(mnemonic[inte][0]),5, "int");
	strcpy_s(&(mnemonic[jmp][0]),5, "jmp");
	strcpy_s(&(mnemonic[jpc][0]),5, "jpc");
	strcpy_s(&(mnemonic[red][0]),5, "red");
	strcpy_s(&(mnemonic[wrt][0]),5, "wrt");
	strcpy_s(&(mnemonic[add][0]),5, "add");
	strcpy_s(&(mnemonic[sub][0]),5, "sub");
	strcpy_s(&(mnemonic[div][0]),5, "div");
	strcpy_s(&(mnemonic[mul][0]),5, "mul");


}
void error(int n)
{
	char space[81];
	memset(space, 32, 81); printf("-------%c\n", ch);
	space[cc - 1] = 0;//����ʱ��ǰ�����Ѿ����꣬����cc-1
	printf("****%s!%d\n", space, n);
	err++;
	while (ch != '\n')
		getch();
}
void getch()
{
	if (cc == ll)
	{
		if (feof(fin))
		{
			return;
		}
		ll = 0;
		cc = 0;
		printf("%d  ", ls);
		ls++;
		//		fprintf(fa1,"%d ",cx);
		ch = ' ';
		while (ch != 10)
		{
			//fscanf(fin,"%c",&ch)
			if (EOF == fscanf_s(fin, "%c", &ch))
			{
				line[ll] = 0;
				break;
			}
			printf("%c", ch);
			//			fprintf(fa1,"%c",ch);
			line[ll] = ch;
			ll++;
		}
		printf("\n");
		//		fprintf(fa1,"\n");
	}
	ch = line[cc];
	cc++;
}

/*�ʷ���������ȡһ������        ����ͼP19
*/

void getsym()
{
	int i, j, k;
	while (ch == ' ' || ch == 10 || ch == 9)  //���Կո񡢻��С�TAB 
	{
		getch();     //getchdo :if(-1==getch())return -1
	}
	if (ch >= 'a'&&ch <= 'z')
	{
		k = 0;
		do{
			if (k<al)
			{
				a[k] = ch;
				k++;
			}
			getch();
		} while (ch >= 'a'&&ch <= 'z' || ch >= '0'&&ch <= '9');
		a[k] = 0;
		strcpy_s(id, a);
		i = 0;
		j = norw - 1;
		do{
			k = (i + j) / 2;
			if (strcmp(id, word[k]) <= 0)
			{
				j = k - 1;
			}
			if (strcmp(id, word[k]) >= 0)
			{
				i = k + 1;
			}

		} while (i <= j);
		if (i - 1>j)
		{
			sym = wsym[k];
		}
		else
		{
			sym = ident;
		}
	}
	else
	{
		if (ch >= '0'&&ch <= '9')
		{
			k = 0;
			num = 0;
			sym = number;
			do{
				num = 10 * num + ch - '0';
				k++;
				getch();
			} while (ch >= '0'&&ch <= '9'); /*��ȡ���ֵ�ֵ*/
			k--;
			if (k>nmax)
			{
				error(1);
			}
		}
		else
		{
			sym = ssym[ch];/* �����Ų�������������ʱ��ȫ�����յ��ַ��Ŵ���*/
			getch();
		}
	}
}
int gen(enum fct x, int y, int z)
{
	if (cx >= cxmax)
	{
		printf("Program too long"); /*�������*/
		return -1;
	}
	code[cx].f = x;
	code[cx].l = y;
	code[cx].a = z;
	cx++;
	return 0;
}
void enter(int lev, int pdx)
{
	ptx++;
	strcpy_s(table[ptx].name, id);       /*ȫ�ֱ���id���Ѵ��е�ǰ���ֵ�����*/
	table[ptx].kind = k;

	switch (k)
	{
	case intfun:                      /*��������*/
		table[ptx].level = 0;
		table[ptx].adr = pdx;
		break;
	case variable:                     /*��������*/
		table[ptx].level = lev;
		table[ptx].adr = pdx;
		pdx++;
		break;                          /*��������*/
	case voidfun:
		table[ptx].level = 0;
		table[ptx].adr = pdx;
		break;
	}

}
int paren()
{
	if (sym == lparen)
	{
		getsym();
		if (sym != rparen)
		{
			error(3);
		}
	}
	else
	{
		error(2);
	}
	getsym();
	return 0;
}
//

int position(char * idt)
{
	int i;
	strcpy_s(table[0].name, idt);
	i = ptx;
	while (strcmp(table[i].name, idt) != 0)
	{
		i--;
	}
	return i;
}

void glintcl()
{
	int i = 1;
	k = variable;
	enter(1, pdx);
	pdx++;
	while (sym == comma)
	{
		getsym();
		if (sym == ident)
		{
			k = variable;
			enter(1, pdx);
			pdx++;
			i++;
			getsym();
		}
	}
	if (sym == semicolon)
	{
		code[0].a = code[0].a + i;
		getsym();
		return;
	}
	else
	{
		error(4);
	}
}

void intcl()
{
	int i = 1;

	if (sym == ident)
	{
		k = variable;
		enter(0, pdx);
		pdx++;
		getsym();
		while (sym == comma)
		{
			getsym();
			if (sym == ident)
			{
				k = variable;
				enter(0, pdx);
				pdx++;
				i++;
				getsym();
			}
		}
		if (sym == semicolon)
		{
			gen(inte, 0, i);
			getsym();
			return;
		}
		else
		{
			error(4);
		}
	}
	else
	{
		error(6);
	}
}
void funcl()
{
	gen(inte, 0, 2);
	while (sym == intsym)
	{
		getsym();
		intcl();
	}
	while (sym != rbrace)
	{
		statement();
	}
	gen(ret, 0, 0);
	getsym();
}
int block()
{
	int cx1;
	int flag = 0;
	cx = 0;
	gen(inte, 0, 3);
	//
	//
	cx1 = cx;
	gen(cal, 0, 0);
	while (!feof(fin))//�ļ�����
	{
		if (sym == intsym)
		{
			pdx = 2;
			getsym();
			if (sym == ident)
			{
				getsym();

				if (sym != lparen)//ȫ�ֱ�������
				{
					pdx = 3;
					glintcl();
				}
				else
				{
					k = intfun;
					enter(0, cx);
					getsym();
					if (sym == rparen)
					{
						getsym();
						if (sym == lbrace)//�����ڲ�����
						{
							getsym();
							funcl();
						}
					}
					else
					{
						error(3);
					}
				}
			}
			else
			{
				error(6);
			}
		}
		else if (sym == voidsym)
		{
			pdx = 2;
			getsym();
			if (sym == ident)
			{
				getsym();
				k = voidfun;
				enter(0, cx);
				paren();
				if (sym == lbrace)
				{
					getsym();
					funcl();
				}
				else
					error(13);
			}
			else if (sym == mainsym)
			{
				if (flag == 1)
				{
					error(5);
					continue;
				}
				flag = 1;
				getsym();
				paren();
				if (sym == lbrace)
				{
					code[cx1].a = cx;
					getsym();
					funcl();
				}
			}
			else
			{
				error(6);
			}
		}
		else if (sym == ident)
		{
			error(4);
		}
		else
		{
			error(4);
			getsym();
		}
	}
	if (flag == 0)
		error(7);
}


void statement()
{
	int i;
	if (sym == ident)
	{
		i = position(id);
		if (i == 0)
		{
			error(8);
		}
		else if (table[i].kind != variable&&table[i].kind != voidfun)
		{
			error(9);
			i = 0;
		}
		else if (table[i].kind == variable)
		{
			getsym();
			if (sym == becomes)
			{
				getsym();
			}
			else
			{
				error(10);
			}
			expression();
			if (i != 0)
			{
				gen(sto, table[i].level, table[i].adr);
			}
			if (sym == semicolon)
			{
				getsym();
			}
			//getsym();
		}
		else if (table[i].kind == voidfun)
		{
			getsym();
			if (table[i].kind == voidfun)
			{
				gen(cal, 0, table[i].adr);  /*����callָ��*/
			}
			else
			{
				error(11);
			}
			paren();
			if (sym == semicolon)
			{
				getsym();
			}
			else
			{
				error(12);
			}
		}
	}
	else if (sym == scanfsym)
	{
		getsym();
		if (sym == lparen)
		{
			getsym();
			if (sym == ident)
			{
				i = position(id);
				if (i == 0)
				{
					error(4);
				}
				else
				{
					gen(red, 0, 0);
					gen(sto, table[i].level, table[i].adr);	/* ���浽����*/
					getsym();
					if (sym == rparen)
					{
						getsym();
						if (sym == semicolon)
						{
							getsym();
						}
						else
						{
							error(12);
						}
					}
					else
					{
						error(3);
					}
				}
			}
			else
			{
				error(6);

			}
		}
		else
		{
			error(2);
		}
	}
	else if (sym == printfsym)
	{
		getsym();
		if (sym == lparen)
		{
			getsym();
			expression();/* ���ñ��ʽ�����˴���read��ͬ��readΪ��������ֵ*/
			gen(wrt, 0, 0);/* �������ָ����ջ����ֵ*/
			//			getsym();
			if (sym == rparen)
			{
				getsym();
				if (sym == semicolon)
				{
					getsym();
				}
				else
				{
					error(12);
				}
			}
			else
			{
				error(3);
			}
		}
		else
		{
			error(2);
		}
	}
	else if (sym == ifsym)
	{
		getsym();
		ifcl();

	}
	else if (sym == whilesym)
	{
		getsym();
		whilecl();

	}
	else if (sym == returnsym)
	{
		getsym();
		expression();
		gen(sto, 1, 0);

		if (sym == semicolon)
		{
			getsym();
		}
		else
		{
			error(12);
		}
	}
}
void whilecl()
{
	int cx1, cx2;
	if (sym == lparen)
	{
		getsym();
		cx2 = cx;
		expression();
		cx1 = cx;
		gen(jpc, 0, 0);
		if (sym == rparen)
		{
			getsym();
			if (sym == lbrace)
			{
				getsym();
				while (sym != rbrace)
				{
					statement();
				}
				getsym();
			}
			else
			{
				statement();
			}
			code[cx1].a = cx + 1;
			gen(jmp, 0, cx2);
		}
		else
		{
			error(3);
		}
	}
}
void ifcl()
{
	int cx1;
	if (sym == lparen)
	{
		getsym();
		expression();
		cx1 = cx;
		gen(jpc, 0, 0);

		if (sym == rparen)
		{
			getsym();
			if (sym == lbrace)
			{
				getsym();
				while (sym != rbrace)
				{
					statement();
				}
				getsym();
			}
			else
			{
				statement();
			}
			code[cx1].a = cx;
			if (sym == elsesym)
			{
				code[cx1].a = cx + 1;
				cx1 = cx;
				gen(jmp, 0, 0);

				getsym();
				if (sym == lbrace)
				{
					getsym();
					while (sym != rbrace)
					{
						statement();
					}
					getsym();
				}
				else
				{
					statement();
				}
				code[cx1].a = cx;
			}

		}
		else
		{
			error(3);
		}

	}
	else
		error(2);
}
void expression()
{
	enum symbol addop;
	if (sym == plus || sym == minus)             /*��ͷ�������ţ���ʱ��ǰ���ʽ������һ�����Ļ򸺵���*/
	{
		addop = sym;                    /*���濪ͷ��������*/
		getsym();
		if (addop == minus)
		{
			gen(lit, 0, 0);
		}
		term();                /*������*/
		if (addop == minus)				//////////////////!!!!!!!���������ſ�ͷ�ı��ʽ!!!!!!!!////////////
		{
			gen(sub, 0, 0);
		}
	}
	else                             /*��ʱ���ʽ��������ļӼ�*/
	{
		term();            /*������*/
	}
	while (sym == plus || sym == minus)
	{
		addop = sym;
		getsym();
		term();              /*������*/
		if (addop == plus)
		{
			gen(add, 0, 0);                    /*���ɼӷ�ָ��*/
		}
		else
		{
			gen(sub, 0, 0);                /*���ɼ���ָ��*/
		}
	}
}
void term()
{
	enum symbol mulop;               /*���ڱ���˳�������*/
	factor();       /*��������*/
	while (sym == times || sym == slash)
	{
		mulop = sym;
		getsym();
		factor();
		if (mulop == times)
		{
			gen(mul, 0, 0);          /*���ɳ˷�ָ��*/
		}
		else
		{
			gen(div, 0, 0);           /*���ɳ���ָ��*/
		}
	}
}
void factor()
{
	int i;
	if (sym == ident)
	{
		i = position(id);        /*��������*/
		if (i == 0)
		{
			error(8);               /*��ʶ��δ����*/
		}
		else
		{
			switch (table[i].kind)
			{
			case variable:
				gen(lod, table[i].level, table[i].adr);
				getsym();
				break;
			case intfun:
				gen(cal, 0, table[i].adr);
				gen(lod, 1, 0);
				getsym();
				paren();
				break;
			case voidfun:
				error(2);
				getsym();
				break;
			}
		}

	}
	else if (sym == number)
	{
		if (num>amax)
		{
			error(1);
			num = 0;
		}
		gen(lit, 0, num);
		getsym();
	}
	else if (sym == lparen)
	{
		getsym();
		expression();
		if (sym == rparen)
		{
			getsym();
		}
		else
		{
			error(3);                                       /*ȱ��������*/
		}
	}
}
void putcode()
{
	int i;
	fa = fopen("fa.tmp", "w");
	for (i = 0; i<cx; i++)
	{
		printf("%d %s %d %d\n", i, mnemonic[code[i].f], code[i].l, code[i].a);
		fprintf(fa, "%d %s %d %d\n", i, mnemonic[code[i].f], code[i].l, code[i].a);
	}
	fclose(fa);
}
void inter()
{
	int p, b, t, k = 0, o;
	struct instruction i;
	int s[stacksize];
	o = 0;
	t = 0;
	b = 0;
	p = 0;
	s[0] = s[1] = s[2] = 0;
	do
	{
		i.f = code[p].f;
		i.a = code[p].a;
		i.l = code[p].l;
		p++;
		switch (i.f)
		{
		case lit:
			s[t] = i.a;
			t++;
			break;
		case ret:
			t = b;
			p = s[t + 1];
			b = s[t];
			break;
		case add:
			t--;
			s[t - 1] = s[t - 1] + s[t];
			break;
		case sub:
			t--;
			s[t - 1] = s[t - 1] - s[t];
			break;
		case mul:
			t--;
			s[t - 1] = s[t - 1] * s[t];
			break;
		case div:
			t--;
			s[t - 1] = s[t - 1] / s[t];
			break;
		case wrt:
			printf("%d\n", s[t - 1]);
			t--;
			break;

		case red:
			printf("please input: ");
			scanf("%d", &s[t]);

			t++;
			break;

		case lod:
			if (i.l == 0)
			{
				s[t] = s[i.a + b];
			}
			else if (i.l == 1)
			{
				s[t] = s[i.a];
			}
			t++;
			break;
		case sto:			//��ֵ������������Ϊ0����ñ��������к���ͬ�㣬��Ϊ1����ñ���Ϊȫ�ֱ���
			t--;
			if (i.l == 0)
			{
				s[i.a + b] = s[t];
			}
			else if (i.l == 1)
			{
				s[i.a] = s[t];
			}
			break;
		case cal:
			if (o != 0)
			{
				s[t] = b;
				s[t + 1] = p;
				b = t;
				p = i.a;
			}
			else
			{
				s[t] = b;
				s[t + 1] = 0;
				b = t;
				p = i.a;
				o = 1;
			}
			break;
		case inte:
			t += i.a;
			break;
		case jmp:
			p = i.a;
			break;
		case jpc:
			t--;
			if (s[t] == 0)
			{
				p = i.a;
			}
			break;
		}
	} while (p != 0);
}
void tableput()
{
	int i;
	for (i = 1; i <= ptx; i++)
	{
		switch (table[i].kind)
		{
		case voidfun:
			printf("%d void %s ", i, table[i].name);
			printf("lev=%d addr=%d \n", table[i].level, table[i].adr);
			break;
		case variable:
			printf("%d int %s ", i, table[i].name);
			printf("lev=%d addr=%d\n", table[i].level, table[i].adr);
			break;
		case intfun:
			printf("%d int() %s ", i, table[i].name);
			printf("lev=%d addr=%d \n", table[i].level, table[i].adr);
			break;
		}
	}
}
void main()
{

	char tableswitch;       //��ʾ���ֱ����  
	char listswitch;        //��ʾ������������ 
	printf("Input C0 file ?  ");
	scanf("%s", fname);
	fin = fopen(fname, "r");
	if (fin)
	{
		printf("List object code ?(Y/N)");                /*�Ƿ�������������*/
		scanf("%s", fname);
		listswitch = (fname[0] == 'y' || fname[0] == 'Y');
		printf("List symbol table ? (Y/N)");             /*�Ƿ�������ֱ�*/
		scanf("%s", fname);
		tableswitch = (fname[0] == 'y' || fname[0] == 'Y');
		init();                                          /*��ʼ��*/
		getsym();
		block();
		printf("\n*******************\n");
		if (tableswitch)
		{
			tableput();
			printf("\n*******************\n");
		}
		if (listswitch)
		{
			putcode();
			printf("\n*******************\n");
		}
		if (err == 0)
			inter();
		else
			printf(" error!!!!\n");
		fclose(fin);
	}
	else
	{
		printf("open file error!");
	}
}