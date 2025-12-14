// DNI 48150407E Martínez García, Álvaro 0130 [mirar error en 622, si borrado entonces i esta mal]

#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <string.h>

using namespace std;

const int MAX_YEAR = 2100;    //Since this is a tasks list program, the maximum and minimum year available can be changed easily from here
const int MIN_YEAR = 2000;
const string ENTER_TASK = "Enter task name: ";   //This strings appear more than once, so they can be set as a constant
const string ENTER_FILE = "Enter filename: ";
const string ENTER_ID = "Enter project id: ";
const int KMAXNAME = 20;      //Constants for the limit of the names and descriptions of the binary files
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

enum Error{
  ERR_OPTION,
  ERR_EMPTY,
  ERR_LIST_NAME,
  ERR_TASK_NAME,
  ERR_DATE,
  ERR_TIME,
  ERR_ID,
  ERR_PROJECT_NAME,
  ERR_FILE,
  ERR_ARGS
};

enum option{            //Enumeration for the type of action that we want to do with the name of the list entered, so it will be easier to see on the code in general and the switch
  NUM_ADD,
  NUM_DEL,
  NUM_CMP
};

enum optionDate{
  DATE_NEW,
  DATE_CHECK
};

void error(Error e){
  switch(e){
    case ERR_OPTION:
      cout << "ERROR: wrong menu option" << endl;
      break;
    case ERR_EMPTY:
      cout << "ERROR: empty string" << endl;
      break;
    case ERR_LIST_NAME:
      cout << "ERROR: wrong list name" << endl;
      break;
    case ERR_TASK_NAME:
      cout << "ERROR: wrong task name" << endl;
      break;
    case ERR_DATE:
      cout << "ERROR: wrong date" << endl;
      break;
    case ERR_TIME:
      cout << "ERROR: wrong expected time" << endl;
      break;
    case ERR_ID:
      cout << "ERROR: wrong project id" << endl;
      break;
    case ERR_PROJECT_NAME:
      cout << "ERROR: wrong project name" << endl;
      break;
    case ERR_FILE:
      cout << "ERROR: cannot open file" << endl;
      break;
    case ERR_ARGS:
      cout << "ERROR: wrong arguments" << endl;
  }
}

void showProjectMenu(){
  cout << "1- Edit project" << endl
       << "2- Add list" << endl
       << "3- Delete list" << endl 
       << "4- Add task" << endl
       << "5- Delete task" << endl
       << "6- Toggle task" << endl
       << "7- Report" << endl
       << "b- Back to main menu" << endl
       << "Option: ";
}

void editProject(Project &toDoList){    //Module to edit the project

  do{                                     //Since the project name can't be an empty string, we use a do-while until the name of the project isn't empty anymore
    cout<<"Enter project name: ";
    getline(cin,toDoList.name);

    if(toDoList.name.empty()==true)         //If it's empty, it will show the error and repeat the loop
      error(ERR_EMPTY);

  }while(toDoList.name.empty()==true);

  cout<<"Enter project description: ";    //The description can be empty, so it will just ask normally and it won't repeat itself if it is empty
  getline(cin,toDoList.description);
}

void getListName(string &newString){   //Module created to ask for the name of the list, since it is asked in more than one function
                                              //It will use a string "newString" that will change in the module where it was called since it is passed as a reference
  do{                                     //The name can't be empty so if "newString" is empty, it will ask again for it, having a similar structure as the do-while used in editProject
    cout<<"Enter list name: ";
    getline(cin,newString);

    if(newString.empty()==true)
      error(ERR_EMPTY);
                       
  }while(newString.empty()==true);
}

int checkList(Project &toDoList, string checkString, option operation){    //Function created to check if the name of the list entered (stored in "checkString") exists in toDoLost
  int i;                                                                      //The function will return i, the position that occupies the list that we are looking for, or -1, to indicate that there's no list with that name
  bool found=false;

  if(toDoList.lists.size()==0 && (operation == NUM_DEL || operation == NUM_CMP)){     //To avoid errors when checking for a string (idicated by NUM_DEL or NUM_CMP), we use this if condition to send an error when there's no lists yet
    error(ERR_LIST_NAME);
    return -1;
  }
  for(i=0;(unsigned)i<toDoList.lists.size() && !found;i++){       //We want to check all the lists, so we will use size to obtain an unsigned number (so we use i as an unsigned too)
    if(checkString==toDoList.lists[i].name){                       //If there's a list name which is the same as "checkString", found will be set to true and we will make the corresponding actions
      found=true;

      if(operation==NUM_ADD){
        error(ERR_LIST_NAME);
        return -1;
      }
      else{
        return i;
      }
    }
  }

  if(!found && (operation!=NUM_ADD)){
    error(ERR_LIST_NAME);
    return -1;
  }
  return i;
}

