
#include "Project.h"

Project::Project(string name, string description){          //Dont put the "" by default

    if(name.empty()){
        throw ERR_EMPTY;
    }
    else{    
        this->name=name;
        this->description=description;
        id=0;
    }

}

int Project::getPosList(string name) const{

    for(int i=0;(unsigned)i<lists.size();i++){
        if(lists[i].getName()==name){
            return i;
        }
    }

    return -1;
}

bool Project::setId(int id){

    if(id>=0){
        this->id=id;
        return true;
    }
    else{
        Util::error(ERR_ID);
        return false;
    }

}

bool Project::setName(string name){

    if(name.empty()){
        Util::error(ERR_EMPTY);
        return false;
    }
    else{
        this->name=name;
        return true;
    }

}

void Project::edit(string name, string description){

    while(name.empty()){
        cout<<"Enter project name: ";
        getline(cin,name);
        this->name=name;

        if(name.empty()==true)
            Util::error(ERR_EMPTY);

    }

    if(description.empty()){
        cout<<"Enter project description: ";
        getline(cin,description);
        this->description=description;
    }

}

void Project::addList(string name){
    bool keepLoop=true,found=false;

    do{
        try{
            if(name.empty()){                   //Maybe needs a loop, not sure, like in the next
                cout<<"Enter list name: ";
                getline(cin,name);
            }
            List newList(name);

            if(newList.setName(name)){
                for(int i=0;(unsigned)i<lists.size() && !found;i++){
                    if(lists[i].getName()==name){
                        found=true;
                    }
                }
                if(!found)
                    lists.push_back(newList);
                else
                    Util::error(ERR_LIST_NAME);
                
                keepLoop=false;
            }
        }
        catch(Error e){
            Util::error(e);
        }
    }while(keepLoop);
    
}

void Project::deleteList(string name){
    bool found=false;

    while(name.empty()){
        cout<<"Enter list name: ";
        getline(cin,name);

        if(name.empty())
            Util::error(ERR_EMPTY);
    }

    while(getPosList(name)!=-1){
        found=true;
        lists.erase(lists.begin()+getPosList(name));        //Maybe just save it in a variable
    }

    if(!found)
        Util::error(ERR_LIST_NAME);
    
}

void Project::addTaskToList(string name){
    string s;
    int newTime;
    unsigned i;

    while(name.empty()){
        cout<<"Enter list name: ";
        getline(cin,name);

        if(name.empty())
            Util::error(ERR_EMPTY);
    }

    if(getPosList(name)!=-1){
        Task newTask(name);
        cout<<"Enter task name: ";
        getline(cin,s);
        newTask.setName(s);

        cout<<"Enter deadline: ";
        getline(cin,s);
        if(newTask.setDeadline(s)){
            cout<<"Enter expected time: ";
            cin >> newTime;

            if(newTask.setTime(newTime)){
                i=getPosList(name);
                lists[i].addTask(newTask);
            }
        }
    }
    else{
        Util::error(ERR_LIST_NAME);
    }

}

void Project::deleteTaskFromList(string name){
    string s;
    unsigned i;

    while(name.empty()){
        cout<<"Enter list name: ";
        getline(cin,name);

        if(name.empty())
            Util::error(ERR_EMPTY);
    }

    if(getPosList(name)!=-1){
        cout<<"Enter task name: ";
        getline(cin,s);

        i=getPosList(name);
        if(lists[i].getPosTask(s)!=-1){
            lists[i].deleteTask(s);

        }
        else{
            Util::error(ERR_TASK_NAME);
        }
    }
    else{
        Util::error(ERR_LIST_NAME);
    }

}

