#include <iostream>
#include <string>
#include <functional>
#include <list>
#include <algorithm>
#include "boost/bind.hpp"

using namespace std;
using namespace boost;

class jia:public binary_function<int,int,void>
{
public:
void operator ()( int i, int j) const
{
	cout << i+j << endl;
}

private:

};

void add(int i, int j)
{
	cout << i + j << endl;
}


int main(void)
{
	list <int> ls1;
	ls1.push_back(5);
	ls1.push_back(15);
	ls1.push_back(125);

	//std 方式
	for_each(ls1.begin(), ls1.end(), bind1st(jia(),10));

	//boost 方式
	for_each(ls1.begin(), ls1.end(), bind(add,13, _1));
	cin.get();
	return 0;
}