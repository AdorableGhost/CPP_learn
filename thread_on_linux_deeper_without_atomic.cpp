#include <iostream>
#include <stdlib.h>
#include <thread>
#include <atomic>

using namespace std;
int count(0);

void run()
{
    for(int i(0);i<1000000;i++)
    {
        count++;
        cout<<"\t"<<i<<"\t"<<count<<"\t";
    }
}

int main()
{
    auto n=thread::hardware_concurrency();

    thread* pt[n];
    for(int z=0;z<n;z++)
    {
        pt[z]=new thread(run);
        pt[z]->detach();

    }
    
    cout<<"Finally count is \t"<<count<<endl;
    cout<<"Used "<<n <<"threads"<<endl;




    cin.get();
    return 0;
}

