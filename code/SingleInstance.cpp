#include <iostream>
#include <string>

class
{
public:
    int a = 100;
} aa;

class SingleInstance
{
private:
    /* data */

    int i = 0;

public:
    static SingleInstance *instance;
    SingleInstance(int a)
    {
        this->i = a;
    }

    static SingleInstance *get_instance()
    {
        return instance;
    }
};

SingleInstance *SingleInstance::instance = new SingleInstance(1995);


class B:public SingleInstance
{

};

int main(void)
{
    SingleInstance *s1=SingleInstance::get_instance();
    SingleInstance *s2=B::get_instance();

    std::cout<<(s1==s2)<<std::endl;

    std::cin.get();

    return 0;
}