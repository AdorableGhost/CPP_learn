#include <iostream>
#include <list>
#include <functional>
#include <array>
#include <algorithm>

using namespace std;


class shuchu {
  public:

  void operator()(int x)
  {
    std::cout<<x<<endl;
  }
};



 int main(int argc, char const *argv[]) {
  /* code */

  // array<int,5>array1({1,2,3,4,5});
  list <int>ls1;
  ls1.push_back(1);
   ls1.push_back(3);
    ls1.push_back(5);
     ls1.push_back(7);
      ls1.push_back(9);
  auto ib=ls1.begin();
  auto ie=ls1.end();
  for_each(ib,ie,shuchu());
  cin.get();
  return 0;
}
