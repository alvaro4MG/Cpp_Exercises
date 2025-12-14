//Pa probar cositasssss

#include "Task.h"
#include "List.h"
#include "Util.h"

#include<iostream>
#include<sstream>

using namespace std;

int main(){
    List l("alvaro");
    vector<List> lists;
    Task t("probando");
    bool trying;

    cout<<t.getName()<<endl;

    t.setName("probando2");

    cout<<t.getName()<<endl;

    t.setDeadline("34-07-2030");

    cout << t;

    try{
        cout<<"Hay 2"<<endl;
        if(false)
            throw 2;
        cout<<"Hay 3"<<endl;
    }
    catch(int e){
        cout<<"An exception occurred. Exception numer "<<e<<endl;
    }

    lists.push_back(l);
    lists[0].setName("prob");
    lists[0].addTask(t);
    trying=lists[0].toggleTask("probando2");
    cout<<lists[0];

    string sum,title="My first",s;
    stringstream ss;
    int num=4;
    ss<<num;
    ss>>s;

    sum="("+s+")"+title;

    cout<<sum<<endl;

    sum+="["+s+"]";

    cout << sum <<endl;

    int d;

    if(d<1){
        cout<<"enter id: ";
        cin>>d;
    }

    return 0;
}