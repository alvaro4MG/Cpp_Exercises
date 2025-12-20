#include <iostream>

using namespace std;

int const MAX=7;

void boludeandoVector(int *v){
    v[1]=4;
}

int main(){
    int* v= new int[MAX];
    

    for(int i=0;i<MAX;i++){
        v[i]=i;
    }

    int* w= new int[MAX];

    for(int i=0;i<MAX;i++){
        w[i]=v[i];
    }

    for(int i=0;i<MAX;i++){
        cout<<v[i];
    }
    cout<<endl;
    for(int i=0;i<MAX;i++){
        cout<<w[i];
    }
    cout<<endl;

    boludeandoVector(v);
    for(int i=0;i<MAX;i++){
        cout<<v[i];
    }
    cout<<endl;
    for(int i=0;i<MAX;i++){
        cout<<w[i];
    }
    cout<<endl;

    //Darle la vuelta a w
    for(int i=0;i<MAX/2;i++){
        swap(w[i],w[(MAX-1)-i]);
    }
    cout<<"Dao la vuelta: ";
    for(int i=0;i<MAX;i++){
        cout<<w[i];
    }
    cout<<endl;

    return 0;
}