// DNI 48150407E Martínez García, Álvaro (7930)

#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

const int MAX_YEAR = 2100;    //Since this is a tasks list program, the maximum and minimum year available can be changed easily from here
const int MIN_YEAR = 2000;
const string ENTER_TASK = "Enter task name: ";   //This text appears more than once, so it can be set as a constant

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

struct List{
  string name;
  vector<Task> tasks;
};

struct Project{
  int id;
  string name;
  string description;
  vector<List> lists;
};

enum Error{
  ERR_OPTION,
  ERR_EMPTY,
  ERR_LIST_NAME,
  ERR_TASK_NAME,
  ERR_DATE,
  ERR_TIME
};

enum option{            //Enumeration for the type of action that we want to do with the name of the list entered, so it will be easier to see on the code in general and the switch
  NUM_ADD,
  NUM_DEL,
  NUM_CMP
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
  }
}

void showMainMenu(){
  cout << "1- Edit project" << endl
       << "2- Add list" << endl
       << "3- Delete list" << endl 
       << "4- Add task" << endl
       << "5- Delete task" << endl
       << "6- Toggle task" << endl
       << "7- Report" << endl
       << "q- Quit" << endl
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

void getListName(string &new_string){   //Module created to ask for the name of the list, since it is asked in more than one function
                                              //It will use a string "new_string" that will change in the module where it was called since it is passed as a reference
  do{                                     //The name can't be empty so if "new_string" is empty, it will ask again for it, having a similar structure as the do-while used in editProject
    cout<<"Enter list name: ";
    getline(cin,new_string);

    if(new_string.empty()==true)
      error(ERR_EMPTY);
                       
  }while(new_string.empty()==true);
}

int checkList(Project &toDoList, string check_string, option operation){    //Function created to check if the name of the list entered (stored in "check_string") exists in toDoLost
  int i;                                                                      //The function will return i, the position that occupies the list that we are looking for, or -1, to indicate that there's no list with that name
  bool found=false;

  if(toDoList.lists.size()==0 && (operation == NUM_DEL || operation == NUM_CMP)){     //To avoid errors when checking for a string (idicated by NUM_DEL or NUM_CMP), we use this if condition to send an error when there's no lists yet
    error(ERR_LIST_NAME);
    return -1;
  }
  for(i=0;(unsigned)i<toDoList.lists.size() && !found;i++){       //We want to check all the lists, so we will use size to obtain an unsigned number (so we use i as an unsigned too)
    if(check_string==toDoList.lists[i].name){                       //If there's a list name which is the same as "check_string", found will be set to true and we will make the corresponding actions
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
  string new_string;
  List new_list;
  int i,j;

  getListName(new_string);                      //We will use GetListName and checkList here like in the rest of the modules, to get the list name in "new_string" and to know if we can continue with the rest of the instructions in the module
  i = checkList(toDoList,new_string,NUM_ADD);

  if(i!=-1){                                       //If i isn't -1 (which means there has been an error, a list already with that name in that case), the list will be added. The use of i in this way will let us use it lñike a bool variable, so that false or error means -1 and true is the rest
    for(j=0;(unsigned)j<new_string.length();j++){       //To copy the name entered before, we will use a for loop as much times as the length of "new_string", pushing back each letter in the name of "new_list"
      new_list.name.push_back(new_string[j]);
    }
    toDoList.lists.push_back(new_list);             //Once we have the name of the list, we can push it back in the lists of the project
  }

}

void deleteList(Project &toDoList){     //Module to delete a list (and all its components too)
  string check_string;
  int i;

  getListName(check_string);
  i = checkList(toDoList,check_string,NUM_DEL);

  if(i!=-1){                                          //If there's no error with the list name entered (which means there is a list with that name), we will erase the list with the position i returned
    toDoList.lists.erase(toDoList.lists.begin()+i);
  }

}

void checkDate (Task &new_task,bool &err_date){   //Module created to ask for the deadline date, so it is easier to work with it
  string s;

  cout<<"Enter deadline: ";           //Since we suppose that the user will always enter the deadline in the right way (dd/mm/yyyy), we can just read until there is a /
  getline(cin,s,'/');                   //Once we read the first in the string s, which is only used to pass the information, we need to make it an integer number
  new_task.deadline.day=stoi(s);          //To do that we will use stoi with the s string each time and save the number in the deadline of the new task
  getline(cin,s,'/');
  new_task.deadline.month=stoi(s);
  getline(cin,s);
  new_task.deadline.year=stoi(s);      

  if(new_task.deadline.year<MIN_YEAR || new_task.deadline.year>MAX_YEAR || new_task.deadline.month>12 || new_task.deadline.day>31)   //Then, it will check if the date exists, using the corresponding conditions to avoid an invalid date (which will set err_date to true)
    err_date=true;
  else if(((new_task.deadline.month%2==0 && new_task.deadline.month<=7) || (new_task.deadline.month%2==1 && 
            new_task.deadline.month>=8)) && new_task.deadline.day==31)
    err_date=true;
  else if(new_task.deadline.month==2 && new_task.deadline.day>28){
    if(((new_task.deadline.year%4==0 && new_task.deadline.year%100!=0)||(new_task.deadline.year%100==0 && 
         new_task.deadline.year%400==0)) && new_task.deadline.day==29)
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
  string str_list,str_task;
  Task new_task;
  bool err_date;
  int i;

  getListName(str_list);
  i=checkList(toDoList,str_list,NUM_CMP);

  if(i!=-1){
    cout<<ENTER_TASK;
    getline(cin,str_task);

    if(str_task.empty()==false)                        //If the name of the task isn't empty (it is allowed to be or not), it will be copied in "new_task"
      for(int j=0;(unsigned)j<str_task.length();j++)
        new_task.name.push_back(str_task[j]);
    
    new_task.isDone=false;                                //Also the new task isDone must be set to false (it is a new task, so it isn't completed yet)

    checkDate(new_task,err_date);                       //It will ask for the deadline date and will get the value of the bool variable "err_date" in order to see if the user can enter the following information
    
    if(err_date==false){
      cout<<"Enter expected time: ";
      cin>>new_task.time;

      if(new_task.time<1 || new_task.time>180)                     //When asked for the time to complete, it has to be between 1 and 180, and if it isn't it must show the error and it won't push back the new task, which can only be done whene the date entered is correct
        error(ERR_TIME);
      else
        toDoList.lists[i].tasks.push_back(new_task);
    }
  }
}

void deleteTask(Project &toDoList){   //Module to delete a task
  string str_list,str_task;
  bool found=false;
  int i,j;

  getListName(str_list);
  i=checkList(toDoList,str_list,NUM_CMP);

  if(i!=-1){
    cout<<ENTER_TASK;
    getline(cin,str_task);

    for(j=0;(unsigned)j<toDoList.lists[i].tasks.size();j++){              //When looking for tasks with the name entered, it doesn't have stop after deleting since it has to delete all tasks with the same name, so when we change found after the first coincidence, it will be used for the error (if there isn't a single task with that name, found will keep false)
      if(str_task==toDoList.lists[i].tasks[j].name){
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
  string str_list,str_task;
  int i,j;
  bool found=false;

  getListName(str_list);
  i=checkList(toDoList,str_list,NUM_CMP);

  if(i!=-1){
    cout<<ENTER_TASK;
    getline(cin,str_task);
    
    for(j=0;(unsigned)j<toDoList.lists[i].tasks.size();j++){    //It will look through all the list all the tasks with the same name and change them from false to true and viceversa
      if(str_task==toDoList.lists[i].tasks[j].name){
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
  int done=0, total_done=0, tasks=0, total_tasks=0;        //Since the report must show the amount of total tasks, tasks done and their respective amount of minutes, we will declare them and initialize as 0, whose value we will increase
  Task high_pri;                                               //It must show the task with the highest priority, name and deadline, so we will save it in high_pri

  cout << "Name: "<<toDoList.name<<endl;
  if(toDoList.description.empty()==false)                      //If the description is empty, "Description" shouldn't appear
    cout << "Description: "<< toDoList.description << endl;
  
  for(unsigned int i=0;i<toDoList.lists.size();i++){           //It has to show all the tasks of all the lists, but it must show the ones that aren't completed yet, so in each list iteration it will first show the uncompleted task and then, in another for loop, it will show the completed ones
    cout << toDoList.lists[i].name << endl;

    for(unsigned int j=0;j<toDoList.lists[i].tasks.size();j++){   //In the first for loop, we will start using the task and total_tasks 
      tasks++;
      total_tasks+=toDoList.lists[i].tasks[j].time;
      
      if(toDoList.lists[i].tasks[j].isDone==false){
        cout <<"[ ] " << "(" << toDoList.lists[i].tasks[j].time << ") " << toDoList.lists[i].tasks[j].deadline.year << "-" << toDoList.lists[i].tasks[j].deadline.month << "-" 
             << toDoList.lists[i].tasks[j].deadline.day << " : " << toDoList.lists[i].tasks[j].name << endl;
        
        if(high_pri.name.empty()==true)                                                      //If high_pri hasn't been set yet, it will take the value of the first uncompleted task, so it can be compared to the rest of the tasks
          high_pri=toDoList.lists[i].tasks[j];
        else{
          if(toDoList.lists[i].tasks[j].deadline.year < high_pri.deadline.year)                  //For the next uncompleted task, it will check if the year, month and day are lower and set high_pri as this task
            high_pri=toDoList.lists[i].tasks[j];
          else if(toDoList.lists[i].tasks[j].deadline.year == high_pri.deadline.year){
            if(toDoList.lists[i].tasks[j].deadline.month < high_pri.deadline.month)
              high_pri=toDoList.lists[i].tasks[j];
            else if(toDoList.lists[i].tasks[j].deadline.month == high_pri.deadline.month)
              if (toDoList.lists[i].tasks[j].deadline.day < high_pri.deadline.day)
                high_pri=toDoList.lists[i].tasks[j];
          }
        }
      }
    }

    for(unsigned int j=0;j<toDoList.lists[i].tasks.size();j++){

      if(toDoList.lists[i].tasks[j].isDone==true){
        cout <<"[X] " << "(" << toDoList.lists[i].tasks[j].time << ") " << toDoList.lists[i].tasks[j].deadline.year << "-" << toDoList.lists[i].tasks[j].deadline.month << "-" 
             << toDoList.lists[i].tasks[j].deadline.day << " : " << toDoList.lists[i].tasks[j].name << endl;
        
        done++;                                                //For the completed tasks, we start counting them for the done tasks variables
        total_done+=toDoList.lists[i].tasks[j].time;
      }
    }
    cout<<endl;
  }

  cout << "Total left: " << tasks-done << " (" << total_tasks-total_done << " minutes)" << endl;
  cout << "Total done: " << done << " (" << total_done << " minutes)" << endl;

  if(tasks-done!=0)                                                 //If there's no task or all of them are completed, the highest priority line doesn't have to appear
    cout << "Highest priority: " << high_pri.name << " (" << high_pri.deadline.year << "-" << high_pri.deadline.month << "-" << high_pri.deadline.day << ")" << endl;
}

int main(){
  Project toDoList;
  toDoList.id=1;
  char option;
  
  do{
    showMainMenu();
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
      case 'q': break;
      default: error(ERR_OPTION);
    }
  }while(option!='q');
  
  return 0;    
}