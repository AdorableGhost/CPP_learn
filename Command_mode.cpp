#include <iostream>
#include <string>
#include <list>

using namespace std;



class doing
{
public:

	void action1() {
		cout << "lalala 吃饭了" << endl;
	}

	void action2()
	{
		cout << "是时候运动了！！！！！" << endl;
	}
private:

};

class  Command
{

public:
	Command(doing * d) {
		reciver = d;
	}

	virtual void do_doing() = 0;

	protected:
		doing* reciver;

		

};


class action1_command:public Command
{
public:
	action1_command(doing* d) :Command(d)
	{

	}

	void do_doing()
	{
		reciver->action1();
	}

};

class action2_command :public Command
{
public:
	action2_command(doing* d) :Command(d)
	{

	}

	void do_doing()
	{
		reciver->action2();
	}

};

class waiter
{
public:

	void set_action(Command* c)
	{
		this->command = c;
	}

	void do_action()
	{
		this->command->do_doing();
	}

protected:
	Command* command;

};

class waiter_n {

public:
	void set_action(Command* c)
	{
		this->command.push_back(c);
	}

	void do_action()
	{
		auto n = command.begin();
		while (n!=command.end())
		{
			(*n)->do_doing();
			n++;
		}
	}

private:
	list<Command*> command;
};


int main(void)
{
	doing* dd = new doing();
	Command* action_command1 = new action1_command(dd);
	Command* action_command2 = new action2_command(dd);
	waiter* w = new waiter();
	w->set_action(action_command1);
	w->do_action();
	w->set_action(action_command2);
	w->do_action();
	cout << endl;
	waiter_n* ww = new waiter_n();
	ww->set_action(action_command1);
	ww->set_action(action_command2);
	ww->do_action();
	return 0;
}