void addList(Project &toDoList){      //Module to add a list to the project
  string newString;
  List newList;
  int i,j;

  getListName(newString);                      //We will use GetListName and checkList here like in the rest of the modules, to get the list name in "newString" and to know if we can continue with the rest of the instructions in the module
  i = checkList(toDoList,newString,NUM_ADD);

  if(i!=-1){                                       //If i isn't -1 (which means there has been an error, a list already with that name in that case), the list will be added. The use of i in this way will let us use it lñike a bool variable, so that false or error means -1 and true is the rest
    for(j=0;(unsigned)j<newString.length();j++){       //To copy the name entered before, we will use a for loop as much times as the length of "newString", pushing back each letter in the name of "newList"
      newList.name.push_back(newString[j]);
    }
    toDoList.lists.push_back(newList);             //Once we have the name of the list, we can push it back in the lists of the project
  }

}

void deleteList(Project &toDoList){     //Module to delete a list (and all its components too)
  string checkString;
  int i;

  getListName(checkString);
  i = checkList(toDoList,checkString,NUM_DEL);

  if(i!=-1){                                          //If there's no error with the list name entered (which means there is a list with that name), we will erase the list with the position i returned
    toDoList.lists.erase(toDoList.lists.begin()+i);
  }

}

void checkDate (Task &newTask,bool &err_date, optionDate operation){   //Module created to ask for the deadline date, so it is easier to work with it
  string s;

  if(operation==DATE_NEW){
    cout<<"Enter deadline: ";           //Since we suppose that the user will always enter the deadline in the right way (dd/mm/yyyy), we can just read until there is a /
    getline(cin,s,'/');                   //Once we read the first in the string s, which is only used to pass the information, we need to make it an integer number
    newTask.deadline.day=stoi(s);          //To do that we will use stoi with the s string each time and save the number in the deadline of the new task
    getline(cin,s,'/');
    newTask.deadline.month=stoi(s);
    getline(cin,s);
    newTask.deadline.year=stoi(s); 
  }    

  if(newTask.deadline.year<MIN_YEAR || newTask.deadline.year>MAX_YEAR || newTask.deadline.month>12 || newTask.deadline.day>31)   //Then, it will check if the date exists, using the corresponding conditions to avoid an invalid date (which will set err_date to true)
    err_date=true;
  else if(((newTask.deadline.month%2==0 && newTask.deadline.month<=7) || (newTask.deadline.month%2==1 && 
            newTask.deadline.month>=8)) && newTask.deadline.day==31)
    err_date=true;
  else if(newTask.deadline.month==2 && newTask.deadline.day>28){
    if(((newTask.deadline.year%4==0 && newTask.deadline.year%100!=0)||(newTask.deadline.year%100==0 && 
         newTask.deadline.year%400==0)) && newTask.deadline.day==29)
      err_date=false;
    else
      err_date=true;
  }
  else
    err_date=false;

  if(err_date==true)    //If there was an error, the error will be shown and the err_date variable won't allow the rest of the information to be asked, since the task won't be saved
    error(ERR_DATE);
  
}

void addTask(Project &toDoList){    //Module to create a task
  string strList,strTask;
  Task newTask;
  bool err_date;
  int i;

  getListName(strList);
  i=checkList(toDoList,strList,NUM_CMP);

  if(i!=-1){
    cout<<ENTER_TASK;
    getline(cin,strTask);

    if(strTask.empty()==false)                        //If the name of the task isn't empty (it is allowed to be or not), it will be copied in "newTask"
      for(int j=0;(unsigned)j<strTask.length();j++)
        newTask.name.push_back(strTask[j]);
    
    newTask.isDone=false;                                //Also the new task isDone must be set to false (it is a new task, so it isn't completed yet)

    checkDate(newTask,err_date,DATE_NEW);                       //It will ask for the deadline date and will get the value of the bool variable "err_date" in order to see if the user can enter the following information
    
    if(err_date==false){
      cout<<"Enter expected time: ";
      cin>>newTask.time;

      if(newTask.time<1 || newTask.time>180)                     //When asked for the time to complete, it has to be between 1 and 180, and if it isn't it must show the error and it won't push back the new task, which can only be done whene the date entered is correct
        error(ERR_TIME);
      else
        toDoList.lists[i].tasks.push_back(newTask);
    }
  }
}

