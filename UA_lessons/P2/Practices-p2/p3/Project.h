#ifndef _PROJECT_H_
#define _PROJECT_H_

#include <iostream>
#include <vector>
#include <sstream>

#include "List.h"
#include "Task.h"
#include "Util.h"

using namespace std;

class Project{
    friend ostream& operator<<(ostream &os, const Project &project);
    protected:
        int id;
        string name;
        string description;
        vector<List> lists;
        int getPosList(string name) const;      //Appears - instead of +
    public:
        Project(string name, string description="");
        int getId() const { return id; };
        string getName() const { return name; };
        string getDescription() const { return description; };
        bool setId(int id);
        bool setName(string name);
        void setDescription(string description) { this->description=description; };
        void edit(string name="", string description="");
        void addList(string name="");
        void deleteList(string name="");
        void addTaskToList(string name="");
        void deleteTaskFromList(string name="");
        void toggleTaskFromList(string name="");
        void menu();
        string summary() const;
};

#endif