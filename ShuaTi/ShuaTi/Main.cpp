#include<iostream>
#include<stack>
#include<vector>
using namespace std;

int main(){

	vector<int> vec;
	vec.push_back(2);
	vec.push_back(4);
	vec.push_back(7);
	vec.push_back(8);
	vec.push_back(9);
	vector<int>::iterator it;
	for (it = vec.begin(); it != vec.end(); it++){
	
		cout << *it << endl;
	}
}