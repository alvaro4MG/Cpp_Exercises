

#include "Task.h"
#include "Util.h"


Task::Task(string name){
    this->name=name;
    isDone=false;
    time=1;
    deadline.day=1;
    deadline.month=1;
    deadline.year=2000;
}

Date Task::getDeadline() const{
    return deadline;
}

void Task::setName(string name){
    this->name=name;
}

bool Task::setDeadline(string deadline){
    bool err_date=false;
    string strTask;
    Date checkDate;

    strTask=deadline.substr(0,deadline.find('/'));
    checkDate.day=stoi(strTask);
    deadline.erase(0,deadline.find('/')+1);
    strTask=deadline.substr(0,deadline.find('/'));
    checkDate.month=stoi(strTask);
    deadline.erase(0,deadline.find('/')+1);
    checkDate.year=stoi(deadline);

    if(checkDate.year<2000 || checkDate.year>2100 || checkDate.month>12 || checkDate.day>31 || checkDate.day<1 || checkDate.month<1)   //Then, it will check if the date exists, using the corresponding conditions to avoid an invalid date (which will set err_date to true)
        err_date=true;
    else if(((checkDate.month%2==0 && checkDate.month<=7) || (checkDate.month%2==1 && 
                checkDate.month>=8)) && checkDate.day==31)
        err_date=true;
    else if(checkDate.month==2 && checkDate.day>28){
        if(((checkDate.year%4==0 && checkDate.year%100!=0)||(checkDate.year%100==0 && 
                checkDate.year%400==0)) && checkDate.day==29)
            err_date=false;
        else
            err_date=true;
    }
    else
        err_date=false;

    if(err_date){
        Util::error(ERR_DATE);
        return false;
    }
    else{
        this->deadline=checkDate;
        return true;
    }

}

bool Task::setTime(int time){

    if(time<1 || time>180){
        Util::error(ERR_TIME);
        return false;
    }
    else{
        this->time=time;
        return true;
    }
    
}

void Task::toggle(){
    if(isDone)
        isDone=false;
    else
        isDone=true;
}


ostream& operator<<(ostream &os, const Task &task){

    os << "[";

    if(task.isDone)
        os<<"X";
    else
        os<<" ";
    
    os<<"] (" << task.getTime() << ") "<< 
    task.deadline.year << "-" << task.deadline.month << "-" << task.deadline.day << " : " << task.getName() << endl;

    return os;
}
