#include <iostream>
#include <boost/array.hpp>
#include <string>

using namespace std;

int main(void)
{
	boost::array<int,10> arr = { 0,1,2,3,4,5,6,7,8,9 };

	boost::array<int, 10>::iterator ib = arr.begin();
	boost::array<int, 10>::iterator ie = arr.end();

	for (;ib!=ie;ib++)
	{
		cout << *ib << endl;
	}

	cin.get();
	return 0;
}