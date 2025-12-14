//Enum types and arguments

#include<iostream>
#include<vector>

using namespace std;

int main(int argc, char *argv[]){         //main can receive argc and argv
                    //int argc: number of arguments passed to the program, including the name
                    //char *argv[]: 
    enum colour {black,blue,green,red};     //Enumerator type, 4 enumerator
    enum animal {cat,dog,fish,monkey};

    cout<<dog<<endl;                        //Dog is 1 in integers


    cout<<"I have "<<argc<<" arguments"<<endl;      //In terminal, write -L,-O,super,etc and those are the arguments, separated by spaces (they usually start with the dash -)

    for(int i=0;i<argc;i++){
        cout<< argv[i]<<endl;                   //First argument will be the name of the program
    }


    return 0;
}