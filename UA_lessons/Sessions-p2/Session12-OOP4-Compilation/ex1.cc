//Compilation
    //Translation to a executable program in two steps: compilation (translate into object code) and links (combines object code and libraries, generating the executable, not the other)
    //If you only wnat the compilation, you can use -c instead of -o and not write the title (because it won't generate the executable since it doesn't do the link), the title will be "name".o (object)
    //For several files: compile each object separately, then link them together ( use -o "name of executable"), but you can compile all of them together
    //Only for a few, if you have 100 it is too much. 
    //Other problem is changing a .h that is in a lot of files, best is using tool "make"
//Make tool
    //allows setting dependencies between files, needs a text file makefile to specify them and what to do when something changes
    //create with make -f name
    //Format:
        // <objective> : <dependencies>
        // [tab] <instruction>
    //It obtains the main objective (the executable, specified in the first instruction) and other secondary objectives
    //You can use constants declared at the beginning
        // CC = g++
        //CFLAGS = -Wall -g
        //OBJS = C1.o C2.o prog.o

        //prog: $OBJS)
        //  $(CC) $(CFLAGS) -o prog
        //...
        //clean:                //deletes from hard drive that, must be used after ( make clean in console)
        //  rm -rf $(OBJS)

#include<iostream>

//#include "name.h"     //My own libraries, this is why we use this
//#include<name.h>      


using namespace std;

int main(){


    return 0;
}

/*
    prog: C1.o C2.o prog.o          //Main objective, obtained with all the secondary objective
        g++ -Wall -g C1.o C2.o prog.o -o prog       //-Wall and -g for debugger
    C1.o: C1.cc C1.h
        g++ -Wall -g -c C1.cc
    C2.o: C2.cc C2.h C1.h           //They use C1, so it is there ( #include "Task.h" )
        g++ -Wall -g -c C2.cc
    prog.o: prog.cc C1.h C2.h       //Why not .cc? only care for methods, optimacing (or something like that) won't change the header, only if it changes the parameters it receives 
        g++ -Wall -g -c prog.cc     




    List.o: List.cc List.h Task.h Util.h        //Must include "Util.h" in the header
        g++ List.cc -
*/