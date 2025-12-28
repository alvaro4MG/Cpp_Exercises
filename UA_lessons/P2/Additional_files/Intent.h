//Abderrahmane Guermat Benaouali 51771088C
#ifndef _INTENT_
#define _INTENT_



#include <iostream>
#include <vector>
#include "Example.h"
using namespace std;

class Intent
{
	friend  ostream& operator<<(ostream &os,const Intent &in);
    protected:
      
        string name;
        string response;
        vector<Example> examples;
                       
    public:
    
       static const unsigned KMAXEXAMPLES;               
       Intent(string name);
       string getName()const;
       string getResponse()const;
       vector<Example> getExamples()const;
       unsigned getNumExamples()const;
       void addExample(const Example &example);
       void deleteExample(int id);
       void addResponse(string response);
       float calculateSimilarity(string text,const char similarity[]) const;       
};


#endif

