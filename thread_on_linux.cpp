#include <iostream>
#include <stdlib.h>
#include <thread>

using namespace std;
void run(char* p)
{
    int i=0;
    i=system(p);
}

int main()
{
    char p[5][20]={
        "ls",
        "echo nihao",
        "gnome-terminal",
        "terminator",
        "ps -aux"

    };

    while("nimei")
    {
       static  int i(0);
        if(i<5){
            thread  *pt=new  thread(run,p[i]);
            i+=1;
            cout<<"I now is :\t"<<i<<endl;
        }
        else{
            break;
        }
        
        cout<<"Breaking...."<<endl;
    }


    cout<<"Finally count is \t"<<count<<endl;
    cout<<"Used "<<n <<"threads"<<endl;


    cin.get();
    return 0;
}

