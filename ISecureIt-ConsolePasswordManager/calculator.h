#ifndef CALCULATOR_H_INCLUDED
#define CALCULATOR_H_INCLUDED

#include<iostream>
#include<string.h>
#include<math.h>
using namespace std;
template<class T>
class Calc
{
private:
    int res,IsRes;
public:
    Calc();
    void Start(T res,T IsRes);
    T Add(T x,T y);
    T Sub(T x,T y);
    T Mult(T x,T y);
    T Div(T x,T y);
    T tonum(string str);
    void Clear();

};
template<class T>
Calc<T>::Calc()
{
    res=0;
    IsRes=0;
}
template<class T>
void Calc<T>::Start(T res,T IsRes)
{
    if(IsRes==1)
        cout<<"\t Result ="<<res<<endl;
    cout<<"Enter the choice of operation :"<<endl;
    cout<<"\t1.Addition \n\t2.Subtraction \n\t3.Multiplication \n\t4.Division \n\t0.Clear"<<endl;
}
template<class T>
T Calc<T>::Add(T x,T y)
{
    return(x+y);
    IsRes=1;
}
template<class T>
T Calc<T>::Sub(T x,T y)
{
    return(x-y);
    IsRes=1;
}
template<class T>
T Calc<T>::Mult(T x,T y)
{
    return(x*y);
    IsRes=1;
}
template<class T>
T Calc<T>::Div(T x,T y)
{
    return(x/y);
    IsRes=1;
}
template<class T>
void Calc<T>::Clear()
{
    res=0;
}
template<class T>
T Calc<T>::tonum(string str)
{
    int num=0,size=str.size();
    for(int i =0,j=size;i<size;i++)
        num+=(str[--j]-'0')*pow(10,i);
    return num;
}
void calc()
{
    Calc <int> A;
    int stop=0,ch,result=0,IsRes=0;
    while(stop!=1)
    {
        A.Start(result,IsRes);
        cin>>ch;
        switch(ch)
        {
        case (1):
            {
                if(IsRes==0)
                {
                   // clrscr();
                    cout<<"Enter the  operands:";
                    int a,b;
                    cin>>a>>b;
                    result=A.Add(a,b);
                    IsRes=1;
                    break;
                }
                else
                {
                   // clrscr();
                    cout<<"Enter the next operand:";
                    int a;
                    cin>>a;
                    result=A.Add(result,a);
                    break;
                }
            }
        case (2):
            {
                if(IsRes==0)
                {
                   // clrscr();
                    cout<<"Enter the  operands:";
                    int a,b;
                    cin>>a>>b;
                    result=A.Sub(a,b);
                    IsRes=1;
                    break;
                }
                else
                {
                   // clrscr();
                    cout<<"Enter the next operand:";
                    int a;
                    cin>>a;
                    result=A.Sub(result,a);
                    break;
                }
            }
            case (3):
            {
                if(IsRes==0)
                {
                   string s[2];
                   cout<<"Enter the  operands:";
                   cin>>s[0]>>s[1];
                   if(s[0]=="open"&&s[1]=="sesame")
                    {
                        return;
                    }
                   else
                   {
                        int a,b;
                        a=A.tonum(s[0]);
                        b=A.tonum(s[1]);
                        result=A.Mult(a,b);
                        IsRes=1;
                        break;
                    }
                }
                else
                {
                    string s;
                    cout<<"Enter the next operand:";
                    cin>>s;
                    int a;
                    a=A.tonum(s);
                    result=A.Mult(result,a);
                    break;
                }
            }
            case (4):
            {
                if(IsRes==0)
                {
                   // clrscr();
                    cout<<"Enter the  operands:";
                    int a,b;
                    cin>>a>>b;
                    result=A.Div(a,b);
                    IsRes=1;
                    break;
                }
                else
                {
                   // clrscr();
                    cout<<"Enter the next operand:";
                    int a;
                    cin>>a;
                    result=A.Div(result,a);
                    break;
                }
            }
            case (0):
            {
                IsRes=0;
                result=0;
                break;
            }
        }
    }

}


#endif // CALCULATOR_H_INCLUDED
