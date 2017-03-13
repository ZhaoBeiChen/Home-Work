# include<iostream>
# include<cstdlib>
using namespace std;
void countingsort(int data[], const int n)
{
	long i;
	long largest = data[0];
	long *tmp = new long[n];
	for (i = 1; i < n; i++)
	if (largest < data[i])
		largest = data[i];
	unsigned long *count = new unsigned long[largest];
	for (i = 0; i <= largest; i++)
		count[i] = 0;	
	for (i = 0; i < n; i++)
		count[data[i]]++;
	for (i = 1; i <= largest; i++)
		count[i] = count[i - 1] + count[i];
	for (i = n - 1; i >= 0; i--)
	{
		tmp[count[data[i]] - 1] = data[i];
		count[data[i]]--;
	}
	for (i = 0; i < n; i++)
		data[i] = tmp[i];
}
int main()
{
	int i, a[1000];
	for (i = 0; i < 100; i++)
	{
		a[i] = rand() % 100;
	}
	countingsort(a, 100);
	for (i = 0; i < 100; i++)
	{
		cout << a[i] << ' ';
		if (i % 10 == 9)
			cout << endl;
	}
}
