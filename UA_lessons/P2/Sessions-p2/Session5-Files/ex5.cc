#include<iostream>
#include<fstream>

using namespace std;

const string fileName="input.txt";

int main(){
    ofstream file;

    file.open("input.txt");     //Necessary to open. Even though it can create a file if it doesn't exist, maybe you don't have permission or storage
                                    //If we use ios::app, it will write this after that

    if(file.is_open()){
        file << "First line"<<endl;
        file << "This is the second line. "<<endl;       //Will save in previous, chekc wit ./4
        file <<"This is the last one"<<endl;

        file.close();
    }
    else{
        cout<<"Couln't open"<<fileName<<endl;
    }



    return 0;
}