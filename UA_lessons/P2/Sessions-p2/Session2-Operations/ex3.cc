//Arrays

#include<iostream>
#include<string.h>

using namespace std;

//Better set the size in constants or nusm, even though it can be done with variables, which takes the value at that point

int main(){
    int nums[]={1,2,3,4,5,6};   //If you give a list of nums, you dont need to tell the size

    for(int i=4;i>=0;i--){      //To show all positions 4,3,2,1,0
        cout<< nums[i]<<endl;
    }

//Matrix
    int table [5][8];       //A table of 5x8 elements, we can use as much dimensions as we want (like 5)

//Character array
    char cad[]="hello world";   //It ends with \0, indicates where the string stops (when we use "" it always ends like that)
    char cad2[]="hello";            //If \0 isnt written, it shows a strange character dependign on the memory

    cout<<cad<<endl;
    cout<<sizeof(cad2)<<endl;   //It counts the \0, storage required in the memory
    cout<<strlen(cad2)<<endl;   //It doesn't count the \0, it looks for the NULL character to stop, so it looks for it in the memory

    return 0;
}