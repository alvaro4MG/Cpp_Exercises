
#include "List.h"


List::List(string name){
    if(name.empty())
        throw ERR_EMPTY;    
    this->name=name;

}

vector<Task> List::getTasks() const{

    return tasks;
}

unsigned List::getNumTasks() const{     //Need vector of tasks to get it for the others

    return tasks.size();
}

unsigned List::getNumDone() const{
    unsigned numDone=0;

    for(int i=0;(unsigned)i<tasks.size();i++){
        if(tasks[i].getIsDone()){
            numDone++;
        }
    }

    return numDone;
}

int List::getTimeTasks() const{
    int timeTasks=0;

    for(int i=0;(unsigned)i<tasks.size();i++){
        timeTasks+=tasks[i].getTime();
    }

    return timeTasks;
}

int List::getTimeDone() const{
    int timeDone=0;

    for(int i=0;(unsigned)i<tasks.size();i++){
        if(tasks[i].getIsDone()){
            timeDone+=tasks[i].getTime();
        }
    }

    return timeDone;
}

int List::getPosTask(string name) const{

    for(int i=0;(unsigned)i<tasks.size();i++){
        if(tasks[i].getName()==name){
            return i;
        }
    }

    return -1;
}

bool List::setName(string name){
    if(name.empty()){
        Util::error(ERR_EMPTY);
        return false;
    }
    else{
        this->name=name;
        return true;
    }

    return true;
}

void List::addTask(const Task &task){
    tasks.push_back(task);                  //Could be inline

}

bool List::deleteTask(string name){
    bool found=false;

    while(getPosTask(name)!=-1){
        found=true;
        tasks.erase(tasks.begin()+getPosTask(name));
    }

    if(!found)
        Util::error(ERR_TASK_NAME);
    

    return found;
}

bool List::toggleTask(string name){
    bool found=false;

    for(int i=0;(unsigned)i<tasks.size();i++){
        if(tasks[i].getName()==name){
            tasks[i].toggle();
            found=true;
        }
    }

    if(!found)
        Util::error(ERR_TASK_NAME);
    

    return found;
}

ostream& operator<<(ostream &os, const List &list){
    //vector<Task> tasks=list.getTasks();

    os << list.getName() << endl;

    for(int i=0;(unsigned)i<list.getNumTasks();i++){
        if(!list.tasks[i].getIsDone()){
            os << list.tasks[i];
        }
    }

    for(int i=0;(unsigned)i<list.getNumTasks();i++){
        if(list.tasks[i].getIsDone()){
            os << list.tasks[i];
        }
    }

    
    return os;
}