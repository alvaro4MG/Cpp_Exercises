//Abderrahmane Guermat Benaouali 51771088C
#include "Chatbot.h"
#include <cstring>

Chatbot::Chatbot()
{
	this->threshold=0.25;
	strcpy(this->similarity,"jc");
}


Chatbot::Chatbot(float threshold,const char similarity[])
{

	char jc[3];
	strcpy(jc,"jc");
	char ng[3];
	strcpy(ng,"ng");

	if(threshold>=0 && threshold<=1)
	{

		this->threshold=threshold;
		if(strcmp(similarity,jc)==0 || strcmp(similarity,ng)==0  )
		{
		    strcpy(this->similarity,similarity);
		}
		else
		{
          throw ERR_SIMILARITY;
		}
	}
	else
	{
      throw ERR_THRESHOLD;
	}

}

float Chatbot::getThreshold() const{
	return this->threshold;
}

string Chatbot::getSimilarity() const{
	return this->similarity;
}



int Chatbot::searchIntent(string name) const{

	   int pos=-1;
	   for(int i=0;(unsigned)i<intents.size();i++)//bucle que recorrera las intenciones
	   {
		 if(name==intents[i]->getName())//ver si los nombres coinciden
		 {
			pos=i;
			break;
		 }
	   }

	   return pos;
}






bool Chatbot::addIntent(Intent *pIntent){

	bool added=false;
   int i=searchIntent(pIntent->getName());

   if(i==-1)
   {
     intents.push_back(pIntent);
     added=true;
   }
   else
   {
	   Util::error(ERR_INTENT);
   }
 return added;
}

bool Chatbot::deleteIntent(string name,bool askConfirm)
{


    bool deleted=false;
	if(name==""){
		cout<<"Intent name: ";
		getline(cin,name);
	}

   int i=searchIntent(name);


   if(i==-1)//seria cierta en caso de que ninguna intencion coincida con el numbre
   {
      Util::error(ERR_INTENT);
   }
   else//en caso de que la intencion exista
   {

	   	string confirm="y";//se inicia a y , en caso de que no haya q confirmar se pase a borrar
	   	if(askConfirm==true){
			do
			{
				cout<<"Confirm [Y/N]?: ";
				cin>>confirm;
				cin.get();
			}while(confirm!="Y" && confirm!="y" && confirm!="n" && confirm!="N" );//bucle que mostrara el mensaje de la confirmacion

	   	}

	    if(confirm=="Y" || confirm=="y")//en caso de que se haya confirmado el eliminar la intencion
	    {
		   intents.erase(intents.begin()+i);//elimanar la intencion
		   deleted=true;
		}
   }
   return deleted;
}


bool Chatbot::addExample(string name)
{

    bool added=false;
	if(name==""){
		cout<<"Intent name: ";
		getline(cin,name);
	}

	int i=searchIntent(name);


   if(i==-1)//seria cierta en caso de que ninguna intencion coincida con el numbre
   {
      Util::error(ERR_INTENT);
   }
   else//en caso de que la intencion exista
   {
	   while(1)//bucle que seguira pidiendo examples para un intent
	   {
			string exampleText="";
			cout<<"New example: ";
			getline(cin,exampleText);

			if(exampleText=="q"){
				break;//salimos del bucle que lee ejemplos y volvemos al menu de train
			}
				try{
				   Example newExample(exampleText);//creamos un nuevo ejemplo para guardar el texto introducido
				   intents[i]->addExample(newExample);//añadimos el example a la intencion adecuada
				   added=true;
				}catch(Error e){
					Util::error(e);
				}


	   }
   }
   return added;
}


