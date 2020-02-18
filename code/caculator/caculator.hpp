#ifndef CACULATOR_HPP
#define CACULATOR_HPP
#include <iostream>
#include <stack>
#include <string>
#include <cstring>

#define DEBUG true

using namespace std;


#define MAX_LEN 10034 //中缀表达式的最大长度


bool is_cal(char* op)
{


    if (strcmp(op,"+")||strcmp(op,"-")||strcmp(op,"*")||strcmp(op,"/")||strcmp(op,"(")||strcmp(op,")"))
    {

        return  true;
    }
    else
    {
        return false;
    }
}



int op_priority(char* op)
{
//    op=const_cast<char>(op);

if(strcmp(op,"+")|| strcmp(op,"-"))
{
    return 1;

}
else if (strcmp(op,"*")|| strcmp(op,"/")) {
 return 2;
}
else if (strcmp(op,"(")|| strcmp(op,")")) {
 return 3;
}
else
{
    throw ("caculation operator not legal!");
}
}


//常规表达式转后缀表达式（逆波兰表达式）
//返回应该是string字符串
double caculate(string& regular)
{
    stack<char*> num;
    stack<char> op;

    if (regular.empty())
    {

        cout << "Expression is blank!!!!";
        exit(1);
    }
    else
    {
        stack<string> polish_expression = {};
        auto it = regular.begin();

          for (size_t i = 0; i < regular.length(); i++)
        {
             char *tmp;


            if (*it >= '0' && *it <= '9')
            {

                tmp+=*it;
                it++;

            }
            else
            {
                num.push(tmp);
                if (is_cal(&(*it))) //数字后面跟着符号，否则不合理
                {
                    if(strcmp(&(*it),"("))
                    {
                        op.push((*it));
                        it++;
                    }else if(strcmp(&(*it),")"))
                    {
                        while(!strcmp(&op.top(),")") )
                        {
                            num.push(&op.top());
                            op.pop();
                        }
                        op.pop(); //弹出） 操作符

                        it++;
                    }else{

                        int prority=op_priority(&(*it));
                        if(prority>op_priority(&op.top()))
                        {
                            op.push(*it);

                        }else if(prority < op_priority(&op.top()) || ! (strcmp(&op.top(),"("))){
                            while (prority< op_priority(&op.top())) {
                                num.push(op.top());
                                op.pop();
                            }




                        }
                        else if((strcmp(&op.top(),"("))) //如果操作符是“（”
                        {

                            num.push(*it);
                        }else{

                            if (!op.empty())
                            {

                                while(!op.empty() )
                                {
                                    num.push(op.top());
                                    op.pop();
                                }

                            }
                        }


                        it++;
                    }


                }
                else
                {
                    throw("caculator not illegal !"); //不合理，抛出异常
                }

            }


        }






    } //函数结束

//测试波兰表达式的代码。
//后面可以把 DEBUG 定义去掉，就不会编译此处了
#ifdef DEBUG

   while(!num.empty())
   {
      cout<<num.top()<<"\t";
      num.pop();
   }


   while(!op.empty())
   {
      cout<<op.top()<<"\t";
      op.pop();
   }

    cout <<endl;


#endif


    return 0;

}



#endif // CACULATOR_HPP
