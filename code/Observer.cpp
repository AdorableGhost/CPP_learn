#include <iostream>
#include <string>
#include <list>

using namespace std;

class  Subject;


class Observer
{
public:
	Observer(string, Subject*);
	~Observer();
	virtual void update()=0;
protected:
	string name;
	Subject* sub;
};

class  Subject
{
public:
	string actions;
	virtual void attach(Observer* s) = 0;
	virtual void detach(Observer* s) = 0;
	virtual void notify() = 0;
protected:
	list<Observer*> observers;
};

Observer::Observer(string nn, Subject* s) : name(nn), sub(s)
{

}

Observer::~Observer()
{
}




class NBAOB :public Observer
{
public:
	NBAOB(string nn, Subject* s) :Observer(nn, s)
	{

	}

	void update()
	{
		cout << name << "收到消息" << sub->actions << endl;
		if (sub->actions == "你妹的")
		{
			cout << "你妹的，你妹的\n" << endl;
		}

		if (sub->actions == "赢了")
		{
			cout << "全体注意，你妹的中国队赢了\n" << endl;
		}
	}

private:

};

class EatOb :public Observer
{
public:
	EatOb(string nn, Subject* s) :Observer(nn, s)
	{

	}
	void update()
	{
		cout << name << "收到消息" << sub->actions << endl;
		if (sub->actions == "吃饭")
		{
			cout << "速度就来\n" << endl;
		}

		if (sub->actions == "时间过了")
		{
			cout << "全体注意，吃饭时间过了\n" << endl;
		}
	}

private:

};



class Secretary :public Subject
{
public:
	void attach(Observer* s)
	{
		observers.push_back(s);
	}
	void detach(Observer* ss)
	{
		auto i = observers.begin();
		while (i != observers.end())
		{
			if ((*i) == ss)
			{
				observers.erase(i);
			}

			++i;
		}
	}

	void notify()
	{
		auto i = observers.begin();
		while (i != observers.end())
		{
			(*i)->update();

			++i;
		}
	}

private:

};







int main(void)
{
	Subject* sj = new Secretary();
	NBAOB* nbs = new NBAOB("NBA1", sj);
	NBAOB* nbs1 = new NBAOB("NBA2", sj);
	EatOb* chihuo1 = new EatOb("小花吃货", sj);

	sj->attach(nbs);
	sj->attach(nbs1);
	sj->attach(chihuo1);

	sj->actions = "你妹的";
	sj->notify();

	sj->actions = "时间过了";
	sj->notify();
	sj->actions = "吃饭";
	sj->notify();
	sj->actions = "赢了";
	sj->notify();

	sj->actions = "你妹的";
	sj->notify();


	cin.get();

	return 0;
}