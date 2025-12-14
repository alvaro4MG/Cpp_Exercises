
#include "ToDo.h"

int ToDo::nextId=1;

ToDo::ToDo(string name){

    if(name.empty()){
        throw ERR_EMPTY;
    }
    else{  
        this->name=name;
    }

}

int ToDo::getPosProject(string name) const{

    for(int i=0;(unsigned)i<projects.size();i++){
        if(projects[i]->getName()==name){
            return i;
        }
    }

    return -1;

}

int ToDo::getPosProject(int id) const{

    for(int i=0;(unsigned)i<projects.size();i++){
        if(projects[i]->getId()==id){
            return i;
        }
    }

    return -1;

}

bool ToDo::setName(string name){

    if(name.empty()){
        Util::error(ERR_EMPTY);
        return false;
    }
    else{
        this->name=name;
        return true;
    }

}

void ToDo::addProject(Project *project){
    string s;

    //this->projects=project;

    for(int i=0;(unsigned)i<projects.size();i++){
        if(project->getName()==projects[i]->getName()){
            throw ERR_PROJECT_NAME;
        }
    }

    project->setId(nextId);
    nextId++;
    
    projects.push_back(project);

}

void ToDo::deleteProject(int id){
    string name;

    while(id<1){
        cout<< "Enter project id: ";
        cin >> id;
    }

    if(getPosProject(id)!=-1){
        for(int i=0;(unsigned)i<projects.size();i++){
            if(projects[i]->getId()==id){
                name=projects[i]->getName();
                projects.erase(projects.begin()+getPosProject(name));
            }
        }
    }
    else{
        Util::error(ERR_ID);
    }

}

void ToDo::setProjectDescription(string name, string description){
    bool found =false;

    for(int i=0;(unsigned)i<projects.size();i++){
        if(projects[i]->getName()==name){
            found=true;
            projects[i]->setDescription(description);
        }
    }

    if(!found)
        Util::error(ERR_PROJECT_NAME);

}

void ToDo::projectMenu(int id){
    bool found=false;

    if(id<1){
        cout<< "Enter project id: ";
        cin >> id;
    }

    if(getPosProject(id)!=-1){
        found=true;
        projects[getPosProject(id)]->menu();
    }

    if(!found)
        Util::error(ERR_ID);

}

ostream& operator<<(ostream &os, const ToDo &ToDo){

    for(int i=0;(unsigned)i<ToDo.projects.size();i++){
        if(i>0)
            os<<endl;
        string content=ToDo.projects[i]->summary();
        os << content;
    }

    return os;
}