void deleteTask(Project &toDoList){   //Module to delete a task
  string strList,strTask;
  bool found=false;
  int i,j;

  getListName(strList);
  i=checkList(toDoList,strList,NUM_CMP);

  if(i!=-1){
    cout<<ENTER_TASK;
    getline(cin,strTask);

    for(j=0;(unsigned)j<toDoList.lists[i].tasks.size();j++){              //When looking for tasks with the name entered, it doesn't have stop after deleting since it has to delete all tasks with the same name, so when we change found after the first coincidence, it will be used for the error (if there isn't a single task with that name, found will keep false) 
      if(strTask==toDoList.lists[i].tasks[j].name){
        found=true;
        toDoList.lists[i].tasks.erase(toDoList.lists[i].tasks.begin()+j);   //When the task is found, it will be erased, but it also has to decrease j by one, since the rest of the elements will have a position less and it can skip a task with that name
        j--;
      }
    }

    if(!found)          //As we have seen in class, the first condition in an AND (&&) should be the one that is always or most of the time false, so it doesn't need to check the second element
      error(ERR_TASK_NAME);
  }
}

void toggleTask(Project &toDoList){     //Module to toogle tasks
  string strList,strTask;
  int i,j;
  bool found=false;

  getListName(strList);
  i=checkList(toDoList,strList,NUM_CMP);

  if(i!=-1){
    cout<<ENTER_TASK;
    getline(cin,strTask);
    
    for(j=0;(unsigned)j<toDoList.lists[i].tasks.size();j++){    //It will look through all the list all the tasks with the same name and change them from false to true and viceversa
      if(strTask==toDoList.lists[i].tasks[j].name){
        if(toDoList.lists[i].tasks[j].isDone==false)
          toDoList.lists[i].tasks[j].isDone=true;
        else
          toDoList.lists[i].tasks[j].isDone=false;
        found=true;
      }
    }

    if(!found){
      error(ERR_TASK_NAME);
    }
  }
}

void report(const Project &toDoList){      //Module to show the report (bigger than it should but I don't think using one or more modules to substitute a just little group of lines would make this module more clear)
  int done=0, totalDone=0, tasks=0, totalTasks=0;        //Since the report must show the amount of total tasks, tasks done and their respective amount of minutes, we will declare them and initialize as 0, whose value we will increase
  Task highPriority;                                               //It must show the task with the highest priority, name and deadline, so we will save it in highPriority

  cout << "Name: "<<toDoList.name<<endl;
  if(toDoList.description.empty()==false)                      //If the description is empty, "Description" shouldn't appear
    cout << "Description: "<< toDoList.description << endl;




    //cout<< "Id: "<<toDoList.id<<endl;   //Delete later



  
  for(unsigned int i=0;i<toDoList.lists.size();i++){           //It has to show all the tasks of all the lists, but it must show the ones that aren't completed yet, so in each list iteration it will first show the uncompleted task and then, in another for loop, it will show the completed ones
    cout << toDoList.lists[i].name << endl;

    for(unsigned int j=0;j<toDoList.lists[i].tasks.size();j++){   //In the first for loop, we will start using the task and totalTasks 
      tasks++;
      totalTasks+=toDoList.lists[i].tasks[j].time;
      
      if(toDoList.lists[i].tasks[j].isDone==false){
        cout <<"[ ] " << "(" << toDoList.lists[i].tasks[j].time << ") " << toDoList.lists[i].tasks[j].deadline.year << "-" << toDoList.lists[i].tasks[j].deadline.month << "-" 
             << toDoList.lists[i].tasks[j].deadline.day << " : " << toDoList.lists[i].tasks[j].name << endl;
        
        if(highPriority.name.empty()==true)                                                      //If highPriority hasn't been set yet, it will take the value of the first uncompleted task, so it can be compared to the rest of the tasks
          highPriority=toDoList.lists[i].tasks[j];
        else{
          if(toDoList.lists[i].tasks[j].deadline.year < highPriority.deadline.year)                  //For the next uncompleted task, it will check if the year, month and day are lower and set highPriority as this task
            highPriority=toDoList.lists[i].tasks[j];
          else if(toDoList.lists[i].tasks[j].deadline.year == highPriority.deadline.year){
            if(toDoList.lists[i].tasks[j].deadline.month < highPriority.deadline.month)
              highPriority=toDoList.lists[i].tasks[j];
            else if(toDoList.lists[i].tasks[j].deadline.month == highPriority.deadline.month)
              if (toDoList.lists[i].tasks[j].deadline.day < highPriority.deadline.day)
                highPriority=toDoList.lists[i].tasks[j];
          }
        }
      }
    }

    for(unsigned int j=0;j<toDoList.lists[i].tasks.size();j++){

      if(toDoList.lists[i].tasks[j].isDone==true){
        cout <<"[X] " << "(" << toDoList.lists[i].tasks[j].time << ") " << toDoList.lists[i].tasks[j].deadline.year << "-" << toDoList.lists[i].tasks[j].deadline.month << "-" 
             << toDoList.lists[i].tasks[j].deadline.day << " : " << toDoList.lists[i].tasks[j].name << endl;
        
        done++;                                                //For the completed tasks, we start counting them for the done tasks variables
        totalDone+=toDoList.lists[i].tasks[j].time;
      }
    }
    cout<<endl;
  }

  cout << "Total left: " << tasks-done << " (" << totalTasks-totalDone << " minutes)" << endl;
  cout << "Total done: " << done << " (" << totalDone << " minutes)" << endl;

  if(tasks-done!=0)                                                 //If there's no task or all of them are completed, the highest priority line doesn't have to appear
    cout << "Highest priority: " << highPriority.name << " (" << highPriority.deadline.year << "-" << highPriority.deadline.month << "-" << highPriority.deadline.day << ")" << endl;
}

