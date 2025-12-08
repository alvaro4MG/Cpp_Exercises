//

#include<iostream>
#include<fstream>

using namespace std;

int main(){
    ofstream file ("myFile.txt");        //Can open after declared

    if(file.is_open()){                     //Will return true or false
        cout<<"Opened"<<endl;


        file.close();                       //Close the file after finishing working with it, because there is a limit to the files you can open, better close it in the if opened
    }
    else{
        cout<<"Something was wrong, couldn't open \"myFile.txt\" "<<endl;
    }


    return 0;
}