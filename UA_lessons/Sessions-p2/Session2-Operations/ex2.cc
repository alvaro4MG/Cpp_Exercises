#include<iostream>

using namespace std;

int main(){
    
    int i=0;
    while(i<10){
        cout<<i<<endl;
        i++;
    }

    for (int i=0;i<10;i++)  //for loop is more elegant
        cout<<i<<endl;      

    //We can use break in loops, but it will skip the rest of the code in the loop, so if there's a necessary instruction, it wont work 
        //We can use a bool found 

    return 0;
}