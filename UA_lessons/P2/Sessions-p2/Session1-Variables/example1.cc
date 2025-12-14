#include<iostream>

using namespace std;

int main(){
    int i=3;                //from max negative to maxpositive,  if not initialized but shown, you get 0 (in previous version could show random number)
    unsigned j=5;               //only positive part
    unsigned n=-1;          //max postive -n

    for(;i<25;i++)          //You can skip the first condition if used before
        n++;

    cout<<sizeof(int)<<endl;

    return 0;
}