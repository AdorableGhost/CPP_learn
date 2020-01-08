#include <iostream>
#include <string>

using namespace std;

class OP
{
public:
    double a;
    double b;
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

class Fac
{
public:
    static OP *selectop(char c)
    {
        switch (c)
        {
        case '+':
            return new add();
            break;

        case '-':
            return new sub();
            break;

        case '*':
            return new mul();
            break;

        case '/':
            return new divv();
            break;

        default:
            printf("you entered wrong caculation!!");
            break;
        }
    }
};

int main(void)
{
    OP *opr = Fac::selectop('/');
    opr->a = 100;
    opr->b = 5;
    cout << opr->jisuan() << endl;

    return 0;
}
