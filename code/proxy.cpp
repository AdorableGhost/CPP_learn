#include <iostream>
#include <string>

using namespace std;

class  girl
{
public:
	 girl(string);
	 girl();
	~ girl();
	string name;
private:

};

 girl:: girl(string s1)
{
	 name = s1;
}

 girl::~ girl()
{
}

 girl::girl()
 {
	 name = "不知名的!";
 }


 class gift {
 public:
	 virtual void gift1() = 0;
	 virtual void gift2() = 0;
 };


 class gg:public gift
 {
 public:
	 gg(girl);
	 ~gg();


	void gift1()
	 {
		 cout << mm.name << "送你礼物1" << endl;
	 }

	void gift2()
	{
		cout << mm.name << "送你礼物2" << endl;
	}
 private:
	 girl mm;
 };

 gg::gg(girl m)
 {
	 mm = m;
 }

 gg::~gg()
 {
 }



 class proxy :public gift
 {
 private :
	 gg gg1;

 public:

	 proxy(girl mm) :gg1(mm)
	 {

	 }

	 void gift1()
	 {
		 gg1.gift1();
	 }

	 void gift2()
	 {
		 gg1.gift2();
	 }
 };



int main(void)
{

	girl mm1("小妹妹");
	proxy p1(mm1);
	p1.gift1();
	p1.gift2();


	cin.get();


	return 0;
}