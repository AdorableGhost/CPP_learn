#include <iostream>
#include <stdlib.h>
#include <string>
#include <sys/wait.h>
#include <sys/types.h>


using namespace std;


string fo[]={"\n11111111111111111111-----你已成仙,顺利通过-----111111111111111111111\n",
" 11111111111111111111111111111111100001111111111111111111111111111\n",
" 11111111111111111111111111111110000111111111111111111111111111111\n",
" 11111111111111111111111111111000000111111111111111111111111111111\n",
"11111111111111111111111111100000011110001100000000000000011111111\n",
" 11111111111111111100000000000000000000000000000000011111111111111\n",
" 11111111111111110111000000000000000000000000000011111111111111111\n",
" 11111111111111111111111000000000000000000000000000000000111111111\n",
" 11111111111111111110000000000000000000000000000000111111111111111\n",
" 11111111111111111100011100000000000000000000000000000111111111111\n",
"11111111111111100000110000000000011000000000000000000011111111111\n",
"11111111111111000000000000000100111100000000000001100000111111111\n",
 "11111111110000000000000000001110111110000000000000111000011111111\n",
 "11111111000000000000000000011111111100000000000000011110001111111\n",
" 11111110000000011111111111111111111100000000000000001111100111111\n",
 "11111111000001111111111111111111110000000000000000001111111111111\n",
 "11111111110111111111111111111100000000000000000000000111111111111\n",
 "11111111111111110000000000000000000000000000000000000111111111111\n",
 "11111111111111111100000000000000000000000000001100000111111111111\n",
 "11111111111111000000000000000000000000000000111100000111111111111\n",
 "11111111111000000000000000000000000000000001111110000111111111111\n",
 "11111111100000000000000000000000000000001111111110000111111111111\n",
 "11111110000000000000000000000000000000111111111110000111111111111\n",
 "11111100000000000000000001110000001111111111111110001111111111111\n",
 "11111000000000000000011111111111111111111111111110011111111111111\n",
 "11110000000000000001111111111111111100111111111111111111111111111\n",
 "11100000000000000011111111111111111111100001111111111111111111111\n",
 "11100000000001000111111111111111111111111000001111111111111111111\n",
 "11000000000001100111111111111111111111111110000000111111111111111\n",
 "11000000000000111011111111111100011111000011100000001111111111111\n",
 "11000000000000011111111111111111000111110000000000000011111111111\n",
 "11000000000000000011111111111111000000000000000000000000111111111\n",
 "11001000000000000000001111111110000000000000000000000000001111111\n",
 "11100110000000000001111111110000000000000000111000000000000111111\n",
 "11110110000000000000000000000000000000000111111111110000000011111\n",
 "11111110000000000000000000000000000000001111111111111100000001111\n",
 "11111110000010000000000000000001100000000111011111111110000001111\n",
 "11111111000111110000000000000111110000000000111111111110110000111\n",
 "11111110001111111100010000000001111100000111111111111111110000111\n",
 "11111110001111111111111110000000111111100000000111111111111000111\n",
 "11111111001111111111111111111000000111111111111111111111111100011"};





string Command[]={
    "git add .",
    "git commit -m ",
    "git push origin master",
    "echo Done with GIt"
};

void run (string &comment)
{
    // int* p[5]={0};
    string cmd;
    Command[1]+='\''+comment+'\'';
  //  cout<<Command[1];
    for(auto cmd:Command)
    {
        int i;
        cout<<cmd<<endl;
        i=system(cmd.c_str());

    }
    
            cout<<"\n\t Conratulations . ALL your Commands excuted Successfully!\t\n"<<endl;
            for (auto n:fo)
            {
                cout<<n;
            }
    // return p;
        
            cout.flush();
    
}


int main (int argc,char* argv[])
{
    
    string cmd;
    for(int i=1;i<argc;i++)
    {
        cmd+=argv[i];
        cout<<argv[i];
    }
    run(cmd);



}