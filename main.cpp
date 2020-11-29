#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <fstream>
#include <string.h>
#include <string>
#include <sstream>
#include <math.h>

using namespace std;

const int code=123;
const string passer="123";
string file="book_list.txt";
string bno,bn,idate,rdate,sno;
std::vector<std::string> b_no;
std::vector<std::string> b_n;
std::vector<std::string> i_d;
std::vector<std::string> r_d;
std::vector<std::string> s_n;
int f=1;//fine per day
int d=7;//exemption of fine for how many days


void find_if_available();
void display_all_books();
void get_info_wname();
void get_info_wno();
void for_issue();
void display_size();
void set_rd();
void set_id();
void add_to_fine(string stu, int fine);
void book_remove();
int calculate_fine(string idate,string rdate);
void book_add();

int rdn(int y, int m, int d){
    if(m<3)
        y--,m+=12;
    return 365*y +y/4 - y/100 + y/400 + (153*m-457)/5 + d - 306;
}

int main()
{
    int i=0;
    ifstream fileio(file);
    if(fileio.is_open())
    {
        string line;
        getline(fileio,line);

        while(!fileio.eof())
        {
            getline(fileio,bno,',');
            b_no.push_back(bno);
            getline(fileio,bn,',');
            b_n.push_back(bn);
            getline(fileio,idate,',');
            i_d.push_back(idate);
            getline(fileio,rdate,',');
            r_d.push_back(rdate);
            getline(fileio,sno,'\n');
            s_n.push_back(sno);
            i+=1;
        }
        fileio.close();
    }
    else
        cout<<"Unable to open file"<<endl;
    i_d.erase(i_d.end());
    r_d.erase(r_d.end());
    b_no.erase(b_no.end());
    b_n.erase(b_n.end());
    s_n.erase(s_n.end());

    cout<<"WELCOME TO THE LIBRARY DATABASE"<<endl;
    cout<<"Main Menu:\n";
    cout<<"1. Display all books.\n";
    cout<<"2. Find if a book is available in Library.\n";
    cout<<"3. Find if a book is available for issue.\n";
    cout<<"4. Get book info(via book name).\n";
    cout<<"5. Get book info(via book number).\n";
    cout<<"6. Set issue date.\n";
    cout<<"7. Set return date and calculate fine.\n";
    cout<<"8. Add a book to database.\n";
    cout<<"9. Remove a book from database.\n";
    cout<<"10. Display how many books are in the database.\n";
    cout<<"11. Exit Program.\n";
    cout<<"\n";
    int passcode=123;
    int option;
    cout<<"Enter the option: ";
    cin>>option;
    switch(option)
    {
    case 1:
        display_all_books();
        break;
    case 2:
        find_if_available();
        break;
    case 3:
        for_issue();
        break;
    case 4:
        get_info_wname();
        break;
    case 5:
        get_info_wno();
        break;
    case 6:
        set_id();
        break;
    case 7:
        set_rd();
        break;
    case 8:
        book_add();
        break;
    case 9:
        book_remove();
        break;
    case 10:
        display_size();
        break;
    case 11:
        break;
    default:
        cout<<"You input an invalid option."<<endl;
    }

    //writing in file
    std::ofstream outfile(file);
    outfile<<"Book Number,Book Name,Issue Date,Return Date,Student ID Number\n";
    for(int j=0;j<b_n.size();j++)
    {
        outfile<<b_no[j]<<","<<b_n[j]<<","<<i_d[j]<<","<<r_d[j]<<","<<s_n[j]<<"\n";
    }
}

