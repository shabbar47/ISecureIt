#include "search.h"
#include "calculator.h"
#include<stdlib.h>
#include<conio.h>
#include<string>
#include<string.h>
#include<iostream>
#include<math.h>
#include "hash.h"
#include<windows.h>
#include<iomanip>

using namespace std;

void setSecurityQuestions(string userName,int row);
void signIn();
void resetPassword(string userName);





void signUp()
{
    search s;
    string userName,password,confirmPassword;
    char answer;
    cout<<endl;
        cout<<"---------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<endl<<setw(50)<<"Sign Up:"<<endl;
    cout<<"Username:";
    cin>>userName;
    if(s.getUser(userName)){
        cout<<"\n Username already exists.\n";
        cout<<"Do you want to sign in instead?(Y/N):";
        cin>>answer;
        while(true){
        if(answer=='y'|| answer=='Y'){
            signIn();
            return;
        }else if(answer=='n' || answer=='N'){
            return;
        }else{
            cout<<"Invalid Option"<<endl;
            return;
        }            cout<<"Confirm Password :";
            cin>>confirmPassword;
        }
    }
    else{
            cout<<"Password : ";
            cin>>password;
            cout<<"Confirm Password :";
            cin>>confirmPassword;
            if(password == confirmPassword)
            {
                fstream fusers;
                fusers.open("userpass.csv",ios::app);
                int row=getLastRow()+1;
                password=hasher(password);
                fusers<<row<<","<<userName<<","<<password<<"\n";
                fusers.close();
                fusers.open("Accounts.csv",ios::app);
                fusers<<row<<","<<userName<<","<<1<<"\n";
                fusers.close();
                setSecurityQuestions(userName,row);
                cout<<"Account Created Successfully"<<endl;
            }
            else
            {
                cout<<"Password does not match"<<endl;
                cout<<"Please try again.."<<endl;
                signUp();
            }

    }
}

void forgotPassword()
{
    string row;
    string user,userName;
    string questions[2],answer[2],ans[2];
    string question;
    ifstream inf;
    search s;
    cout<<"Enter your user name : ";
    cin>>userName;
    if(s.getUser(userName))
    {
     int rowNumber=getRow(userName);
    inf.open("SecurityQuestions.csv");
    for(int i=0;i<rowNumber;i++)
    {
        getline(inf,row,',');
        getline(inf,user,',');
        if(i==rowNumber-1)
        {
            getline(inf,questions[0],',');
            getline(inf,answer[0],',');
            getline(inf,questions[1],',');
            getline(inf,answer[1]);
        }
        getline(inf,question);
    }
    cout<<questions[0]<<endl;
    cin>>ans[0];
    cout<<questions[1]<<endl;
    cin>>ans[1];
    if(ans[0]==answer[0]&&ans[1]==answer[1])
    {
        resetPassword(userName);
    }
    else
    {
        int ans;
            cout<<"Wrong Answer"<<endl;
            cout<<"Do you wish to:"<<endl;
            bool i=true;
            while(i)
             {
                 cout<<"1.Create a new account \n2.Try again. \n3.Cancel"<<endl;
                cout<<"Option:";
                cin>>ans;
                if(ans==1)
                {
                    signUp();
                    return;
                }
                else if(ans==2)
                {
                    forgotPassword();
                    return;
                }
                else if(ans==3)
                {
                    return;
                }
                else
                {
                    cout<<"Invalid option, please try again."<<endl;
                }
            }
    }
    }
    else
    {
        cout<<"Please provide a valid username."<<endl;
        return;
    }
}


