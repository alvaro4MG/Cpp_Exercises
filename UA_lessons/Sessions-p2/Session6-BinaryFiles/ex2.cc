//"write" function
    //We get the information and then write it into the file
    //Similar to read
    //Two parameters: what to write (with "const char*", because this information isn't going to change), how many bytes
    //Can also use seekp (seek put), if seekp is larger than the file, it will enlarger the file (will make it bigger and occupy more memory)

//"tellg" and "tellp" to know the current position of the pointer

#include<iostream>
#include<fstream>
#include<string.h>
#include<vector>

using namespace std;

const int SIZE=20;

struct TStudent{
    char name [20]; //20 bytes
    int dni;  
    int group;
};

int main(){
    ofstream file("myFile.dat",ios::binary);

    if(file.is_open()){
        TStudent newStudent;
        strcpy(newStudent.name,"Pepito");       //First we get the information
        newStudent.dni=48150407;
        newStudent.group=10;
        
        file.write((const char*)&newStudent,sizeof(TStudent));  //Then we write it

        char str[SIZE];
        string s;
        strncpy(str,s.c_str(),SIZE-1);  //Pass the string to a char array, even if it is smaller
        str[SIZE-1]='\0';

        file.close();
    }
    else{
        cout<<"File couldn't be opened"<<endl;
    }


    return 0;
}