#ifndef SEARCH_H_INCLUDED
#define SEARCH_H_INCLUDED
#include<iostream>
#include<fstream>
#include<string>
#include<string.h>
#include<math.h>
using namespace std;

long int p, q, n, t, flag, e[100], d[100], temp[100], j, m[100], en[100], i;
char msg[100];
int prime(long int);
void ce();
long int cd(long int);
string encrypt(string password);
string decrypt(string password);

int toint(string str)
{
    int num=0,size=str.size();
    for(int i =0,j=size;i<size;i++)
        num+=(str[--j]-'0')*pow(10,i);
    return num;
}

int getRow(string username)
{
    string row="";
    string user;

    string password;
    ifstream inf;
    inf.open("userpass.csv");
    while(inf)
    {
       //
        getline(inf,row,',');
        getline(inf,user,',');
        getline(inf,password);
        if(user==username)
        {
            inf.close();
            return toint(row);
        }
    }
    return 0;
}

int getLastRow()
{
    string row;
    string user;
    string password;

    ifstream inf;
    inf.open("userpass.csv");
    int counter=-1;
    while(inf)
    {
        getline(inf,row,',');
        getline(inf,user,',');
        getline(inf,password);
        counter++;
    }
        return counter;
}

class search{
    public:
    string getPassword(string username);
    string getAccounts(string username);
    string getQuestions(string username);
    bool getUser(string username);
};

string search::getPassword(string username)
{
    int rowNumber=getRow(username);
    string row;
    string user;
    string password;
    ifstream inf;
    inf.open("userpass.csv");
    for(int i=0;i<rowNumber;i++)
    {
        getline(inf,row,',');//cout<<row<<endl;
        getline(inf,user,',');//cout<<user<<endl;
        getline(inf,password);
    }
    return password;
}

string search::getAccounts(string username)
{
    int rowNumber=getRow(username);
    string row;
    string user;
    string accounts;
    ifstream inf;
    inf.open("Accounts.csv");
   // cout<<rowNumber;
    for(int i=0;i<rowNumber;i++)
    {
        getline(inf,row,',');
        getline(inf,user,',');
        getline(inf,accounts);
    }
    return accounts;
}

string search::getQuestions(string username)
{
    string row;
    string user;
    string questions;
    ifstream inf;
     int rowNumber=getRow(username);
    inf.open("SecurityQuestions.csv");
    for(int i=0;i<rowNumber;i++)
    {
        getline(inf,row,',');
        getline(inf,user,',');
        getline(inf,questions);
    }
    return questions;
}

bool search::getUser(string username)
{
    string row;
    string user;
    string password;
    ifstream inf;
    inf.open("userpass.csv");
    while(inf)
    {
        getline(inf,row,',');
        getline(inf,user,',');
        getline(inf,password);
        if(user==username)
        {
            inf.close();
            return 1;
        }
    }
    return 0;
}



void ce()
{
    int k;
    k = 0;
    for (i = 2; i < t; i++)
    {
        if (t % i == 0)
            continue;
        flag = prime(i);
        if (flag == 1 && i != p && i != q)
        {
            e[k] = i;
            flag = cd(e[k]);
            if (flag > 0)
            {
                d[k] = flag;
                k++;
            }
            if (k == 99)
                break;
        }
    }
}
long int cd(long int x)
{
    long int k = 1;
    while (1)
    {
        k = k + t;
        if (k % x == 0)
            return (k / x);
    }
}




string encrypt(string password)
{
    p=29;
    q=71;
    for(int j=0;password[j]!='\0';j++)
        msg[j]=password[j];
    for (i = 0; msg[i] != '\0'; i++)
        m[i] = msg[i];
    n = p * q;
    t = (p - 1) * (q - 1);
    ce();
    long int pt, ct, key = e[0], k, len;
    i = 0;
    len = strlen(msg);
    while (i != len)
    {
        pt = m[i];
        pt = pt - 96;
        k = 1;
        for (j = 0; j < key; j++)
        {
            k = k * pt;
            k = k % n;
        }
        temp[i] = k;
        ct = k + 96;
        en[i] = ct;
        i++;
    }
    en[i] = -1;
    string pass;
    for (i = 0; en[i] != -1; i++)
//        printf("%c", en[i]);
        pass+=en[i];
        return pass;
}

string decrypt(string password)
{
    p=29;
    q=71;
    for(int j=0;password[j]!='\0';j++)
        msg[j]=password[j];
    for (i = 0; msg[i] != '\0'; i++)
        m[i] = msg[i];
    n = p * q;
    t = (p - 1) * (q - 1);
    ce();
    long int pt, ct, key = d[0], k;
    i = 0;
    while (en[i] != -1)
    {
        ct = temp[i];
        k = 1;
        for (j = 0; j < key; j++)
        {
            k = k * ct;
            k = k % n;
        }
        pt = k + 96;
        m[i] = pt;
        i++;
    }
    m[i] = -1;
    string pass;
   for (i = 0; m[i] != -1; i++)
//        printf("%c", en[i]);
        pass+=m[i];
        return pass;
}


int prime(long int pr)
{
    int i;
    j = sqrt(pr);
    for (i = 2; i <= j; i++)
    {
        if (pr % i == 0)
            return 0;
    }
    return 1;
}



#endif // SEARCH_H_INCLUDED
