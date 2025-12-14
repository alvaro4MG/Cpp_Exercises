//Tests for the practice

#include<iostream>
#include<fstream>
#include<vector>
#include<string.h>

using namespace std;

const int KMAXNAME = 20;
const int KMAXDESC = 40;

struct Date{
  int day;
  int month;
  int year;
};

struct Task{
  string name;
  Date deadline;
  bool isDone;
  int time;
};

struct BinTask{
    char name[KMAXNAME];
    Date deadline;
    bool isDone;
    int time;
};

struct List{
  string name;
  vector<Task> tasks;
};

struct BinList{
    char name[KMAXNAME];
    unsigned numTasks;
};

struct Project{
  int id;
  string name;
  string description;
  vector<List> lists;
};

struct BinProject{
    char name[KMAXNAME];
    char description[KMAXDESC];
    unsigned numLists;
};

struct ToDo{
    int nextId;
    string name;
    vector<Project> projects;
};

struct BinToDo{
    char name[KMAXNAME];
    unsigned numProjects;
};

bool tryBool(int num){
    if(num==0){
        return true;
    }
    else{
        return false;
    }
}

void checkFile(ifstream &file){
    string line;

    getline(file,line);
    cout<<line<<endl;;
}

int main(int argc, char *argv[]){
    int n1,n2;
    ifstream file("prueba1");

    cout<<"I have "<<argc<<" arguments"<<endl;      //In terminal, write -L,-O,super,etc and those are the arguments, separated by spaces (they usually start with the dash -)

    for(int i=0;i<argc;i++){
        cout<< argv[i]<<endl;                   //First argument will be the name of the program
    }    

    n2=0;

    if(tryBool(n2)){
        cout<<"sí es"<<endl;
    }

    /*if(strcmp(argv[1],argv[3])==0){
        cout<<"copy"<<endl;
    }*/

    if(file.is_open()){

        checkFile(file);

        file.close();
    }
    else{
        cout<<"Couldn't open"<<endl;
    }

    return 0;
}

/* first test for reading
    ifstream file;
    string s="input",name;
    int num1,num2;
    vector<int> list;


    if(file.is_open()){
        int i=1;
        while(getline(file,s)){     //Most common to read from a file, one line at a time
            cout << i <<": " << s << endl;
            i++;
        }
        //while(!file.eof())         //Read until find the end (eof: end of file), it is a bool

        file.close();
    }
    else{
        cout<<"Couldn't open it"<<endl;
    }
*/


/* Import project
    //getline(filename,line,'\n')
    //switch segun el primer char, con default para las tareas (letras)
    
    /*getline(file2,line,'*');
    cout<<line<<endl;
    cout<<line[0]<<endl;
    cout<<line[4]<<endl;
    

    do{
        getline(file2,line);
        cout<<line<<endl;
        if(line!=""){
            switch(line[0]){
                case '<':
                        cout<<"[New project]"<<endl;
                        j=-1;
                    break;
                case '#':
                        cout<<"[New project name]"<<endl;
                        
                        newProject.name=line.substr(1);
                        cout<<newProject.name<<endl;
                        todolist.projects.push_back(newProject);
                        i++;
                    break;
                case '*':
                        cout<<"[New project description]"<<endl;
                        todolist.projects[i].description=line.substr(1);
                        cout<<todolist.projects[i].description<<endl;
                    break;
                case '@':
                        cout<<"[New list]"<<endl;

                        newList.name=line.substr(1);
                        cout<<newList.name<<endl;
                        todolist.projects[i].lists.push_back(newList);
                        j++;
                        k=-1;
                    break;
                case '>':
                        cout<<"[Close project]"<<endl;
                    break;
                default:
                        cout<<"[New task]"<<endl;

                        /*do{
                            getline(line,strTask,'|');
                            if(strTask!=""){
                                switch()
                            }
                        }while(strTask!="");*/
                        
                        /*getline(line,strTask,'|');
                            newTask.name=strTask;
                            getline(line,strTask,'/');
                            newTask.deadline.day;
                            getline(line,strTask,'/');
                            newTask.deadline.month;
                            getline(line,strTask,'|');
                            newTask.deadline.year;
                            getline(line,strTask,'|');
                            if(strTask=="F"){
                                newTask.isDone==false;
                            }
                            else{
                                newTask.isDone==true;
                            }
                            getline(line,strTask);
                            newTask.time=stoi(strTask);
                            strTask=line.substr(0,line.find('|'));
                            newTask.name=strTask;
                            line.erase(0,line.find('|')+1);

                            strTask=line.substr(0,line.find('/'));
                            newTask.deadline.day=stoi(strTask);
                            line.erase(0,line.find('/')+1);
                            strTask=line.substr(0,line.find('/'));
                            newTask.deadline.month=stoi(strTask);
                            line.erase(0,line.find('/')+1);
                            strTask=line.substr(0,line.find('|'));
                            newTask.deadline.year=stoi(strTask);
                            line.erase(0,line.find('|')+1);

                            strTask=line.substr(0,line.find('|'));
                            if(strTask=="F")
                                newTask.isDone=false;
                            else
                                newTask.isDone=true;
                            
                            line.erase(0,line.find('|')+1);
                            newTask.time=stoi(strTask);
                            todolist.projects[i].lists[j].tasks.push_back(newTask);
                            k++;
                        break;
                }
            }else{
                todolist.nextId=i+1;
            }
        }while(line!="");
        /*
        getline(file2,line,'@');
        cout<<line<<endl;
        todolist.projects[0].name.push_back(line);
        getline(file2,line,'@');
        todolist.projects[0].description;
    */

/* save project
    ifstream file2;
    string line;
    ToDo todolist;
    BinToDo binTodo;
    BinProject binProj;
    BinList binList;
    BinTask binTask;
    int i,j,k;

    file2.open("pruebin",ios::binary);
    if(file2.is_open()){

        file2.read((char*)&binTodo,sizeof(BinToDo));

        cout<< binTodo.name<<endl;
        cout<<binTodo.numProjects<<endl;

        todolist.name=binTodo.name;
        cout<<todolist.name<<endl;

        for(i=0;i<binTodo.numProjects;i++){
            file2.read((char*)&binProj,sizeof(BinProject));
            cout<<binProj.name<<endl;
            cout<<binProj.description<<endl;
            cout<<binProj.numLists<<endl;

            for(j=0;j<binProj.numLists;j++){
                file2.read((char*)&binList,sizeof(BinList));
                cout<< binList.name<<endl;
                cout<< binList.numTasks<<endl;

                for(k=0;k<binList.numTasks;k++){
                    file2.read((char*)&binTask,sizeof(BinTask));
                    cout<<binTask.name<<endl;
                    cout<<binTask.time<<endl;
                }
            }
        }
        

        file2.close();
    }
    else{
        cout<<"Couldn't open the file"<<endl;
    }
*/