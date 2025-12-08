//High relation with arrays
    //When we cout an array without [], we get the location, like pointers

#include<iostream>

using namespace std;

typedef int *tIntegerPointer;   //Can use this so later create them as tIntegerPointer (name), then ypu dont need * because it goes with int

struct tStructure{
    char c;
    int i;
};

int main(){
    int vec[3] = {1,2,3};

    cout << vec << endl;        //Says the address
    cout << *vec << endl;       //Shows just the first element


    int vecs[20];
    int *pVec = vecs;
    *pVec = 58;               //Assign to vecs[0]=58, using this as a shortcut


    int *pv;                //You can use pointers to create dynamic memory
    pv = new int [10];
    pv[0] = 585;
    //...
    delete[] pv;


    tStructure ps;
    ps = new tStructure;
    ps->.c='a';

    return 0;
}