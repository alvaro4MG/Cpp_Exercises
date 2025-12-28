//Abderrahmane Guermat Benaouali 51771088C
#include "Example.h"


using namespace std;



int Example::nextId=1;

Example::Example(string text){


     if(text!="")//ver si cadena introducida esta vacia
	 {	     
	     vector<string> Etokens=Util::extractTokens(text);	     
	     if(Etokens.size()>0){
			this->text=text;
			this->id=this->nextId;
			for(unsigned i=0;i<Etokens.size();i++)		   
			  this->tokens.push_back(Etokens[i]);			
			this->nextId++;
		 }
		 else
		   throw ERR_EMPTY;
	 }
	 else
	    throw ERR_EMPTY;      
}



void Example::resetNextId(){
	nextId=1;
}

int Example::getId()const{
  return this->id;
}

string Example::getText() const{
   return this->text;
}

vector<string> Example::getTokens() const{
	return this->tokens;
}


vector<string>Example::BorrarRepetidos(const vector<string> &tokens){

   vector<string> newTokens;
   newTokens=tokens;
   
   if(tokens.size()>0){
	for(int i=0;(unsigned)i < newTokens.size()-1;i++)
	{		
		for(int j=(i+1);(unsigned)j < newTokens.size();j++)
		{		
			if(newTokens[i]==newTokens[j])
			{			
				newTokens.erase(newTokens.begin()+j);
				j--;
				i--;
		    }
		}		
	 }
	} 
	return newTokens;
}

int Example::getComun( const vector<string> &auxTconsulta, const vector<string> &auxTexample)
{
	int comun=0;

	for(int i=0;(unsigned)i<auxTconsulta.size();i++)
	{		    
			for(int j=0;(unsigned)j<auxTexample.size();j++)
			{
 				if(auxTconsulta[i]==auxTexample[j]) 			
				  comun++;			  
		    }	
    }
        
    return comun;
}


float Example::Similitud(const vector<string> &Consulta,const vector<string> &Actual)
{	
	vector<string> ConsultaNR=Example::BorrarRepetidos(Consulta);		        
    vector<string> ActualNR=Example::BorrarRepetidos(Actual);	     

    float CJ;//para guardar el coficiente de jjacar de cada ejemplo			  
	int TamConsultaNR=ConsultaNR.size();
	int TamActualNR=ActualNR.size();
	int TamComun=Example::getComun(ConsultaNR,ActualNR);//almacenara el numero de palabras en comun
				  
	if(((float)TamConsultaNR+(float)TamActualNR-(float)TamComun)>0)//para no dividir entre 0
		CJ=(float)TamComun/((float)TamConsultaNR+(float)TamActualNR-(float)TamComun);//se calcula el coificiente
	else 
		CJ=0.0;
		
	return CJ;

}

float Example::jaccardSimilarity(string text)const{
	
	vector<string> Consulta=Util::extractTokens(text);	
	vector<string> Actual=this->getTokens();//llamar a getTokens()
		     
	float CJ=Example::Similitud(Consulta,Actual);
	return CJ;
}

vector<string>Example::extraeNgramas(const vector<string> tokens )
{
    vector<string> ngramas;//se declara el vector de 3-gramas que se devolvera
    for(int i=0;(unsigned)i<tokens.size();i++)//recorrer los tokens	
    {
	   if(tokens[i].length()>=3)//ver si el token tiene como minimo 3 letras	   
	   {
		    for(int j=0;(unsigned)j<tokens[i].length();j++)//recorremos un token caracter a caracter para extraer 3-gramas
		    {
			  if(tokens[i].length()-j>=3)//comprobar que aun podemos extraer un 3-grama;(es decir no estar en el ultimo caracter o penultimo) (palabra >=3)
			  {				 
			    string grama=tokens[i].substr(j,3);//extraemos un 3-grama
			    ngramas.push_back(grama);//metemos el 3-grama en en el vector
			  }			
			}		   
	    }
	}
	return ngramas;
}

float Example::ngramSimilarity(string text)const{
	vector<string> Consulta=Util::extractTokens(text);	
	vector<string> Actual=this->getTokens();//llamar a getTokens()
	
	vector<string> ConsultaNG=Example::extraeNgramas(Consulta);		        
    vector<string> ActualNG=Example::extraeNgramas(Actual);	     

	float CJ=Example::Similitud(ConsultaNG,ActualNG);
	return CJ;
}

ostream& operator<<(ostream &os,const Example &ex){

	os<<"Example "<<ex.id<<": "<<ex.text<<endl;
	os<<"Tokens "<<ex.id<<":";
	for(int i=0;(unsigned)i< ex.tokens.size();i++){
		os<<" <"<<ex.tokens[i]<<">";
	}
	return os;
}

