#include <iostream>
#include <vector> 
#include <algorithm>

using namespace std;

template <class T>
class vector_s {
public:
void operator()(const T &t1)
	{
		cout << t1 << endl;
	}
};

int main(void)
{
	vector<int> myv;
	myv.push_back(13);
	myv.push_back(23);
	myv.push_back(33);
	myv.push_back(113);
	myv.push_back(1995);
	myv.push_back(1996);

	vector_s<int> print;
	for_each(myv.begin(), myv.end(), print);

	cin.get();



	return 0;
}