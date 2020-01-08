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
        "terminator",
        "remmina",
        "gnome-terminal",
        "google-chrome",
        "code"

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

    cout<<"Hi ,Have a good day!"<<endl;
    cin.get();
    return 0;
}

