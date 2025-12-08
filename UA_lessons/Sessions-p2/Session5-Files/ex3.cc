

#include<iostream>
#include<fstream>

using namespace std;

int main(){
    ifstream file;
    char c;

    file.open("input.txt");     //Text with "Hello world"

    if(file.is_open()){
        /*while(file >> c){       //It ignores blanks
            cout<<c;
        }*/
        while(file.get(c)){     //Doesn't ignore blanks
            cout<<c;
        }

        file.close();
    }
    else{
        cout<<"Couln't open it"<<endl;
    }



    return 0;
}