

#include<iostream>
#include<cstdlib>           //For usign atoi and atof
#include<vector>

using namespace std;

int main(){
    char nums[]="100";

    int num=atoi(nums);     //converts char 100 to int 100
    cout<<num+1<<endl;

    char numsf[]="10.5";

    int numf=atof(numsf);
    cout<<numf+1.2<<endl;


    string s="hello";
    int num=atoi(s.c_str());

    return 0;
}