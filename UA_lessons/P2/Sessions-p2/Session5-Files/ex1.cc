//Files
    //Until now, we worked with RAM (which is volatile) and it is deleted after we finish
    //Files are dynamic structures, size may vary during execution, and they can be text files and binary files (today we'll see text files)
    //You can access from sequential access (read and write from the beginning, one after other) and direct/random access (read and write any position without seeing the previous)

    //Text files:
        //Stores information as a character sequence (and usually use sequential access, you don't know where lines start and end)
        //They use the characters from ASCII (the ones from 32, which are the printables)
        //Use library fstream, 3 basic data types: ifstream (Read only), ofstream (Write only) and stream (read and write, it is unusual with text files, only when all the lines are the same length, otherwise they can sobreescribirse)
        //This logical file must be associated with physical file, must be opened with file.open("myFile.txt")

#include<iostream>
#include<fstream>

using namespace std;

int main(){
    //iftream file;             //Read from file

    //file.open("myFile.txt");  //Even when you use it, you must forget the OG name, we will use the variable

    ifstream file;

    file.open("myFile.txt");            //Created in console with touch myFile.txt, when it is in the same directory (to refer to its location, write ./"folder"/..., for posterior folder, to go to parent folder, ../"folder"/"file", but can also use the whole/absolute path (or rayita de ñ before /...), see it with pwd, but may give problems between computers)
    file.open("myFile.txt", ios::in);        //This to read only (it is by default), ios::out to write (or this is default, dependign on type of struct), ios::in|ios::out to read/write, ios::out|ios::app to add information at the end (append mode)
                                                //If data structure and ios is different (ofstream and ios::in), you can't read it
                                                //If you open to write and the file doesn't exist, one will be created with size 0


    return 0;
}