void ProjectMenu(Project &toDoList){      //Module for the last menu with the corresponding changes for this practice      
  char option;
  
  do{
    showProjectMenu();
    cin >> option;
    cin.get();
    
    switch(option){
      case '1': editProject(toDoList);
                break;
      case '2': addList(toDoList);
                break;
      case '3': deleteList(toDoList);
                break;
      case '4': addTask(toDoList);
                break;
      case '5': deleteTask(toDoList);
                break;
      case '6': toggleTask(toDoList);
                break;
      case '7': report(toDoList);
                break;
      case 'b': break;
      default: error(ERR_OPTION);
    }
  }while(option!='b');
    
}

void showMainMenu(){                      //Module for the new main menu
    cout << "1- Project menu" << endl
       << "2- Add project" << endl
       << "3- Delete project" << endl 
       << "4- Import projects" << endl
       << "5- Export projects" << endl
       << "6- Load data" << endl
       << "7- Save data" << endl
       << "8- Summary" << endl
       << "q- Quit" << endl
       << "Option: ";
}

void checkProjectMenu(ToDo &Projects){        //Module created to check if there is a project with the id the user asks
    int projectId;
    bool found=false;

    cout << ENTER_ID;
    cin >> projectId;
    cin.get();

    for(unsigned int i=0; i < Projects.projects.size() && !found; i++){
      if(Projects.projects[i].id==projectId){
          ProjectMenu(Projects.projects[i]);                            //When the project with the same id is found, this project will be passed as an argument to use it in the option 1
          found=true;
      }
    }

    if(!found)                                                            //If it isn't found, an error will appear about the id
      error(ERR_ID);

}

bool checkProjectName(ToDo Projects,string enteredName){    //Module created to return a bool value if the name of the project exists in the list of projects
  bool found=false;

  for(unsigned int i=0;i<Projects.projects.size() && !found;i++)
    if(Projects.projects[i].name==enteredName)
      found=true;

  if(found)                                                   //In case it is found (we know it with the bool variable found), it will return true, otherwise it will return false
    return true;
  else
    return false;
  
}

void addProject(ToDo &Projects){          //Module for the option 2, adding projects 
  Project newProject;
  string enteredText;

  do{
    cout << "Enter project name: ";
    getline(cin,enteredText);

    if(enteredText.empty())
      error(ERR_EMPTY);
  }while(enteredText.empty());

  if(checkProjectName(Projects,enteredText)){        //After entering the name of the project, we will the previous module to see if there is a project with the same name (we can use it as a condition since it returns a bool value)
    error(ERR_PROJECT_NAME);
  }
  else{                                                 //If there isn't a project with that name, the name will be pushed back into the newProject, along with the description and the id (depending on the value of nextId)
    for(unsigned int i=0;i<enteredText.length();i++)
      newProject.name.push_back(enteredText[i]);
    
    newProject.id=Projects.nextId;
    Projects.nextId++;                                          //Once the id of the project is assigned, it will always increase once, and it will never be decreased, even after deleting a project

    cout<<"Enter project description: ";
    getline(cin,newProject.description);

    Projects.projects.push_back(newProject);            //Finally, newProject is pushed back into the list of projects
  }
}

