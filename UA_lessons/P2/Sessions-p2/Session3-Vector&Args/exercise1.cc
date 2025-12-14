//Exercise 1

#include<iostream>
#include<string.h>

using namespace std;

int primeNumber(int n);     //Not necessary
bool testArguments(int argc, char *argv[],int &newLine, int &num_primes);

int main(int argc, char *argv[]){
    int num_primes=10;
    bool newLine=false;

    if(testArguments(argc,argv,newLine,num_primes)){
        //newLine
        //num_primes
        //primeNumber()
    }
    else{
        cout<<"Error: "<<argv[0]<<" [-L] [-N n]"<<endl;
    }


    return 0;
}

bool testArguments(int argc, char *argv[],int &newLine, int &num_primes){
    bool correct=true;

    if(argc>4){
        correct=false;
    }
    else{
        for(int i=1;i<argc && correct;i++){
            if(strcmp(argv[i],"-L")==0){
                newLine=true;
            }
            else if(strcmp(argv[i],"-N")==0){
                if(i<argc-1){
                    num_primes=atoi(argv[i+1]);                     //atoi transforms char in its corresponding int
                    if(num_primes<=0){                                  //If the char isn't a number, atoi will be 0, so it is an error
                        correct=false;
                    }
                    i++;                //We skip the number after, it is not necessary since it was already checked
                }
                else{
                    correct=false;
                }
            }
            else{
                correct=false;
            }
        }
    }

    return correct;
}

/*int main(int argc, char *argv[]){
    int num,prints;

    if(argc>1){
        prints=argv[1];
    }
    else{
        prints=10;
    }

    //for(){}                       //For adding the numbers in a vector by dividign by all of them

    for(int i=1;i<prints;i++){
        cout<<i;

        //if(strcpm(argv[1],"-L")==0){
        if(argc==3){
            cout<<endl;
        }
    }

    return 0;
}*/