bool Chatbot::deleteExample(int id){

	bool deleted=false;
	if(id==0){
		cout<<"Example id: ";
		cin>>id;
	}

	unsigned int intentSize=intents.size();//almacenara el nº de las intenciones
	int pos=-1;
	int i;

	for(i=0;(unsigned)i<intentSize;i++)
	{
	   unsigned int exampleSize=intents[i]->getNumExamples();//almacena nª de los ejemplos

	   for(int j=0;(unsigned)j<exampleSize;j++)
	   {
		   if(intents[i]->getExamples()[j].getId()==id)
		   {
		       pos=j;
		       break;
		   }
	   }

	   if(pos!=-1)//si el ejemplo existe se borra
	   {
		    //intents[i]->getExamples().erase(intents[i]->getExamples().begin()+pos);
		    intents[i]->deleteExample(id);
		    deleted=true;
     		break;
	   }
	}
	if(pos==-1)//si el ejemplo no existe
	{
	   Util::error(ERR_EXAMPLE);
    }

    return deleted;
}



bool Chatbot::addResponse(string name,string response)
{
	   bool added=false;
	   if(name==""){
			cout<<"Intent name: ";
			getline(cin,name);
		}

	   int i=searchIntent(name);
	   if(i==-1)//seria cierta en caso de que ninguna intencion coincida con el numbre
	   {
	      Util::error(ERR_INTENT);
	   }
	   else
	   {
		    if(response=="")
		    {
		       cout<<"New response: ";
		       getline(cin,response);
		    }

		    intents[i]->addResponse(response);
		    added=true;
	   }
	   return added;
}


string Chatbot::bestResponse(string query,bool debug) const{

	float CJmax=0;
    string bestresponse="";
	for(unsigned i=0;i<intents.size();i++){
		float CJ=intents[i]->calculateSimilarity(query,similarity);
		if(CJ>CJmax){
			CJmax=CJ;
			bestresponse=intents[i]->getResponse();
		}
	}

	if(CJmax<threshold){
		throw ERR_RESPONSE;
	}
	else{

		if(debug==true){

			stringstream ss;
			string s;
			ss<<CJmax;
		    s=ss.str();
			bestresponse="("+s+") "+bestresponse;
		}
		 return bestresponse;
	}
}


void Chatbot::test(bool debug) const{
	    cout << ">> " << Util::welcome()<< endl;
	    string pregunta;
	    while(1)
	    {
			cout<<"<< ";
			getline(cin,pregunta);

			if(pregunta=="q") break;//salir del bucle while(1)

			try{
				 string respuesta=bestResponse(pregunta,debug);
				 cout<<">> "<<respuesta<<endl;
			}
			catch(Error e){
				Util::error(e);
			}
	    }
}


void Chatbot::configure(float threshold,const char similarity[])
{
	if(threshold==-1){
	cout<<"Enter threshold: ";
	cin>>threshold;
	cin.get();
	}
	if(threshold>=0 && threshold<=1)
	  this->threshold=threshold;
	else
	   Util::error(ERR_THRESHOLD);

	string algoritmo=similarity;
	if(algoritmo==""){
	cout<<"Enter algorithm: ";
	getline(cin,algoritmo);
	}

	if(algoritmo=="jc" || algoritmo=="ng")
	 strcpy(this->similarity,algoritmo.c_str());
	else
	  Util::error(ERR_SIMILARITY);
}


ostream& operator<<(ostream &os,const Chatbot &ch){

	char jc[3];
	strcpy(jc,"jc");
	char ng[3];
	strcpy(ng,"ng");
    int contExamples=0;
    os<<"Similarity: ";
    if(strcmp(ch.similarity,jc)==0)
      os<<"Jaccard\n";
    else if(strcmp(ch.similarity,ng)==0)
      cout<<"N-grams\n";
    os<<"Threshold: "<<ch.threshold<<endl;

    for(int i=0;(unsigned)i<ch.intents.size();i++)
    {
      os<<*(ch.intents[i])<<endl;
      contExamples=contExamples+ch.intents[i]->getNumExamples();
	}

    os<<"Total intents: "<<ch.intents.size()<<endl;
    os<<"Total examples: "<<contExamples<<endl;

    float media=0.0;
    if(contExamples!=0) //para no dividir entre 0
      media=(float)contExamples/(float)ch.intents.size();

    os<<"Examples per intent: "<<media;

    return os;
}