void deleteProject(ToDo &Projects){       //Module for the option 3, deleting projects
  int checkId;
  bool found=false;

  cout << ENTER_ID;
  cin >> checkId;

  for (unsigned int i=0;i < Projects.projects.size() && !found;i++){    //After the user enters the id of the project he/she wants to delete, the program will look through all the project's id to see if any of them has the same id
    if(Projects.projects[i].id==checkId){
      Projects.projects.erase(Projects.projects.begin()+i);               //If the project exists (which doesn't always even if the id has been used), it will be deleted
      found=true;
    }
  }

  if(!found)                                                              //If no project exists with the same id, an error will appear
    error(ERR_ID);
}

void importingTask(ToDo &Projects,ifstream &file,string &line,int i,int j){   //Moduel created to import a task
  string strTask;
  Task newTask;
  bool err_date;

  strTask=line.substr(0,line.find('|'));    //First, it will read and save the name of the task until the first '|'
  newTask.name=strTask;
  line.erase(0,line.find('|')+1);
  strTask=line.substr(0,line.find('/'));    //Then, it will read and save the date
  newTask.deadline.day=stoi(strTask);
  line.erase(0,line.find('/')+1);
  strTask=line.substr(0,line.find('/'));
  newTask.deadline.month=stoi(strTask);
  line.erase(0,line.find('/')+1);
  strTask=line.substr(0,line.find('|'));
  newTask.deadline.year=stoi(strTask);
  line.erase(0,line.find('|')+1);

  checkDate(newTask,err_date,DATE_CHECK);     //The date will be checked, if it is correct, it will keep reading the information for the new task

  if(err_date==false){
    strTask=line.substr(0,line.find('|'));
    if(strTask=="F")
        newTask.isDone=false;
    else
        newTask.isDone=true;
  
    line.erase(0,line.find('|')+1);         //After checking the isDone, it will check if the time is correct and if it can push back the newTask
    newTask.time=stoi(line);

    if(newTask.time<1 || newTask.time>180)
      error(ERR_TIME);
    else{
      Projects.projects[i].lists[j].tasks.push_back(newTask);
    }
  }
}

void switchLine(ToDo &Projects,ifstream &file,string line,int &i,int &j,bool &found){     //Module created for the switch depending on the first character of the line
  Project newProject;
  List newList;

  switch(line[0]){
    case '<':
      break;
    case '#':
        newProject.name=line.substr(1);                     //The name of the new proejct will be the characters behind '#', but then the program will check if that name exists
        found=checkProjectName(Projects,newProject.name);     //If the name exists, an error will appear and it it will set found to true, which will avoid the rest of the information of the project to be registered
        if(found){
          error(ERR_PROJECT_NAME);
        }
        else{
          Projects.projects.push_back(newProject);            //If the name doesn't exists, it will be pushed back with the id, i will increased(which will make -1 into 0) and will set j to -1, the same way as i
          i++;
          Projects.projects[i].id=i+1;
          j=-1;
        }
      break;
    case '*':
        if(!found)                                            //As explained before, if the project can be pushed back, the same will happen with its description, lists and tasks
          Projects.projects[i].description=line.substr(1);
      break;
    case '@':
        if(!found){
          newList.name=line.substr(1);
          Projects.projects[i].lists.push_back(newList);
          j++;
        }
      break;
    case '>': 
      break;
    default:
        if(!found)
          importingTask(Projects,file,line,i,j);              //For the task, it will be imported in the previous module
      break;
  }
}

void importingProj(ToDo &Projects,ifstream &file){      //Module created to start importing the project
  string line;
  int i,j;
  bool found=false;

  if(Projects.projects.empty())                       //If there are no projects in the current execution of the program, i will be set to -1 for the correct execution of the module
    i=-1;
  else
    i=Projects.nextId-2;                                //If there are other projects, the first of the imported projects will start depending on the next id
  
  do{
    getline(file,line);
    if(line!=""){
      switchLine(Projects,file,line,i,j,found);       //The program will start reading line by line and will pass it to this module for a switch depending on the first character
    }else{
      Projects.nextId=i+2;                            //When there are no more lines, nextId will be assigned the value of i+2
    }
  }while(line!="");
}

void importProjects(ToDo &Projects, string filename, bool &doneArg,bool &finishedArg){      //Module for the option 4, importing projects
  ifstream file;

  if(doneArg){                        //If there are no arguments or the changes for the arguments have been applied, this module will ask for the name of the file and open it
    cout<<ENTER_FILE;
    getline(cin,filename);
  }
  else
    doneArg=true;                     //If this is the first execution when using an "-i" argument, this bool variable will store that the changes have been applied after the execution

  file.open(filename);
  if(file.is_open()){
    importingProj(Projects,file);     //Once the file is opened, we will start importing the projects of the file with this module

    file.close();
  }
  else{
    error(ERR_FILE);                  //If the file can't be opened, it will show an error, and it the changes of an argument couldn't be done, the bool variable will be set to false, which later will cause the program to close after not being able to open the argument, without showing the menu
    if(!finishedArg)
      doneArg=false;
  }

}

