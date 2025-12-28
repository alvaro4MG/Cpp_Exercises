//Abderrahmane Guermat Benaouali 51771088C
#include "Intent.h"
#include <cstring>
const unsigned Intent::KMAXEXAMPLES=10;


Intent::Intent(string name)
{
	if(name!=""){
       this->name=name;
	}
	else
		throw ERR_EMPTY;
}


void Intent::addExample(const Example &example){


	if(getNumExamples()< KMAXEXAMPLES){

		examples.push_back(example);
	}
	else{
		throw ERR_MAXEXAMPLES;
	}
}


void Intent::deleteExample(int id){

	int pos=-1;
	for(unsigned i=0;i<getNumExamples();i++){
		if(examples[i].getId()==id){
			pos=i;
			break;
		}
	}

   if(pos!=-1)//si el ejemplo existe se borra
   {
		examples.erase(examples.begin()+pos);
   }else{
	   throw ERR_EXAMPLE;
   }
}


void Intent::addResponse(string response){
	this->response=response;
}

string Intent::getName()const{
	return this->name;
}



string Intent::getResponse()const{
	return this->response;
}
vector<Example> Intent::getExamples()const{
	return this->examples;
}
unsigned Intent::getNumExamples()const{
	return this->examples.size();
}

float Intent::calculateSimilarity(string text,const char similarity[]) const{

	float CJmax=0;

	char jc[3];
	strcpy(jc,"jc");
	char ng[3];
	strcpy(ng,"ng");
	if(strcmp(similarity,jc)==0 || strcmp(similarity,ng)==0  ){

		for(unsigned i=0;i<getNumExamples();i++){
			float CJ=0;
			if(strcmp(similarity,jc)==0)//en caso de que el coificiente sea jc
			{
                CJ=examples[i].jaccardSimilarity(text);
			}
			else
			{
				CJ=examples[i].ngramSimilarity(text);
			}
			CJmax=max(CJmax,CJ);
		}
	}
	else
	{
		throw ERR_SIMILARITY;
	}

	return CJmax;
}


ostream& operator<<(ostream &os,const Intent &in){

	 os<<"Intent: "<<in.name<<"\n";
	 os<<"Response: "<<in.response<<"\n";
     for(unsigned i=0;i<in.getNumExamples();i++){
    	 os<<in.examples[i]<<endl;
     }
     return os;
}




