void setSecurityQuestions(string userName,int row)
{
    int i;
     string question1,question2,ans1,ans2;
    fstream fquestions;
    fquestions.open("SecurityQuestions.csv",ios::app);
    cout<<"Please set security questions for recovering \n";
    cout<<"1.Do you want to frame your own question"<<endl;
    cout<<"2.Do you want to use the default questions "<<endl;
    cout<<"Option:";
    cin>>i;
        switch(i)
        {
            case 1:     cout<<"Type you first question :";
                        cin.sync();
                        getline(cin,question1);
                        cout<<" \n Answer :";
                        cin.sync();
                        getline(cin,ans1);
                        cout<<"Type your second question :";
                        getline(cin,question2);
                        cout<<"\n Answer :";
                        getline(cin,ans2);
                      // fquestions<<"\n"<<row<<","<<userName<<","<<question1<<","<<ans1<<","<<question2<<","<<ans2;
                        break;

            case 2:     question1="programmer?";
                        cout<<question1;
                        cout<<" \n Answer :";
                        cin>>ans1;
                        question2="vegan?";
                        cout<<question2;
                        cout<<"\n Answer :";
                        cin>>ans2;
                       // fquestions<<"\n"<<row<<","<<userName<<","<<question1<<","<<ans1<<","<<question2<<","<<ans2;
                        break;
        }
        //int Row=getLastRow()+1;
       fquestions<<row<<","<<userName<<","<<question1<<","<<ans1<<","<<question2<<","<<ans2<<"\n";
}

    void signIn()
    {
        search s;int i=0;
        string userName,password;
        char c;
        cout<<endl;
        cout<<"---------------------------------------------------------------------------------------------------------------------"<<endl;
        cout<<endl<<setw(50)<<"Sign In:"<<endl;
        for(i=0;i<3;i++ )
        {
        cout<<"UserName :";
        cin>>userName;
        if(s.getUser(userName))
        {
            cout<<"Password :";
            for(int i=0;i<1000;i++)
            {
            c=getch();
            if(c=='\r')
                break;
            password+=c;
            }
            cout<<endl;
        }
        else
        {
            int ans;
            cout<<"This user does not exist."<<endl;
            cout<<"Do you wish to:"<<endl;
            bool i=true;
            while(i)
             {
                 cout<<"1.Create a new account \n2.Try again.\n3.Cancel"<<endl;
                cin>>ans;
                if(ans==1)
                {
                    signUp();
                    return;
                }
                else if(ans==2)
                {
                    signIn();
                    return;
                }
                else if(ans==3)
                {
                    return;
                }
                else
                {
                    cout<<"Invalid option, please try again."<<endl;
                }
             }

        }


        if(hasher(password)==s.getPassword(userName))
        {
           int b=1;
            while(b)
            {
            fstream upass,uacc,udel;
            string accName,acc,pass,previousAbove;
        string user="",accounts="";
        string above,below="",required;
        int a=1,c=1;
        char character;
        string row,r="";
            i=4;
            char n;
            //system("CLS");
            cout<<"Select an option: "<<endl;
            cout<<"1. View accounts 2. Add accounts 3. Delete account 4.Reset Password 5.SignOut "<<endl;
            cout<<"Option:";
            cin>>n;

         switch(n)
         {
             case '1':
                        upass.open("Accounts.csv");
                        while(upass)
                        {
                            getline(upass,row,',');
                            getline(upass,user,',');
                            getline(upass,accounts);
                            if(user==userName)
                            {
                                if(accounts=="1"){
                                    cout<<endl<<"You don't have any accounts."<<endl<<endl;
                                }
                                else{
                                cout<<endl<<"Accounts:"<<endl<<accounts<<endl<<endl;

                                }
                                break;
                            }
                        }
                        upass.close();
                        break;

            case '2':
                    cout<<"Add account:"<<endl;
                        cout<<"Enter account name(Facebook,Gmail,etc):";
                        cin>>accName;
                        cout<<"Enter your account's Username/Email:";
                        cin>>acc;
                        cout<<"Enter the account's password:";
                        for(int i=0;i<1000;i++)
            {
            character=getch();
            if(character=='\r')
                break;
            pass+=character;
            }
                       // cin>>pass;
                            uacc.open("Accounts.csv",ios::in);
                            // cout<<uacc.is_open();
                         while(uacc)
                        {
                           if(a)
                           {
                            if (r!="")
                            previousAbove+= r + "," + user + "," + accounts + "\n" ;

                            getline(uacc,r,',');
                            getline(uacc,user,',');
                            getline(uacc,accounts,'\n');


                            if(user==userName)
                            {
                                if(accounts=="1"){
                                previousAbove+= r + "," + user + "," + accName + "," + acc + "," + pass + ":" + "\n";
                                }
                                else{
                                    previousAbove+= r + "," + user + "," + accounts + accName + "," + acc + "," + pass + ":" + "\n" ;
                                }
                                cout<<"Account Successfully added."<<endl;
                                //cout<<"Press any key to continue...";
                                a=0;
                                if(toint(r)==getLastRow()){
                                    uacc.close();
                                    break;
                                }
                            }
                            }
                            else if(toint(r)<getLastRow()){
                                getline(uacc,r,',');
                                getline(uacc,user,',');
                                getline(uacc,accounts,'\n');
                                below+= r + "," + user + "," + accounts + "\n" ;
                                if(toint(r)==getLastRow()){
                                    uacc.close();
                                    break;
                                }
                            }
                        }
                                uacc.open("Accounts.csv",ios::out);
                                uacc<<previousAbove<<below;
                                uacc.close();

                          //      cout<<previousAbove<<endl<<below;
                                break;
                case '3':         //cout<<"Delete accounts: \n";
                                udel.open("Accounts.csv",ios::in); //For deleting from Accounts.csv
                                while(udel)
                        {
                           if(c)
                           {
                            if (r!="")
                            previousAbove+= r + "," + user + "," + accounts + "\n" ;

                            getline(udel,r,',');
                            getline(udel,user,',');
                            getline(udel,accounts,'\n');


                            if(user==userName)
                            {
                                previousAbove+= r + "," + "??" + "," + "??" + "," + "??" + "," + "??" + "\n";

                               // cout<<"Account Deleted Successfully."<<endl;
                                c=0;
                                if(toint(r)==getLastRow()){
                                    udel.close();
                                    break;
                                }
                            }
                            }
                            else if(toint(r)<getLastRow()){
                                getline(udel,r,',');
                                getline(udel,user,',');
                                getline(udel,accounts,'\n');
                                below+= r + "," + user + "," + accounts + "\n" ;
                                if(toint(r)==getLastRow()){
                                    udel.close();
                                    break;
                                }
                            }
                        }
                                udel.open("Accounts.csv",ios::out);
                                udel<<previousAbove<<below;
                                udel.close();
                                c=1; r=""; user=""; accounts=""; previousAbove=""; below="";

                        udel.open("userpass.csv",ios::in); //For deleting from userpass.csv
                                while(udel)
                        {
                           if(c)
                           {
                            if (r!="")
                            previousAbove+= r + "," + user + "," + accounts + "\n" ;

                            getline(udel,r,',');
                            getline(udel,user,',');
                            getline(udel,accounts,'\n');


                            if(user==userName)
                            {
                                previousAbove+= r + "," + "??" + "," + "??" + "," + "??" + "," + "??" + "\n";

                               // cout<<"Account Deleted Successfully."<<endl;
                                c=0;
                                if(toint(r)==getLastRow()){
                                    udel.close();
                                    break;
                                }
                            }
                            }
                            else if(toint(r)<getLastRow()){
                                getline(udel,r,',');
                                getline(udel,user,',');
                                getline(udel,accounts,'\n');
                                below+= r + "," + user + "," + accounts + "\n" ;
                                if(toint(r)==getLastRow()){
                                    udel.close();
                                    break;
                                }
                            }
                        }
                                udel.open("userpass.csv",ios::out);
                                udel<<previousAbove<<below;
                                udel.close();
                                c=1; r=""; user=""; accounts=""; previousAbove=""; below="";

                        udel.open("SecurityQuestions.csv",ios::in); //For deleting from SecurityQuestions.csv
                                while(udel)
                        {
                           if(c)
                           {
                            if (r!="")
                            previousAbove+= r + "," + user + "," + accounts + "\n" ;

                            getline(udel,r,',');
                            getline(udel,user,',');
                            getline(udel,accounts,'\n');


                            if(user==userName)
                            {
                                previousAbove+= r + "," + "??" + "," + "??" + "," + "??" + "," + "??" + "\n";

                                cout<<"Account Deleted Successfully."<<endl;
                                c=0;
                                if(toint(r)==getLastRow()){
                                    udel.close();
                                    break;
                                }
                            }
                            }
                            else if(toint(r)<getLastRow()){
                                getline(udel,r,',');
                                getline(udel,user,',');
                                getline(udel,accounts,'\n');
                                below+= r + "," + user + "," + accounts + "\n" ;
                                if(toint(r)==getLastRow()){
                                    udel.close();
                                    break;
                                }
                            }
                        }
                                udel.open("SecurityQuestions.csv",ios::out);
                                udel<<previousAbove<<below;
                                udel.close();
                                return;

                                break;
                case '4':         resetPassword(userName);
                                break;
                case '5':         b=0;
                                break;
                default:        cout<<"Please enter a valid option."<<endl;
                                break;
        }
    }
        }
    else
    {
        cout<<"wrong password \n";
            return;
            //forgot pass;
    }
    }
}
void resetPassword(string userName)
{
    fstream udel;
    string user="",password="", r = "" , previousAbove="";
    string newPass,confirmPassword, below= "";
    int c=1;
    cout<<"Please enter your new password."<<endl;
    cin>>newPass;
    cout<<"Please confirm your new password."<<endl;
    cin>>confirmPassword;
    if(newPass==confirmPassword)
    {

            udel.open("userpass.csv",ios::in); //For deleting from userpass.csv
                                while(udel)
                        {
                           if(c)
                           {
                            if (r!="")
                            previousAbove+= r + "," + user + "," + password + "\n" ;

                            getline(udel,r,',');
                            getline(udel,user,',');
                            getline(udel,password,'\n');


                            if(user==userName)
                            {
                                previousAbove+= r + "," + user + "," + hasher(newPass) + "\n";
                                c=0;
                                if(toint(r)==getLastRow()){
                                    udel.close();
                                    break;
                                }
                            }
                            }
                            else if(toint(r)<getLastRow()){
                                getline(udel,r,',');
                                getline(udel,user,',');
                                getline(udel,password,'\n');
                                below+= r + "," + user + "," + password + "\n" ;
                                if(toint(r)==getLastRow()){
                                    udel.close();
                                    break;
                                }
                            }
                        }
                                udel.open("userpass.csv",ios::out);
                                udel<<previousAbove<<below;
                                udel.close();
                                cout<<"Your password is reset"<<endl;
            }
}


