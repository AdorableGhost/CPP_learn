#include <iostream>
#include <string>
using namespace std;

class data1
{

public:
    virtual void getdata() = 0;
    virtual void setdata() = 0;
};

class intdata : public data1
{
public:
    int a = 0;
    int b = 0;

public:
    void setdata()
    {
        cout << "please Enter two int data:" << endl;
        cin >> a >> b;
    }

    void getdata()
    {
        if (a == 0 && b == 0)
        {
            cout << "data not set!" << endl;
        }
        else
        {
            cout << "a IS :\t" << a << "\t b IS \t" << b << endl;
        }
    }
};

class doubledata : public data1
{
public:
    double a = 0;
    double b = 0;
    void setdata()
    {
        cout << "please Enter two double data:" << endl;
        cin >> a >> b;
    }
    void getdata()
    {
        if (a == 0.0 && b == 0.0)
        {
            cout << "data not set!" << endl;
        }
        else
        {
            cout << "a IS :\t" << a << "\t b IS \t" << b << endl;
        }
    }
};

class stringdata : public data1
{
public:
    string a = nullptr;
    string b = nullptr;
    void setdata()
    {
        cout << "please Enter two strings data:" << endl;
        cin >> a >> b;
    }

    void getdata()
    {
        if (a.empty() && b.empty())
        {
            cout << "data not set!" << endl;
        }
        else
        {
            cout << "a IS :\t" << a << "\t b IS \t" << b << endl;
        }
    }
};

class OP
{
public:
    data1 *op1;
    data1 *op2;

    virtual double jisuan()
    {
        return 0;
    }
};


// 太多太复杂，只实现一个加法把
class iadd : public OP
{
    intdata *op1 = new intdata();
    intdata *op2 = new intdata();
    op1->setdata();
    op2->setdata();
    double jisuan()
    {
        return op1->a + op2->a + op1->b + op2->b;
    }
};

class dadd : public OP
{
    doubledata *op1 = new doubledata();
   doubledata *op2 = new doubledata();
    op1->setdata();
    op2->setdata();
    double jisuan()
    {
        return op1->a + op2->a + op1->b + op2->b;
    }
};


class sadd : public OP
{
    doubledata *op1 = new doubledata();
    doubledata *op2 = new doubledata();
    op1->setdata();
    op2->setdata();
    double jisuan()
    {
        return op1->a + op2->a + op1->b + op2->b;
    }
};

class IFac
{
private:
    /* data */
public:
    data1* d1;
    data1* d2;
    OP *selectop() ;
};

class intaddop : public IFac
{
public:
    static OP *selectop()
    {
        return new iadd();
    }
};

class doubleaddop : public IFac
{
public:
    static OP *selectop()
    {
        return new dadd();
    }
};

class astringddop : public IFac
{
public:
    static OP *selectop()
    {
        return new sadd();
    }
};


int main(void)
{
    IFac *opp =iadd::selectop;

    cout << opp->jisuan() << endl;
    return 0;
}