void book_add()
{
    cout<<"For availing this functionality you must enter the password."<<endl;
    cout<<"Password: ";
    string pass;
    cin>>pass;
    if(!pass.compare(passer))
    {
        string n;
        cout<<"Enter the book number: ";
        cin.ignore();
        getline(cin,n);
        int flag=0;
        for(int j=0;j<b_n.size();j++)
        {
            if(!n.compare(b_no[j]))
            {
                flag+=1;
                break;
            }
        }
        if(flag!=0)
        {
            cout<<"This book number already exists."<<endl;
            return ;
        }
        else
        {
            string q;
            cout<<"Enter the book you want to add: ";
            getline(cin,q);
            b_no.push_back(n);
            b_n.push_back(q);
            i_d.push_back("No date");
            r_d.push_back("No date");
            s_n.push_back("No student");
        }
    }
    else
    {
        cout<<"Wrong password."<<endl;
        cout<<"This functionality is not available to you."<<endl;
    }
}

void book_remove()
{
    cout<<"For availing this functionality you must enter the password."<<endl;
    cout<<"Password: ";
    string pass;
    cin>>pass;
    if(!pass.compare(passer))
    {
        string n;
        cout<<"Enter the book number you want to remove: ";
        cin>>n;
        //string q;
        //cout<<"Enter the book name you want to remove: ";
        //getline(cin,q);
        int flag=0;
        for(int j=0;j<b_n.size();j++)
        {
            if(!n.compare(b_no[j]))
            {
                b_no.erase(b_no.begin()+j);
                b_n.erase(b_n.begin()+j);
                i_d.erase(i_d.begin()+j);
                r_d.erase(r_d.begin()+j);
                s_n.erase(s_n.begin()+j);
                flag+=1;
                break;
            }
        }
        if(flag==0)
        {
            cout<<"Book is not available in library database."<<endl;
        }

    }
    else
    {
        cout<<"Wrong password."<<endl;
        cout<<"This functionality is not available to you."<<endl;
    }
}

int calculate_fine(string idate,string rdate)
{
    int rd=stoi(rdate);
    int id=stoi(idate);

    int d2=rd/1000000;
    int m2=rd/10000 - d2*100;
    int y2=rd - m2*10000 - d2*1000000;

    int d1=id/1000000;
    int m1=id/10000 - d1*100;
    int y1=id - m1*10000 - d1*1000000;

    int diff = rdn(y2,m2,d2) - rdn(y1,m1,d1);
    int fine=0;
    if(diff>d)
    {
        fine+=(diff-d)*f;
    }
    cout<<"The fine to be paid is = "<<fine<<endl;
}

void set_rd()
{
    cout<<"For availing this functionality you must enter the password."<<endl;
    cout<<"Password: ";
    string pass;
    cin>>pass;
    if(!pass.compare(passer))
    {
        string n,idate;
        cout<<"Enter the book number: ";
        cin>>n;
        int flag=0;
        int j;
        for(j=0;j<b_n.size();j++)
        {
            if(!n.compare(b_no[j]))
            {
                if(i_d[j].compare("No date"))
                {
                    cout<<"Enter the return date: ";
                    cin>>idate;
                    r_d[j]=idate;
                    cout<<b_no[j]<<"\t\t"<<b_n[j]<<"\t\t"<<i_d[j]<<"\t\t"<<r_d[j]<<"\t\t"<<s_n[j]<<endl;
                    flag+=1;
                    string student=s_n[j];
                    int fine = calculate_fine(i_d[j],r_d[j]);
                    i_d[j]="No date";
                    r_d[j]="No date";
                    s_n[j]="No student";
                    break;
                }
                else
                {
                    cout<<"Book is not available for return as it has not been issued yet."<<endl;
                    flag+=1;
                }
            }
        }
        if(flag==0)
        {
            cout<<"Book is not available in library database."<<endl;
        }
    }
    else
    {
        cout<<"Wrong Password."<<endl;
        cout<<"This functionality is not available to you."<<endl;
    }
}

void display_size()
{
    int j;
    for(j=0;j<i_d.size();j++)
    {
        j+=1;
    }
    cout<<"Number of books = "<<j<<endl;
}

