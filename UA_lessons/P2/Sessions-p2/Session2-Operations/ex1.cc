#include<iostream>

using namespace std;

int main(){
    int a=7;
    float b=3;

    cout<< 7/2 <<endl;      //You only get 3, since it gives the integer of the division
    cout<< a/b <<endl;          //Unless one is a float or we change the data type of a
    cout << (float)a/b <<endl;
    cout<< (float)(3/7) <<endl;     //Here we change already 3 to float, so it wont be enough

    // The % operand
    int num;

    cin>>num;
    cout<<"Days: "<<num/24<<endl;
    cout<<"Hours: " <<num%24 <<endl;

        //The negation and increment/decrement have the most precedence, before mult and div

    if(num==5)                              //The result of (num=5) is 5, which is different of NULL (0), so it is true, if (num=0 and only 0), it is false
        cout<<"They are equal"<<endl;
    else
        cout<<"They are not equal"<<endl;
    
    cout << (10<21) <<endl;                 //It shows 1 (true) or 0 if it was false

    //Short circuit evaluation
        //In &&, if the left is false (false && A), it won't evaluate the second, so A&&B != B&&A
        //Happens the same with || and true on left
    for(int i=0;i<10 && vec[i]!=6;i++){     //This way is correct, but not the other way of the &&
        cout<< i<<endl;
        i++;
    }

    cout<< "I am cout"<<endl;       //If written in console ex1 > output.txt, cout will be in the new file output.txt
    cerr<< "I am cerr"<<endl;           //To pass this, we use ex1 2>output.txt, it is useful g++... ex1 2>output.txt and check the errors

    

    return 0;
}