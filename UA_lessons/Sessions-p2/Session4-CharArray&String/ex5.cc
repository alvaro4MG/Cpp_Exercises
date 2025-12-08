//string methods

#include<iostream>
#include<vector>

using namespace std;

int main(){
    string s="Hello, world";

    cout<<s.length()<<endl;     //Prints 12, better than size

    cout<<s.find("world");          //It shows 7 since it is where it starts
                                        //If not found, it gives string::npos

    if(s.find("world")!=string::npos){ 
        cout<<"Found!"<<endl;               //It finds it, so it is different than string::npos and the condition se cumple
    }

    s.replace(0,5,"hola");      //(first element, size)
    cout<<s<<endl;

    s.erase(4,3);               //(first element, size)
    cout<<s<<endl;                  //from s[4]='o', erase "o w"

    s="hello world";
    string subs=s.substr(2,5);      //Makes a substring
    cout<<s<<endl;
    cout<<subs<<endl;

    //You can compare strings with ==

    string s1="hello";
    string s2="world";
    s2=s1;      //To copy
    string s3=s1+", "+s2;       //Concatenate strings, can also use it as a psuh_back (s = s + 'g')
    cout<<s1<<", "<<s2<<endl;       //Show without other string

    for(unsigned int i=0;i<s1.length();i++){
        s[i]='f';                               //Will change all characters for 'f'
    }


    return 0;
}