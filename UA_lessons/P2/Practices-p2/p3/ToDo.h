
#ifndef _TODO_H_
#define _TODO_H_

#include<iostream>

#include "Project.h"
#include "List.h"
#include "Task.h"
#include "Util.h"

class ToDo{
    friend ostream& operator<<(ostream &os, const ToDo &ToDo);
    protected:
        static int nextId;
        string name;
        vector<Project *> projects;
        int getPosProject(string name) const;   //- not +
        int getPosProject(int id) const;        //- not +
    public:
        ToDo(string name);
        string getName() const { return name; };
        bool setName(string name);
        void addProject(Project *project);
        void deleteProject(int id=0);
        void setProjectDescription(string name, string description);
        void projectMenu(int id=0);
};

#endif