#include<iostream>
using namespace std;

int maze[1000][1000];
int row;
int col;
int sum=0;

struct Coordinate	//坐标
{
	int x;
	int y;
};

class Block		//通道砖
{
	int ord;
	Coordinate seat;
	int direction;
public:
	Block()
	{
		direction = 1;
	}
	void IN(int step, Coordinate site, int Dire)
	{
		ord = step;
		seat = site;
		direction = Dire;
	}
	void changeDir()
	{
		direction++;
	}
	int Out_ord()
	{
		return ord;
	}
	Coordinate Out_seat()
	{
		return seat;
	}
	int Out_Dire()
	{
		return direction;
	}
};
Block nulldata;
class StackNode		//栈结点
{
	Block a;
public:
	StackNode(Block e)
	{
		a = e;
		next = NULL;
	}
	Block Out_data()
	{
		return a;
	}
	StackNode *next;
};

class setStack		//创建栈
{
	StackNode *top;
public:
	setStack()
	{
		top = new StackNode(nulldata);
		top->next = NULL;
	}
	bool IsEmpty()
	{
		if (top->next == NULL)
			return true;
		else return false;
	}
	void push(Block e)
	{
		StackNode *p;
		p = new StackNode(e);
		p->next = top->next;
		top->next = p;
	}
	Block pop()
	{
		if (top->next != NULL)
		{
			StackNode *p;
			Block e;
 			p = top->next;
			e = p->Out_data();
			top->next = p->next;
			delete p;
			return e;
		}
		else
		{
			cout << "the stack is Empty" << endl;
			return nulldata;
		}
	}
	Block GetTop()
	{
		if (top->next != NULL)
			return top->next->Out_data();
		else
		{
			cout << "the stack is Empty" << endl;
			return nulldata;
		}
	}
};

class Maze		//迷宫求解类
{
	Block e;
	Coordinate curpos;
	int curstep;
public:
	bool Pass(Coordinate curpos)
	{
		if (maze[curpos.x][curpos.y] == 1)
			return true;
		else return false;
	}
	void Footprint(Coordinate curpos)
	{
		maze[curpos.x][curpos.y]=0;
		return;
	}
	void MakeStop(Coordinate curpos)
	{
		maze[curpos.x][curpos.y] = 0;
		return;
	}
	Coordinate NextPos(Coordinate nowPos, int Dire)
	{
		if (Dire == 1 && nowPos.y<col)
		{
			nowPos.y++;
		}
		else if (Dire == 2&&nowPos.x<row)
		{
			nowPos.x++;
		}
		else if (Dire == 3 && nowPos.y>1 )
		{
			nowPos.y--;
		}
		else if (Dire == 4 && nowPos.x>1 )
		{
			nowPos.x--;
		}
		return nowPos;
	}
	void MazePath(Coordinate start,Coordinate end)
	{
		setStack s;
		curpos = start;
		curstep = 1;
		do
		{
			if (Pass(curpos))
			{
				Footprint(curpos);
				e.IN(curstep,curpos,1);
				s.push(e);
				if (curpos.x == end.x && curpos.y == end.y)
				{
					sum++;
					
					e = s.pop();
					maze[curpos.x][curpos.y] = 1;
					e = s.pop();
					while (e.Out_Dire() == 4 && !s.IsEmpty())
					{
						maze[e.Out_seat().x][e.Out_seat().y] = 1;
						e = s.pop();
					}
					if (s.IsEmpty())
					{
						cout << sum << endl;
						return;
					}
					e.changeDir();
					s.push(e);
					curpos.x = e.Out_seat().x;
					curpos.y = e.Out_seat().y;
					curpos = NextPos(curpos,e.Out_Dire());
				}
				else curpos = NextPos(curpos,1);
				curstep++;
			}
			else
			{
				if (!s.IsEmpty())
				{
					e = s.pop();
					while (e.Out_Dire() == 4 && !s.IsEmpty())

					{
						maze[e.Out_seat().x][e.Out_seat().y] = 1;
						e = s.pop();
					}
					if (e.Out_Dire() < 4)
					{
						e.changeDir();
						s.push(e);
						curpos = NextPos(e.Out_seat(),e.Out_Dire());
					}
				}
			}
			
		} while (!s.IsEmpty());
		if (sum != 0)
			cout << sum << endl;
		else cout << "没有通路" << endl;
	}
};

int main()
{
	while (1)
	{
		sum = 0;
		cin >> row;
		cin >> col;
		if (row == 0 && col == 0)
			break;
		int i;
		int j;
		for (i = 1; i <= row; i++)
		{
			for (j = 1; j <= col; j++)
			{
				cin >> maze[i][j];
			}
		}

		Coordinate start;
		Coordinate end;
		start.x = 1;
		start.y = 1;
		end.x = row;
		end.y = col;

		Maze s;
		s.MazePath(start, end);
	}
}