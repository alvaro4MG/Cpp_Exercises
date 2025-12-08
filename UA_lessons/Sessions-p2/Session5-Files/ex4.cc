

#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

int main(){
    ifstream file;
    string s;
    int num1,num2;

    file.open("input.txt");     //Text with "Hello world"

    if(file.is_open()){
        int i=1;
        while(getline(file,s)){     //Most common to read from a file, one line at a time
            cout << i <<": " << s << endl;
            i++;
        }
        //while(!file.eof())         //Read until find the end (eof: end of file), it is a bool

        file.close();
    }
    else{
        cout<<"Couln't open it"<<endl;
    }



    return 0;
}