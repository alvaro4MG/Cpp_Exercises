//Exercise2

#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

const string inputName = "file.txt";
const string outputFile = "FILE.txt";

int main(){
    ifstream fileInput;
    ofstream fileOutput;

    fileInput.open(inputName,ios::in);
    if(fileInput.is_open()){
        fileOutput.open(outputFile,ios::out);
        if(fileOutput.is_open()){
            string line;

            while(getline(fileInput,line))
                cout<<toupper(line)<<endl;

            fileOutput.close();
        }
        else{
            cout<<"Coulnd't open it"<<endl;
        }

        fileInput.close();
    }
    else{
        cout<<"Coulnd't open it"<<endl;
    }
    


    return 0;
}