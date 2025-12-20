/*Álvaro Martínez García, 48150407E
ADA. 2021-22
Práctica 5: "Divide y vencerás"
*/
#include <unistd.h>
#include <iostream>
#include <math.h>
#include <iomanip>
#include <vector>

double pasos=0;


using namespace std;

vector<int> diccionario= {1};

bool pow2_0(unsigned long n, unsigned exp){
    
    return (pow(2,exp)==n);
}

//Coste : \theta(log(n))
unsigned long pow2_1(unsigned n ){
    pasos++;


    if(n==0){
        return 1;
    }
    else{
        unsigned long result;
        if(n%2==0){
            result= pow2_1(n/2);
            return (result*result);
        }
        result= pow2_1(n/2);
        return (2*result*result);
    }

}
//Coste : \theta(n^2)
unsigned long pow2_2(unsigned n){
    pasos++;

    if(n==0){
        return 1;
    }
    else{
        n--;
        return ( pow2_2(n) + pow2_2(n));
    }
    
}

//Coste : \theta(n)
unsigned long pow2_3(unsigned n){
    pasos++;

    if(n==0){
        return 1;
    }
    else{
        if((n+1) > diccionario.size()){
            diccionario.push_back(2*pow2_3(n-1));
        }
        return diccionario[n];
    }

}

int main(){
    
    cout << "# pow2_x(n) steps:"
        << endl
        << "# Exp \t\t Steps"
        << endl
        << "# ----------------------------"
        << endl;

    for (int exp = 1; exp < 26; exp++){
        unsigned long check;


        cout << exp << "\t\t" << flush;

        check=pow2_1(exp);
        if(pow2_0(check,exp)){
            cout << pasos << "\t";
            pasos=0;
        }

        check=pow2_2(exp);
        if(pow2_0(check,exp)){
            cout << pasos << "\t";
            pasos=0;
        }

        check=pow2_3(exp);
        if(pow2_0(check,exp)){
            cout << pasos << endl;
            pasos=0;
        }
        diccionario.clear();
        diccionario.push_back(1);

    }

    return 0;
}