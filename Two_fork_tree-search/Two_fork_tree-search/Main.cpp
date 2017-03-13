#include<iostream>
#include<cstring>
using namespace std;

class TreeNode
{
	char letter[50];
	int count;
public:
	TreeNode *rightChild;
	TreeNode *leftChild;
	TreeNode()
	{
		rightChild = NULL;
		leftChild = NULL;
		count = 1;
	}
	void In(char * &a)
	{
		strcpy_s(letter,a);
	}
	char *Out()
	{
		return letter;
	}
	void Count()
	{
		count++;
	}
	void In_count(int i)
	{
		count = i;
	}
	int Out_count()
	{
		return count;
	}
};

class BinaryTree_Search
{
	TreeNode *root;
public:
	BinaryTree_Search()
	{
		root = NULL;
	}
	TreeNode *Out_root()
	{
		return root;
	}
	void change(TreeNode * &obj)
	{
		root = obj;
	}
	int Compared(char * &a, char * &b)
	{
		int i = 0;
		while (1)
		{
			if (a[i] > b[i])
				return 1;
			else if (a[i] < b[i])
				return 0;
			else
			{
				if (strlen(a) == strlen(b) && i == strlen(a))
					return -1;
				else if (strlen(a)>strlen(b) && i == strlen(b))
					return 1;
				else if (strlen(a) < strlen(b) && i == strlen(a))
					return 0;
				else i++;
			}
		}
	}
	TreeNode *Search(char * &s, TreeNode * &parent)
	{
		TreeNode *p;
		p = root;
		parent = p;
		char *temp;
		while (p)
		{
			temp = p->Out();
			if (Compared(s,temp)==1)
			{
				parent = p;
				p = p->rightChild;
			}
			else if (Compared(s, temp) == 0)
			{
				parent = p;
				p = p->leftChild;
			}
			else if (Compared(s, temp) == -1)
			{
				
				return p;
			}
		}
		return NULL;
	}
	void buildSearchTree(char * &s) 
	{
		TreeNode * pp = NULL;
		TreeNode *p = NULL;
		if ((p = Search(s, pp)) != NULL)
		{
			p->Count();
			return;
		}
		TreeNode *r = new TreeNode();
		r->In(s);
		char *temp = pp->Out();
		if (!root)
		{
			root = r;
			return;
		}
		else if (Compared(s,temp)==1)
			pp->rightChild = r;
		else pp->leftChild = r;
		return;
	}
	void Deleted(char *key)
	{
		TreeNode * pp = NULL;
		TreeNode *p = NULL;
		if ((p = Search(key, pp)) == NULL)
			return;
		if (p->leftChild && p->rightChild)
		{
			TreeNode *s = p->rightChild, *ps = p;
			while (s->leftChild)
			{
				ps = s;
				s = s->leftChild;
			}

			char *t = s->Out();
			p->In(t);
			p->In_count(s->Out_count());
			p = s;
			pp = ps;
		}

		TreeNode *pc;
		if (p->leftChild)
			pc = p->leftChild;
		else pc = p->rightChild;
		if (p == root) root = pc;
		else
		{
			if (p == pp->leftChild)
				pp->leftChild = pc;
			else pp->rightChild = pc;
		}
		delete p;
	}
};

BinaryTree_Search Tree;

void MidRead(TreeNode * &t)
{
	if (t)
	{	
		MidRead(t->leftChild);
		cout << t->Out() << " " << t->Out_count() << endl;
		MidRead(t->rightChild);
	}
}

void PreRead(TreeNode * &t)
{
	if (t)
	{
		cout << t->Out() << " " << t->Out_count() << endl;
		PreRead(t->leftChild);
		PreRead(t->rightChild);
		
	}
}

void BuildBinaryTree(char s[])
{
	Tree.buildSearchTree(s);
}


void change(char a[])
{
	int n = strlen(a);
	int i;
	for (i = 0; i < n; i++)
	{
		if (a[i] < 97)
		{
			a[i] = a[i] + 32;
		}
	}
}


int main()
{
	char str[10000];
	char str_0;
	int i = 0;
	while (cin.get(str_0))
	{
		if (str_0 == '#')
			break;
		if ((str_0>=65 && str_0<=90) || (str_0>=97 && str_0<=122)||str_0 == ' ')
		{
			str[i] = str_0;
			i++;
		}
	}
	str[i] = '#';
	char str_store[50];
	i = 0;
	int j = 0;
	while (1)
	{
		if (str[i] == '#')
		{
			str_store[j] = '\0';
			change(str_store);
			if (str_store[0] != '\0')
				BuildBinaryTree(str_store);
			break;
		}
		if (str[i] == ' ')
		{
			str_store[j] = '\0';
			change(str_store);
			if (str_store[0] != '\0')
				BuildBinaryTree(str_store);
			j = 0;
		}
		else
		{
			str_store[j] = str[i];
			j++;
		}
		i++;
	}

	TreeNode *t;
	t = Tree.Out_root();
	MidRead(t);
	Tree.Deleted("a");
	Tree.Deleted("was");
	Tree.Deleted("of");
	Tree.Deleted("and");
	Tree.Deleted("is");
	Tree.Deleted("are");
	Tree.Deleted("an");
	Tree.Deleted("were");
	Tree.Deleted("the");

	t = Tree.Out_root();
	PreRead(t);
	return 0;
}