#include<iostream>
#include<cmath>
using namespace std;
int main()
{
	double a, b, c;
	int d, f, g;
	cin >> g;
	for (int i = 0; i<g; i++)
	{
		cin >> a >> b >> c;
		if (a == 0)
			cout << int(-c / b) << endl;
		else
		{
			if (b*b - 4 * a*c<0)
				cout << "no root" << endl;
			else
			{
				d = (-b + sqrt(b*b - 4 * a*c)) / (2 * a);
				f = (-b - sqrt(b*b - 4 * a*c)) / (2 * a);
				if (d>f)
					cout << f << " " << d << endl;
				else cout << d << " " << f << endl;
			}


		}

	}
}