void Project::toggleTaskFromList(string name){
    string s;
    unsigned i;

    while(name.empty()){
        cout<<"Enter list name: ";
        getline(cin,name);

        if(name.empty())
            Util::error(ERR_EMPTY);
    }

    if(getPosList(name)!=-1){
        cout<<"Enter task name: ";
        getline(cin,s);

        i=getPosList(name);
        if(lists[i].getPosTask(s)!=-1){
            lists[i].toggleTask(s);
        }
        else{
            Util::error(ERR_TASK_NAME);
        }
    }
    else{
        Util::error(ERR_LIST_NAME);
    }

}

void Project::menu(){
    char option;
    string s;
  
  do{
    cout << "1- Edit project" << endl
        << "2- Add list" << endl
        << "3- Delete list" << endl 
        << "4- Add task" << endl
        << "5- Delete task" << endl
        << "6- Toggle task" << endl
        << "7- Report" << endl
        << "b- Back to main menu" << endl
        << "Option: ";

    cin >> option;
    cin.get();
    
    switch(option){
      case '1': edit();
                break;
      case '2': addList();
                break;
      case '3': deleteList();
                break;
      case '4': addTaskToList();
                break;
      case '5': deleteTaskFromList();
                break;
      case '6': toggleTaskFromList();
                break;
      case '7': cout << *this << endl;
                break;
      case 'b': break;
      default: Util::error(ERR_OPTION);
    }
  }while(option!='b');

}

string Project::summary() const{
    string summ,s;
    stringstream ssId,ssDone,ssTasks;
    int num=getId(),numDone=0,numTasks=0;
    ssId<<num;
    ssId>>s;

    summ="("+s+") "+getName();

    for(int i=0;(unsigned)i<lists.size();i++){
        numDone+=lists[i].getNumDone();
    }

    ssDone<<numDone;
    ssDone>>s;
    summ+=" ["+s+"/";

    for(int i=0;(unsigned)i<lists.size();i++){
        numTasks+=lists[i].getNumTasks();
    }

    ssTasks<<numTasks;
    ssTasks>>s;
    summ+=s+"]";


    return summ;
}

ostream& operator<<(ostream &os, const Project &project){
    int totalTasks=0,totalDone=0,timeTasks=0,timeDone=0;
    bool taskSaved=false;
    Task highTask(""), compTask("");
    Date highDate, compDate;
    
    os << "Name: " << project.getName() << endl; 
    if(!project.description.empty())
        cout << "Description: " << project.getDescription() << endl;
    for(int i=0;(unsigned)i<project.lists.size();i++){
        cout << project.lists[i];
        totalTasks+=project.lists[i].getNumTasks();
        totalDone+=project.lists[i].getNumDone();
        timeTasks+=project.lists[i].getTimeTasks();
        timeDone+=project.lists[i].getTimeDone();

        vector<Task> tasks = project.lists[i].getTasks();
        for(int j=0;(unsigned)j<tasks.size();j++){
            if(!taskSaved && !tasks[j].getIsDone()){
                highTask=tasks[j];
                taskSaved=true;
                highDate=highTask.getDeadline();
            }
            if(taskSaved){
                compTask=tasks[j];
                compDate=compTask.getDeadline();

                if(highDate.year>compDate.year && !compTask.getIsDone()){
                    highTask=compTask;
                    highDate=compTask.getDeadline();
                }
                else if(highDate.year==compDate.year){
                    if(highDate.month>compDate.month){
                        highTask=compTask;
                        highDate=compTask.getDeadline();
                    }
                    else if(highDate.month==compDate.month){
                        if(highDate.day>compDate.day){
                            highTask=compTask;
                            highDate=compTask.getDeadline();
                        }
                    }
                }
            }
        }
    }

    cout << "Total left: " << totalTasks-totalDone << " (" << timeTasks-timeDone << " minutes)" << endl
         << "Total done: " << totalDone << " (" << timeDone << " minutes)" << endl;
    if(taskSaved)
        cout << "Highest priority: " << highTask.getName() << " (" << highDate.year << "-" << highDate.month << "-" << highDate.day << ")" << endl;
    

    return os;
}