void writeFile(ofstream &file,Project &newProject){     //Module created to start writing the information in the file
  unsigned int j,k;

  file << "<" << endl;  
  file << "#" << newProject.name << endl;                                 //It will write in each line the corresponding first character and its information into the file
  if(!newProject.description.empty()){
    file << "*" << newProject.description << endl;
  }
  if(!newProject.lists.empty()){
    for(j=0;j<newProject.lists.size();j++){
      file << "@" << newProject.lists[j].name << endl;

      if(!newProject.lists[j].tasks.empty()){
        for(k=0;k<newProject.lists[j].tasks.size();k++){
          file << newProject.lists[j].tasks[k].name
                << "|" << newProject.lists[j].tasks[k].deadline.day
                << "/" << newProject.lists[j].tasks[k].deadline.month
                << "/" << newProject.lists[j].tasks[k].deadline.year
                << "|";
          if(newProject.lists[j].tasks[k].isDone)
            file << "T";
          else
            file << "F";
          file << "|" << newProject.lists[j].tasks[k].time << endl;
        }
          
      }
    }
  }

  file << ">" << endl;
}

void exportingProj(ToDo &Projects,ofstream &file,int projId){     //Module created to start exporting the projects (or the project desired)
  unsigned int i;
  bool allProjects,found=false;

  if(projId==0){                                                  //If projId is 0, it means the user wants to export all, but if it isn't, the program will check which proejct as the same id and the value i will be given depending on it
    allProjects=true;                                               //We set this variable to true so it will keep the do-while loop going until the end
    i=0;
  }
  else{
    allProjects=false;
    for(i=0;i<Projects.projects.size() && !found;i++)
      if(Projects.projects[i].id==projId)
        found=true;
    i--;
  }
  
  do{
    writeFile(file,Projects.projects[i]);                           //At least once this module will be executed to save the project indicated, which can be all of them or just one
    i++;
  }while(allProjects && i<Projects.projects.size());
}

void exportProjects(ToDo &Projects){                                    //Module for the option 5, exporting projects
  ofstream file;
  char option;
  string filename;
  int projId;
  bool found=false,errId=false;

  do{
    cout << "Save all projects [Y/N]?: ";                               //First, it has to ask if the user wants to export all the projects or just one
    cin >> option;
    cin.get();
  }while(option!='y' && option!='Y' && option!='n' && option!='N');

  if(option=='n' || option=='N'){                                           //If the user only wants to export one, it will ask the user for the id and check if it exists or not
    cout << ENTER_ID;
    cin >> projId;
    cin.get();

    for (unsigned int i=0;i < Projects.projects.size() && !found;i++)
      if(Projects.projects[i].id==projId)
        found=true;
      
    if(!found){
      error(ERR_ID);
      errId=true;
    }
  }
  else
    projId=0;                                                              //If the user wants to export all of them, projId will be saved as 0, which can't ba a project id since they start from 1

  if(!errId){
    cout<<ENTER_FILE;
    getline(cin,filename);

    file.open(filename);
    if(file.is_open()){
      exportingProj(Projects,file,projId);                                //If there is no problem with the file and the id, the program will start exporting it or them

      file.close();
    }
    else
      error(ERR_FILE);
  }
}

void loadingData(ToDo &Projects, ifstream &file, string filename,bool &doneArg){    //Module created to start loading the data
  BinToDo binTodo;
  Project newProject;
  BinProject binProj;
  List newList;
  BinList binList;
  Task newTask;
  BinTask binTask;
  unsigned int i,j,k;

  if(!Projects.projects.empty() && doneArg)                                 //If there are projects from before, they will be deleted as specified, but also if there are arguments whose changes haven't been done, it will mark them as completed with the bool variable in the else
    Projects.projects.clear();
  else
    doneArg=true;
  
  file.read((char*)&binTodo,sizeof(BinToDo));                               //Then, it will start readinng al the information, which will be save in their corresponding project (i), lists (j) and task (k)
  Projects.name=binTodo.name;

  for(i=0;i<binTodo.numProjects;i++){
    file.read((char*)&binProj,sizeof(BinProject));
    newProject.name=binProj.name;
    newProject.description=binProj.description;
    newProject.id=i+1;
    Projects.projects.push_back(newProject);

    for(j=0;j<binProj.numLists;j++){
      file.read((char*)&binList,sizeof(BinList));
      newList.name=binList.name;
      Projects.projects[i].lists.push_back(newList);

      for(k=0;k<binList.numTasks;k++){
        file.read((char*)&binTask,sizeof(BinTask));
        newTask.name=binTask.name;
        newTask.deadline=binTask.deadline;
        newTask.isDone=binTask.isDone;
        newTask.time=binTask.time;
        Projects.projects[i].lists[j].tasks.push_back(newTask);
      }
    }
    Projects.nextId=i+2;                                            //After loading all of them, the nextId would be the current position of the last project plus 2
  }
}

