//Try copy vectors

#include<iostream>
#include<vector>
#include<cstdlib>

using namespace std;

struct Date{
  int day;
  int month;
  int year;
};

struct Task{
  string name;
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

void copyString(List &list, string str2, int num);

int main(){
  Date date;
  bool er_date;
  List list;
  Project toDoList;
  vector <char> str;
  vector <char> trying;
  string fill;
  string new_string;
  string day,month,year,s;

  //cin>>trying;
  //str.push_back(trying);

  //cout<<str[0]<<endl;

  /*getline(cin,fill);

  copyString(list,fill,1);

  cout<<fill<<endl;
  cout<<list.name<<endl;*/

  //list.name.push_back(fill);

  new_string="enter";
  list.name=new_string;

  toDoList.lists.push_back(list);                   //You can do a push_back of a struct


  for(int i=0;(unsigned)i<new_string.size();i++){       //This works, but maybe isn't the best way (too many iterations per work), and needs the list to be pushed back first
    toDoList.lists[0].name.push_back(new_string[i]);
  }

  cout<<toDoList.lists[0].name<<endl;             //Need to push back lists, have to know how (push_back a new_list)
      
  do{
    cout<<"Enter deadline (dd-mm-yy, between 2000 and 2100): ";
    //cin>>date.day>>date.month>>date.year;
    getline(cin,s,'/');
    date.day=stoi(s);           //stoi works like this
    getline(cin,s,'/');
    date.month=stoi(s);
    getline(cin,s);
    date.year=stoi(s);
    cout<<date.day<<date.month<<date.year<<endl;
    
    cout<<date.day+1;

    if(date.year<2000 || date.year>2100 || date.month>12 || date.day>31){
      cout<<"mal 1"<<endl;
      er_date=false;
    }
    else if(((date.month%2==0 && date.month<=7) || (date.month%2==1 && date.month>=8)) && date.day==31){
      cout<<"mal 2"<<endl;
      er_date=false;
    }
    else if(date.month==2 && date.day>28){  //Enter the previous here
      if(((date.year%4==0 && date.year%100!=0)||(date.year%100==0 && date.year%400==0)) && date.day==29){
        cout<<"bien bisi"<<endl;
        er_date=true;
      }
      else{
        cout<<"mal 4"<<endl;
        er_date=false;
      }
    }
    else{
      cout<<"bien"<<endl;
      er_date=true;
    }

    //if()                      //Check error in date, also leap years, leap years are divisible by 4 and by 100 (use xxxx%4!=0) || divisible 110 and 400, and odd and even with 31 change in august
  }while(er_date==false);   //Maybe use a bool for this error since it has 4 condition (2 for year and 2 for month)
          //Leap years are divisible by 4 but 
            //If they are divisible by 100, must be also divisible by 400 (2000 is but 2100 isn't)
          //Months are 31 days in odd until 7 and in even from 8


  return 0;
}

void copyString(List &list, string str2, int num){      //Doesn't work, pass full list and with a switch change it, passing what we want to do as an int
  //string str1;

  cout<<num;

  switch (num){                                     //Switch works
    case 1:

        for(int i=0;(unsigned)i<str2.size();i++){       //This works, but maybe isn't the best way (too many iterations per work)
          list.name.push_back(str2[i]);
        }
      break;
  }
  
}

/*for(unsigned int j=0;j<toDoList.lists[i].tasks.size();j++){
      tasks++;
      total_tasks+=toDoList.lists[i].tasks[j].time;
      

      if(toDoList.lists[i].tasks[j].isDone==false)
        cout<<"[ ] ";
      else{
        cout<<"[X] ";
      }
      cout << "(" << toDoList.lists[i].tasks[j].time << ") " << toDoList.lists[i].tasks[j].deadline.year << "-" << toDoList.lists[i].tasks[j].deadline.month << "-" << toDoList.lists[i].tasks[j].deadline.day << " : "
           << toDoList.lists[i].tasks[j].name << endl;

      if(toDoList.lists[i].tasks[j].isDone==true){
        done++;
        total_done+=toDoList.lists[i].tasks[j].time;
      }
      else{
        if(high_pri.name.empty()==true){
          high_pri=toDoList.lists[i].tasks[j];
        }
        else{
          if(toDoList.lists[i].tasks[j].deadline.year < high_pri.deadline.year){
            high_pri=toDoList.lists[i].tasks[j];
          }
          else if(toDoList.lists[i].tasks[j].deadline.year == high_pri.deadline.year){
            if(toDoList.lists[i].tasks[j].deadline.month < high_pri.deadline.month){
              high_pri=toDoList.lists[i].tasks[j];
            }
            else if(toDoList.lists[i].tasks[j].deadline.month == high_pri.deadline.month){
              if (toDoList.lists[i].tasks[j].deadline.day < high_pri.deadline.day){
                high_pri=toDoList.lists[i].tasks[j];
              }
            }
          }
        }
      }
    }*/