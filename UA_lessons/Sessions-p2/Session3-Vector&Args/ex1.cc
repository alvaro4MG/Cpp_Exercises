//STL vectors

#include<iostream>
#include<vector>        //From Standard Template Library (STL), not worrying about the size
//Define vector: vector <int> vec; (not necessary to say its size, initial size is 0, it grows dinamically as required)
    //Add elements at the end of the vector: vec.puch_back(12)(adds 12 at the end)
    //vec.push_back(8): Add 8 after 12, vector is a class, so methods use a point
    //We see the size of the vector wth vec.size()

using namespace std;

int main(){
    vector <int> vec(8);    //We get 8 spaces directly, we can also use resize()
    vector <int> vec2;

    vec.push_back(10);

    vec[0]=12;
    vec.push_back(8);           //We can't set them with vec[1]=??, because the memory doesn't exist, you have to use the push_back
    vec.push_back(35);

    for(int i=0;(unsigned)i<vec.size();i++){         //We use unsigned for i since vec.size can't be negative, so it is better, see this with -Wall
        cout<<vec[i]<<endl;
    }

    cout<<"Size: "<<vec.size()<<endl;

    vec2.push_back(9);
    vec2.push_back(10);
    vec2.push_back(11);
    vec2.push_back(12);
    vec2.push_back(13);
    vec2.erase(vec2.begin()+1);                                  //To erase the next vector (the second, since it is a iterator), the size decreases and the data changes automatically
    //vec2.clear;

    for(int i=0;(unsigned)i<vec2.size();i++){
        cout<<vec2[i]<<endl;
    }

    return 0;
}