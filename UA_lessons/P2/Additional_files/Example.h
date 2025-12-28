//Abderrahmane Guermat Benaouali 51771088C
#ifndef _EXAMPLE_
#define _EXAMPLE_



#include <iostream>
#include <vector>
#include "Util.h"
using namespace std;

class Example{


    friend  ostream& operator<<(ostream &os,const Example &ex);
    protected:
    
        int id;
        string text;
        vector<string> tokens;
        static int nextId;
        static vector<string>  BorrarRepetidos(const vector<string> &tokens);
        static int getComun(const vector<string> &auxTconsulta, const vector<string> &auxTexample);
        static vector<string> extraeNgramas(const vector<string> tokens);
        static float Similitud(const vector<string> &Consulta,const vector<string> &Actual);
        
        
    public:
    
       Example(string text);
       static void resetNextId();
       int getId() const;
       string getText()const;
       vector<string> getTokens()const;   
       float jaccardSimilarity(string text)const;
       float ngramSimilarity(string text)const;             
};


#endif


