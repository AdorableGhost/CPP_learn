#include <iostream>
#include <string>


using namespace std;

class  Request
{
public:
	string request_name;
	string request_type;
	int n;
private:
	
};


class Manager {
public:
	Manager(string n, string j, int id)
	{
		name = n;
		job = j;
		classid = id;
	}

	void setSuper(Manager *p)
	{
		this->super = p;
	}

	virtual void  apply(Request*) = 0;
	int classid;
	Manager* super;
	string name;
	string job;
private:

	
	
};

class  zhuguan:public Manager
{
public:
	zhuguan(string n,  int id) :Manager(n,"主管", id) {}

	void apply(Request* r)
	{
		if (r->n > this->classid)
		{
			cout << r->request_type << "\t" << r->request_name << "\t 被" << this->job << this->name << "审阅！无权限，将继续向上递交！！" << "classid=" << this->classid << endl;
			super->apply(r);
		}
		else
		{
			cout << r->request_type << "\t" << r->request_name << "\t 被"<<this->job<<this->name<<"批准！！！"<<"classid="<<this->classid<< endl;
		}
	}

private:

};

class  zongjian :public Manager
{
public:
	zongjian(string n, int id) :Manager(n, "总监", id) {}

	void apply(Request* r)
	{
		if (r->n > this->classid)
		{
			cout << r->request_type << "\t" << r->request_name << "\t 被" << this->job << this->name << "审阅！无权限，将继续向上递交！！" << "classid=" << this->classid << endl;
			super->apply(r);
		}
		else
		{
			cout << r->request_type << "\t" << r->request_name << "\t 被" << this->job << this->name << "批准！！！" << "classid=" << this->classid << endl;
		}
	}

private:

};


class  zongjingli :public Manager
{
public:
	zongjingli(string n) :Manager(n, "总经理", 1000) {}

	void apply(Request* r)
	{
		
			cout << r->request_type << "\t" << r->request_name << "\t 被" << this->job << this->name << "批准！！！" << "classid=" << this->classid << endl;
		
	}

private:

};


int main(void)
{
	Request* request = new Request();
	request->request_name = "生病请10天假";
	request->request_type = "病假";
	request->n = 50;

	zhuguan* zg = new zhuguan("小芳", 10);
	zongjian* zj = new zongjian("小明", 30);
	zongjingli* zjl = new zongjingli("老大");
	zg->setSuper(zj);
	zj->setSuper(zjl);

	zg->apply(request);
	return 0;
}