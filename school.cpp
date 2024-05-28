#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
using namespace std;
class Student 
{
   public : 
   int rollno,count=0,csp=0;float ps;string sname,fname,mname,doa,add,cn, crs;
   void get()
   {
      cout<<"\n-----Enter Student Details----- ";
      cout<<"\nEnter Student Name : ";
      cin>>sname;
      cout<<"\nEnter Father's Name : ";
      cin>>fname;
      cout<<"\nEnter Mother's Name : ";
      cin>>mname;
      cout<<"\nEnter Date of Admission : ";
      cin>>doa;
      rollno = (rand()%20)+1;count++;
      cout<<"\nEnrolled in the Extra Course ? (yes/no) : ";cin>>crs;
      if(crs=="yes")
      csp++;
      cout<<"\nEnter Contact Number : ";cin>>cn;
      cout<<"\nEnter Address (City): ";cin>>add;
      cout<<"\nEnter Previous Result (Percentage) : ";cin>>ps;
   }
   void display()
   {
       cout<<"\n-------------------------------------";
       cout<<"\nStudent's Name : "<<sname;
       cout<<"\nFather's Name : "<<fname;
       cout<<"\nMother's Name: "<<mname;
       cout<<"\nDate of Admission : "<<doa;
       cout<<"\nRoll Number : "<<rollno;
       cout<<"\nContact Number : "<<cn;
       cout<<"\nExtra Course : "<<crs;
       cout<<"\nAddress (City): "<<add;
       cout<<"\nPrevious Result : "<<ps<<" Percentage";
       cout<<"\n-------------------------------------\n";
   }
};
Student s;
void write()
{
    ofstream fout;
    fout.open("School.dat",ios::app|ios::binary);
    s.get();
    fout.write((char*)&s,sizeof(s));
    fout.close();
    cout<<"\nData Added Successfully...";
}
void read()
{
    ifstream fin;
    fin.open("School.dat",ios::in|ios::binary);
    while(fin.read((char*)&s,sizeof(s)))
    {
        s.display();
    }
    fin.close();
}
void searchrn()
{
    fstream fin;
    int rn,flag=0;
    fin.open("School.dat",ios::in|ios::binary);
    cout<<"\nEnter the Roll Number of the Student whose data you want to Search : ";
    cin>>rn;
    while(fin.read((char*)&s,sizeof(s)))
    {
        if(s.rollno==rn)
        {
            flag=1;
            cout<<"\nRecord Found";
            s.display();
            break;
        }
    }
    if(flag==0)
    {
        cout<<"\nRecord Not Found !!!";
    }
    fin.close();
}
void searchname()
{
    fstream fin;
    int flag=0;string name;
    fin.open("School.dat",ios::in|ios::binary);
    cout<<"\nEnter the Name of the Student whose data you want to Search : ";fflush(stdin);
    getline(cin,name);
    while(fin.read((char*)&s,sizeof(s)))
    {
        if(s.sname.compare(name)==0)
        {
            flag=1;
            cout<<"\nRecord Found";
            s.display();
            break;
        }
    }
    if(flag==0)
    {
        cout<<"\nRecord Not Found !!!";
    }
    fin.close();
}
void update()
{
    int ac,fl=0;string address,contact;char ans1,ans2,ans3;float nps;
    fstream f;
    f.open("School.dat",ios::out|ios::in|ios::binary);
    cout<<"\nEnter the Roll Number of the Student whose Details you want to Update : ";
    cin>>ac;
    while(f.read((char*)&s,sizeof(s)))
    {
        if(s.rollno==ac)
        {
            cout<<"\nDo you want to Update Address ? (y/n) : ";cin>>ans1;
            if(ans1=='y')
            {
            fl=1;
            cout<<"\nRecord Found";
            cout<<"\nEnter the New Address : ";cin>>address;
            int t=f.tellp();
            s.add=address;
            f.seekp(t-sizeof(s));
            f.write((char*)&s,sizeof(s));
            cout<<"\nData Updated Successfully.....";
            }
            cout<<"\nDo you Want to Update Contact Number ? (y/n) : ";cin>>ans2;
            if(ans2=='y')
            {
                fl=1;
            cout<<"\nRecord Found";
            cout<<"\nEnter the New Contact Number : ";cin>>contact;
            int t=f.tellp();
            s.cn=contact;
            f.seekp(t-sizeof(s));
            f.write((char*)&s,sizeof(s));
            cout<<"\nData Updated Successfully.....";
            }
            cout<<"\nDo you want to Update Previous Result of the Student ? (y/n) : ";cin>>ans3;
            if(ans3=='y')
            {
                 fl=1;
            cout<<"\nRecord Found";
            cout<<"\nEnter the Updated Result : ";cin>>nps;
            int t=f.tellp();
            s.ps=nps;
            f.seekp(t-sizeof(s));
            f.write((char*)&s,sizeof(s));
            cout<<"\nData Updated Successfully.....";
            }
            break;
        }
    }
    if(fl==0)
    {
        cout<<"\nRecord Not Found !!!";
    }
    f.close();
    
}
void delete_specific()
{
    int ac,fl=0;
    fstream f;
    f.open("School.dat",ios::in|ios::binary);
    ofstream fout;
    fout.open("new.dat",ios::app|ios::binary);
    cout<<"\nEnter Roll Number of Student whose details you want to delete : ";
    cin>>ac;
    if(s.rollno==ac)
    {
       s.count--;
       if(s.crs.compare("yes")==0)
       s.csp--;
    }
    while(f.read((char*)&s,sizeof(s)))
    {
        if(s.rollno!=ac)
        {

            fout.write((char*)&s,sizeof(s));
        }
        else{
            fl=1;
        }
    }
    f.close();
    fout.close();
    remove("School.dat");
    rename("new.dat","school.dat");
    cout<<"\nSuccessful";
}
void count()
{
    cout<<"\n\nTotal Students in School : "<<s.count<<"\n";
}
void course()
{
    cout<<"\n\nTotal Students Enrolled in Extra Course : "<<s.csp<<"\n";
}
int main()
{
    int ch;
    remove("School.dat");
    while(1)
    {
        cout<<"\nEnter : \n1. Add Student Details\n2. Display Student Details\n3. Search for Specific Student using Roll Number\n4. Search for Specific Student using Name\n5. Update Details of Specific Student\n6. Delete The Details of Specific Student\n7. Display Total count of Students Enrolled in Special Course\n8. Display Total Count of Students\n9. EXIT";
        cout<<"\nEnter Your Choice : ";
        cin>>ch;
        switch(ch)
        {
            case 1:write();break;
            case 2:read();break;
            case 3:searchrn();break;
            case 4:searchname();break;
            case 5:update();break;
            case 6:delete_specific();break;
            case 7:course();break; 
            case 8:count();break;   
            case 9:exit(0);break;       
            default:cout<<"\nInvalid Choice";
        }
    }
}