main()
{
    calc();
    search s;
    int i,n=1, counter=0;
    while(n)
    {
        if(counter){
        system("Pause");
        }
        counter=1;
        system("CLS");
        cout<<"\n \n \n";
        cout<<setw(74)<<" _____                              _____ _  "<<endl;
        cout<<setw(75)<<"|_   _|                            |_   _| |  "<<endl;
        cout<<setw(78)<<"  | |  ___  ___  ___ _   _ _ __ ___  | | | |_    "<<endl;
        cout<<setw(75)<<"  | | / __|/ _ \\/ __| | | | '__/ _ \\ | | | __|"<<endl;
        cout<<setw(75)<<" _| |_\\__ \\  __/ (__| |_| | | |  __/_| |_| |_ "<<endl;
        cout<<setw(75)<<"|_____|___/\\___|\\___|\\__,_|_|  \\___|_____|\\__|"<<endl;
        cout<<""<<endl;
        //cout<<setw(50)<<"1.Sign In \n2.Sign Up \n3.Forgot Password \n4.Exit"<<endl;
        cout<<setw(55)<<"1.Sign In \n";
        cout<<setw(55)<<"2.Sign Up \n";
        cout<<setw(63)<<"3.Forgot Password \n";
        cout<<setw(52)<<"4.Exit \n";
        cout<<setw(51)<<"Option:";
        cin>>i;
        switch(i)
        {
            case 1: //cout<<"Main case 1"<<endl;
                    signIn();
                    break;
            case 2: //cout<<"Main case 2"<<endl;
                    signUp();
                    break;
            case 3: forgotPassword();
                    break;
            case 4: n=0;
        }
         cout<<"--------------------------------------------------------------"<<endl;
    }
    cout<<"End Of Program."<<endl;
}














