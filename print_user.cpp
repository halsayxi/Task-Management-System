#include "user.h"
using namespace std;

extern string get_hash(string);
extern void DelLineData(string fileName);
extern int debug;
void print_user(string Name, string Password)
{
    string pw, pw_in, pw_in2;
    if (debug == 0) system("clear");

    cout<<"\nPlease enter the password:";
    system("stty -echo");
    if (debug == 0) cin>>pw;
    else
    {
        ifstream testfile("testfile.txt");
        if (!testfile.is_open()) return;
        testfile >> pw;
        testfile.close();
        DelLineData("testfile.txt");
        cout << pw;
    }
    system("stty echo");
    cout<<endl;
    
    pw_in = get_hash(Password);
    pw_in2 = get_hash(pw);
    
    if (pw_in != pw_in2) {cout<<"Wrong password!"; return;}
    cout << "\n=======User Information=======\n";
    cout <<"Username:"<<Name<<endl;
    cout <<"Password:"<<Password<<endl;
}
