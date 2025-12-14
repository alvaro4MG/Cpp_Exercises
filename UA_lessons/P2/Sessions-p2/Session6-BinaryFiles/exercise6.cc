//Exercise 6

#include<iostream>
#include<fstream>

using namespace std;

const string KNAME="students.dat";      //Name of file

struct TStudent{
    char id [10];
    char surname [40];
    char name [20];
    int group;
};                          //74 bytes

int main(){
    ifstream file;
    
    file.open(KNAME,ios::binary);

    if(file.is_open()){
        TStudent newStudent;

        while(file.read((char*)&newStudent,sizeof(TStudent))){
            if(newStudent.group==7){
                cout<<newStudent.id<<endl;
            }
        }

        file.close();
    }
    else{
        cout<<"Couldn't open the file"<<endl;
    }

    return 0;
}