#include <iostream>
#include <string>
using namespace std;


class OP
{
public:
    double a, b;
    virtual double jisuan()
    {
        return 0;
    }
};

class add : public OP
{
    double jisuan()
    {
        return a + b;
    }
};

class sub : public OP
{
    double jisuan()
    {
        return a - b;
    }
};

class divv : public OP
{
    double jisuan()
    {
        return a / b;
    }
};

class mul : public OP
{
    double jisuan()
    {
        return a * b;
    }
};

class IFac
{
private:
    /* data */
public:
    virtual OP *selectop() = 0;
};

class addop : public IFac
{
public:
    static OP *selectop()
    {
        return new add();
    }
};

class subop : public IFac
{
public:
    static OP *selectop()
    {
        return new sub();
    }
};

class divop : public IFac
{
public:
    static OP *selectop()
    {
        return new divv();
    }
};

class mulop : public IFac
{
public:
    static OP *selectop()
    {
        return new mul();
    }
};

int main(void)
{
    IFac *opp = mulop::selectop();
    opp->a=90;
    opp->b=100;
    cout << opp->jisuan()<<endl;
    return 0;
}