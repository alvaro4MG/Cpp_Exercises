//Binary files
    //In binary files we use 0s and 1s copied (if you open it with a text editor, it is all 0s and 1s), not in chraracters
    //Usually use structs, not always, we take advantage of direct access, we have to know exactly the structures so we know where the first and last bit are (thats why we can't use dynamic data)
    //Variables are declared as in text files
    //To use them we have to use ios from before, but also add "| ios::binary"

    //"read" function, to read data from binary files
        //Two parameters: where it is saved, and the amount of information to read
    //"seekg"(seek get) to jump to a byte or group of bytes
        //Two parameters: how many bytes to skip; reference point to make the jump (beg for beginning, cur for current and end for the end of file, where the number can be negative)

#include<iostream>
#include<fstream>

using namespace std;

struct TStudent{
    char name [20]; //20 bytes
    int dni;        //4 bytes
    int group;      //4 bytes
};                      //28 bytes each struct

int main(){
    ifstream file("myFile.dat",ios::binary);
    //Structs of TStudents of 28 bytes

    if(file.is_open()){
        TStudent newStudent;                                    //We create a new variable 
        file.read((char*)&newStudent,sizeof(TStudent));             //First parameter, where I want to save it (newStudent); second parameter how many to read (sizeof returns the size of the variable, 28, could also use newStudent, thats why it is important to know the structs)
                                                                        //(char*) forces the first to be char, avoiding compilation error

        file.seekg(2*sizeof(TStudent),ios::beg);                //Skip the first 2 records from the begginning (beg) and get the pointer there
        file.read((char*)&newStudent,sizeof(TStudent));             //Once the pointer is there, we read


        file.close();
    }
    else{
        cout<<"File couldn't be opened"<<endl;
    }



    return 0;
}