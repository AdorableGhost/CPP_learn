#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

string Command[]={
    "git add .",
    "git commit -m ",
    "git push origin master",
    "echo DOne with GIt"
};

void run (string &comment)
{
    // int* p[5]={0};
    string cmd;
    Command[1]+=comment;
    cout<<Command[1];
    for(auto cmd:Command)
    {
        // static int i=0;
        cout<<cmd;
        cout<<system(cmd.c_str());
        // i++;
    }
    
    // return p;
    
}


int main (void)
{
    
    string cmd="test";
    run(cmd);

}
