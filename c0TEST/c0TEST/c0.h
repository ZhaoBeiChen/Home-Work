# define norw 9        //a number of reserved word         /*关键字个数*/ 
# define txmax 100      //length of identifier table         /*名字表容量*/
# define nmax  14       //max number of digits in numbers         /*number的最大位数*/
# define al 10           //length of identifier        /*符号的最大长度*/
# define amax 2047      //maximum address         /*地址上界*/
# define cxmax 200      //size of code array        /*最多的虚拟机代码数*/
#define stacksize 500
/*符号*/
enum symbol{
	nul, ident, number, plus, minus,
	times, slash, lbrace, rbrace, lparen,
	rparen, comma, semicolon, becomes, ifsym,
	elsesym, whilesym, printfsym, scanfsym,
	intsym, voidsym, returnsym, mainsym,
};
#define symnum 23
/*-------------*/
enum object{   //object为标识符的类型 
	variable,
	intfun,
	voidfun,
};
/*--------------*/
enum fct{   //fct类型分别标识类PCODE的各条指令
	lit, ret, lod, sto, cal, inte, jmp, jpc, add, div, mul, sub, wrt, red,
};
#define fctnum 14
/*--------------*/
struct instruction   //指令 
{
	enum fct f;  //功能码 
	int l;     //层次
	int a;
};
FILE * fa;   //输出虚拟机代码

char ch;                //获取字符的缓冲区,getch使用 
enum symbol sym;        //当前符号 
enum object k;
char tmp[al + 1];
char id[al + 1];          //当前ident,多出一个字节用于存放0 
int  num;               //当前number 
int ls;
int cc, ll;              //getch使用的计数器,cc表示当前字符(ch)的位置 
int cx;                 //虚拟机代码指针，取值范围[0,cxmax-1]
int ptx;				//名字表最后位指针
int pdx;				//当前层地址
char line[81];          //读取行缓冲区 
char a[al + 1];           //临时符号，多出的一个字节用于存放0 
struct instruction code[cxmax];   //存放虚拟机代码的数组 
char word[norw][al];              //保留字
enum symbol wsym[norw];           //保留字对应的符号值 
enum symbol ssym[256];            //单字符的符号值 
char mnemonic[fctnum][5];         //虚拟机代码指令名称 
struct tablestruct
{
	char name[al];                            /*名字*/
	enum object kind;                         /*类型：const，var，array or procedure*/
	int val;                                  /*数值，*/
	int level;                                /*所处层，*/
	int adr;                                  /*地址，*/
	int size;                                 /*需要分配的数据区空间，仅procedure使用*/
};
struct tablestruct table[txmax];             /*名字表*/
FILE * fin;        //fin文本文件用于指向输入的源程序文件
FILE* fout;        //fout文本文件用于指向输出的文件
char fname[al];
int err;                                       /*错误计数器*/
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