void for_issue()
{
    string q;
    cout<<"Enter book name: ";
    cin.ignore();
    getline(cin,q);
    int flag=0;
    int ctr=0;
    for(int j=0;j<b_n.size();j++)
    {
        if(!q.compare(b_n[j]))
        {
            if(!i_d[j].compare("No date"))
            {
                cout<<"Book is available for issue."<<endl;
                cout<<b_no[j]<<"\t\t"<<b_n[j]<<"\t\t"<<i_d[j]<<"\t\t"<<r_d[j]<<"\t\t"<<s_n[j]<<endl;
                flag+=1;
                ctr+=1;
            }
            else
            {
                flag+=1;
            }
        }
    }
    if(flag==0)
        cout<<"No such book is in library database."<<endl;
    else if(flag!=0 && ctr==0)
        cout<<"Book is not available for issue."<<endl;
}

void set_id()
{
    cout<<"For availing this functionality you must enter the password."<<endl;
    cout<<"Password: ";
    string pass;
    cin>>pass;
    if(!pass.compare(passer))
    {
        string book,idate;
        cout<<"Enter the book number: ";
        cin>>book;
        int flag=0;
        for(int j=0;j<b_n.size();j++)
        {
            if(!book.compare(b_no[j]))
            {
                if(!i_d[j].compare("No date"))
                {
                    cout<<"Enter the issue date: ";
                    cin>>idate;
                    i_d[j]=idate;
                    string s_no;
                    cout<<"Enter the Student id: ";
                    cin>>s_no;
                    s_n[j]=s_no;
                    cout<<b_no[j]<<"\t\t"<<b_n[j]<<"\t\t"<<i_d[j]<<"\t\t"<<r_d[j]<<"\t\t"<<s_n[j]<<endl;
                    flag+=1;
                    break;
                }
                else
                {
                    cout<<"Book is not available for issue."<<endl;
                    flag+=1;
                }
            }
        }
        if(flag==0)
        {
            cout<<"Book is not available in library database."<<endl;
        }
    }
    else
    {
        cout<<"Wrong password."<<endl;
        cout<<"This functionality is not available to you."<<endl;
    }
}

void get_info_wname()
{
    string book;
    cout<<"Enter book name: ";
    cin.ignore();
    getline(cin,book);
    int flag=0;
    for(int j=0;j<b_n.size();j++)
    {
        if(!book.compare(b_n[j]))
        {
            cout<<b_no[j]<<"\t\t"<<b_n[j]<<"\t\t"<<i_d[j]<<"\t\t"<<r_d[j]<<"\t\t"<<s_n[j]<<endl;
            flag+=1;
        }
    }
    if(flag==0)
        cout<<"Book is not available in library database."<<endl;
}

void get_info_wno()
{
    cout<<"Enter book number: ";
    string book;
    cin>>book;
    int j=0;
    int flag=0;
    for(j=0;j<b_n.size();j++)
    {
        if(!book.compare(b_no[j]))
        {
            cout<<b_no[j]<<"\t\t"<<b_n[j]<<"\t\t"<<i_d[j]<<"\t\t"<<r_d[j]<<"\t\t"<<s_n[j]<<endl;
            flag+=1;
            break;
        }
    }
    if(flag==0)
        cout<<"Book is not available in library database."<<endl;
}

void find_if_available()
{
    cout<<"Enter the book name you want to search for: ";
    string q;
    cin.ignore();
    getline(cin,q);
    int flag=0;
    for(int j=0;j<b_n.size();j++)
    {
        if(!q.compare(b_n[j]))
        {
            cout<<"Book is in library database."<<endl;
            flag=1;
            break;
        }
    }
    if(flag==0)
        cout<<"Book is not available in library database."<<endl;
}

void display_all_books()
{
    cout<<"Book Number\t\tBook Name\t\tIssue Date\t\tReturn Date\t\tStudent ID Number"<<endl;
    for(int j=0;j<b_n.size();j++)
    {
        cout<<b_no[j]<<"\t\t"<<b_n[j]<<"\t\t"<<i_d[j]<<"\t\t"<<r_d[j]<<"\t\t"<<s_n[j]<<endl;
    }
}