void loadData(ToDo &Projects, string filename,bool &doneArg,bool &finishedArg){            //Module for the option 6, loading projects from binary files
  ifstream file;
  char option='y';      //This variable is set to 'y' so when using arguments it won't give any problems

  if(doneArg){                          //If there are no arguments or the changes for the arguments have been applied, this module will ask for the name of the file and open it
    cout<<ENTER_FILE;
    getline(cin,filename);
  }
  

  file.open(filename,ios::binary);
  if(file.is_open()){
    if(doneArg){
      do{
        cout << "Confirm [Y/N]?: ";                           
        cin >> option;
      }while(option!='Y' && option!='y' && option!='n' && option!='N');
    }
    
    if(option=='Y' || option=='y')                        //After the user confirms that they want to load the data, the previous module will start loading it
      loadingData(Projects,file,filename,doneArg);
    
    file.close();
  }
  else{
    error(ERR_FILE);        //If the file can't be opened, it will show an error, and it the changes of an argument couldn't be done, the bool variable will be set to false, which later will cause the program to close after not being able to open the argument, without showing the menu
    if(!finishedArg)
      doneArg=false;
  }
}

void savingData(ToDo &Projects,ofstream &file){                       //Module created to save the information of the projects
  BinToDo binTodo;
  BinProject binProj;
  BinList binList;
  BinTask binTask;
  unsigned int i,j,k;

  strncpy(binTodo.name,Projects.name.c_str(),KMAXNAME-1);               //First, it passes the string to a char array with the specified size, even if it is smaller, and will make this will all the strings in the projects
  binTodo.name[KMAXNAME-1]='\0';
  binTodo.numProjects=Projects.projects.size();
  file.write((const char*)&binTodo,sizeof(BinToDo));

  for(i=0;i<Projects.projects.size();i++){                                                  //It will write all the information from all the projects, lists and tasks
    strncpy(binProj.name,Projects.projects[i].name.c_str(),KMAXNAME-1);
    binProj.name[KMAXNAME-1]='\0';
    strncpy(binProj.description,Projects.projects[i].description.c_str(),KMAXDESC-1);
    binProj.description[KMAXDESC-1]='\0';
    binProj.numLists=Projects.projects[i].lists.size();
    file.write((const char*)&binProj,sizeof(BinProject));

    for(j=0;j<Projects.projects[i].lists.size();j++){
      strncpy(binList.name,Projects.projects[i].lists[j].name.c_str(),KMAXNAME-1);
      binList.name[KMAXNAME-1]='\0';
      binList.numTasks=Projects.projects[i].lists[j].tasks.size();
      file.write((const char*)&binList,sizeof(BinList));

      for(k=0;k<Projects.projects[i].lists[j].tasks.size();k++){
        strncpy(binTask.name,Projects.projects[i].lists[j].tasks[k].name.c_str(),KMAXNAME-1);
        binTask.name[KMAXNAME-1]='\0';
        binTask.deadline=Projects.projects[i].lists[j].tasks[k].deadline;
        binTask.isDone=Projects.projects[i].lists[j].tasks[k].isDone;
        binTask.time=Projects.projects[i].lists[j].tasks[k].time;
        file.write((const char*)&binTask,sizeof(BinTask));
      }
    }
  }
}

void saveData(ToDo &Projects){            //Module for the option 7, saving the projects into a binary file    
  ofstream file;
  string filename;
  
  cout<<ENTER_FILE;                   
  getline(cin,filename);

  file.open(filename,ios::binary);          //After asking for the name of the file, it will be opened and the previous module will start writing in the file
  if(file.is_open()){
    savingData(Projects,file);

    file.close();
  }
  else{
    error(ERR_FILE);
  }
}

