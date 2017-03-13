# define norw 9        //a number of reserved word         /*�ؼ��ָ���*/ 
# define txmax 100      //length of identifier table         /*���ֱ�����*/
# define nmax  14       //max number of digits in numbers         /*number�����λ��*/
# define al 10           //length of identifier        /*���ŵ���󳤶�*/
# define amax 2047      //maximum address         /*��ַ�Ͻ�*/
# define cxmax 200      //size of code array        /*���������������*/
#define stacksize 500
/*����*/
enum symbol{
	nul, ident, number, plus, minus,
	times, slash, lbrace, rbrace, lparen,
	rparen, comma, semicolon, becomes, ifsym,
	elsesym, whilesym, printfsym, scanfsym,
	intsym, voidsym, returnsym, mainsym,
};
#define symnum 23
/*-------------*/
enum object{   //objectΪ��ʶ�������� 
	variable,
	intfun,
	voidfun,
};
/*--------------*/
enum fct{   //fct���ͷֱ��ʶ��PCODE�ĸ���ָ��
	lit, ret, lod, sto, cal, inte, jmp, jpc, add, div, mul, sub, wrt, red,
};
#define fctnum 14
/*--------------*/
struct instruction   //ָ�� 
{
	enum fct f;  //������ 
	int l;     //���
	int a;
};
FILE * fa;   //������������

char ch;                //��ȡ�ַ��Ļ�����,getchʹ�� 
enum symbol sym;        //��ǰ���� 
enum object k;
char tmp[al + 1];
char id[al + 1];          //��ǰident,���һ���ֽ����ڴ��0 
int  num;               //��ǰnumber 
int ls;
int cc, ll;              //getchʹ�õļ�����,cc��ʾ��ǰ�ַ�(ch)��λ�� 
int cx;                 //���������ָ�룬ȡֵ��Χ[0,cxmax-1]
int ptx;				//���ֱ����λָ��
int pdx;				//��ǰ���ַ
char line[81];          //��ȡ�л����� 
char a[al + 1];           //��ʱ���ţ������һ���ֽ����ڴ��0 
struct instruction code[cxmax];   //����������������� 
char word[norw][al];              //������
enum symbol wsym[norw];           //�����ֶ�Ӧ�ķ���ֵ 
enum symbol ssym[256];            //���ַ��ķ���ֵ 
char mnemonic[fctnum][5];         //���������ָ������ 
struct tablestruct
{
	char name[al];                            /*����*/
	enum object kind;                         /*���ͣ�const��var��array or procedure*/
	int val;                                  /*��ֵ��*/
	int level;                                /*�����㣬*/
	int adr;                                  /*��ַ��*/
	int size;                                 /*��Ҫ������������ռ䣬��procedureʹ��*/
};
struct tablestruct table[txmax];             /*���ֱ�*/
FILE * fin;        //fin�ı��ļ�����ָ�������Դ�����ļ�
FILE* fout;        //fout�ı��ļ�����ָ��������ļ�
char fname[al];
int err;                                       /*���������*/
void factor();
void init();
void error(int n);
void term();
void expression();
void ifcl();
void whilecl();
void statement();
void putcode();
void inter();
void glintcl();
void getch();
void getsym();