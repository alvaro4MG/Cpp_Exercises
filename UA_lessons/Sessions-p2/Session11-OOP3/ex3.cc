//Objects and memory management (not for the practice)

//Object relationships
    //Different arrows have different meanings:

    //Aggregation and composition
        //Composition if the container is destroyed, its objects too (wing->plane)
        //Aggregation, container can be erased, not its objects (players->team)
            //Aggregation uses pointers, so the container erased doesnt erase the objects too

#include<iostream>
#include "Date13.h"

using namespace std;

int main(){
    Date d(10,20,2040);
    Date f(13,4,1995);

    cout<< d.getDay() << endl;

    //cout << d << endl;    //This doesn't work, must overload
    cout << d;      //Once we declared and described ostream in .cc, we are now telling the program what to do

    return 0;
}

/*
    List.h
    class List{
        private:
            string name;
            vector<Task> tasks; //If I destroy the list, also the tasks in it, same with projects and its lists
        public: ...
    };

    class ToDo{
        private:
            string name;
            static int nextId;
            vector<Project*> projects;   //Using pointers, create project then add them, addProject receives a pointer
        public:
            A(B *b) ( this->b=b );       //Constructor from example
    }
*/