void summary(const ToDo Projects){             //Module for the option 8, showing the basic information of all the projects
  unsigned int i,j,k,taskCounter,completedCounter;

  if(!Projects.projects.empty()){                         //If there are projects, it will start printing the information
    for(i=0;i<Projects.projects.size();i++){
      cout << "(" << Projects.projects[i].id << ") "
           << Projects.projects[i].name << " [";

      taskCounter=0;                                            //We will also set counters for all the tasks and the completed tasks and will count them in the following for loop, to show then the information between brackets
      completedCounter=0;

      for(j=0;j<Projects.projects[i].lists.size();j++){
        for(k=0;k<Projects.projects[i].lists[j].tasks.size();k++){
          if(Projects.projects[i].lists[j].tasks[k].isDone)
            completedCounter++;
          taskCounter++;
        }
      }

      cout << completedCounter << "/" << taskCounter << "]" << endl;
    }
  }
}

void checkArgs(int argc, char *argv[], bool &errArg){           //Module created to check the arguments entered by the user

  if(argc>5){                                                           //This module checks all the posible problems with the arguments (more than 5, missing arguments, not the proper arguments name,etc.)
    errArg=true;                                                          //This bool variable will change to true if there is a problem, which will make the program to stop
  }
  else if(argc%2==0){
    errArg=true;
  }
  else if((strcmp(argv[1],"-i")!=0 && strcmp(argv[1],"-l")!=0)){
    errArg=true;
  }
  else if(argc>3){
    if(strcmp(argv[1],argv[3])==0){
      errArg=true;
    }
    else if(argc>3 && ((strcmp(argv[3],"-i")!=0 && strcmp(argv[3],"-l")!=0))){
      errArg=true;
    }
  }   
}

void programArg(ToDo &Projects,int argc, char *argv[], bool &errArg, bool &dataLoaded, bool &binLoaded, bool &finishedArg){   //Module created to handle the arguments entered for the program

  checkArgs(argc,argv,errArg);                                      //First, it will check if there are any problems with the arguments entered, if there are no problems, it will do the corresponding actions depending on them

  if(!errArg){
    finishedArg=false;                                                  //We set this bool variable to false to indicate that we are doing changes with arguments, before showing the menu
    if(argc==3){                                                        //If there are 3 valid arguments, it means that we have to do the corresponding changes depending on argv[1] 
      if(strcmp(argv[1],"-i")==0){
        dataLoaded=false;                                                 //This bool variable will be set as false and will only set back to true if the data has been correctly loaded
        importProjects(Projects,argv[2],dataLoaded,finishedArg);
      }
      if(strcmp(argv[1],"-l")==0){
        binLoaded=false;
        loadData(Projects,argv[2],binLoaded,finishedArg);
      }
    }
    else{                                                              //If there aren't 3 arguments, it means that there are 5 valid arguments
      dataLoaded=false;
      binLoaded=false;
      if(strcmp(argv[3],"-i")==0){                                        //First, it will always execute loadData, since it deletes the previous data, then it will executeimportProjects to add them, the program has to check what is argv[] to know which filenames pass to each module
        loadData(Projects,argv[2],binLoaded,finishedArg);
        importProjects(Projects,argv[4],dataLoaded,finishedArg);
      }
      else{
        loadData(Projects,argv[4],binLoaded,finishedArg);
        importProjects(Projects,argv[2],dataLoaded,finishedArg);
      }
    }
    finishedArg=true;
  }
  else
    error(ERR_ARGS);
}

int main(int argc, char *argv[]){                 //This is the main module, which know also receives the information of the arguments
  ToDo Projects;
  char option;
  bool errArg=false,dataLoaded=true,binLoaded=true,finishedArg=true;    //This bool variables are already set so when there are no arguments, they don't give problems
  string filename;

  Projects.nextId=1;
  Projects.name="My ToDo list";

  if(argc>1)                                                                  //If there is more than one argument (which always is the execution of the program), it the program have to check them
    programArg(Projects,argc,argv,errArg,dataLoaded,binLoaded,finishedArg);
  
  if(!errArg && dataLoaded && binLoaded){                                         //If there are no errors and the file could be opened and loaded, the program can start working as usual and show the main menu
    do{
      showMainMenu();
      cin >> option;
      cin.get();
      
      switch(option){
        case '1': checkProjectMenu(Projects);
                  break;
        case '2': addProject(Projects);
                  break;
        case '3': deleteProject(Projects);
                  break;
        case '4': importProjects(Projects,filename,dataLoaded,finishedArg);
                  break;
        case '5': exportProjects(Projects);
                  break;
        case '6': loadData(Projects,filename,binLoaded,finishedArg);
                  break;
        case '7': saveData(Projects);
                  break;
        case '8': summary(Projects);
                  break;
        case 'q': break;
        default: error(ERR_OPTION);
      }
    }while(option!='q');
  }
  return 0;    
}