//The string class

#include<iostream>

using namespace std;

int main(){
    char str[]={"hello"};           //Not necessary to set the size if initialized when declared
    char str2[]={'h','e','l','l','o','\0'};     //Only works with \0 (NULL character) at the end, the size between [] includes \0
    char str3[32];
    int num;

    cout<<str<<endl;

    //When using cin, ignore space, tab or \n (blanks in general), but will ignore the rest of the string after them
        //The rest stays in the buffer, which will give problems to the next string
            //Also problem with int since the getline reads the \n

    //Can also use getline: cin.getline(str,SIZE), reads until \n or SIZE-1

    cout<<"Num: ";
    cin>>num;
    cout<<"Char: ";
    cin.getline(str3,32);           //Problems with \n from int, use before cin.get(), gets \n out of the buffer


    return 0;
}