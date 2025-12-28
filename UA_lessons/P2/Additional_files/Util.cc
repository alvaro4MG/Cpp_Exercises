//Abderrahmane Guermat Benaouali 51771088C
#include "Util.h"

using namespace std;
string cleanString(string);
const int KSIZE=10;

const string greetings[KSIZE]={
  "Hola, ¿en qué puedo ayudarte?",
  "¿Qué puedo hacer hoy por ti?",
  "Oh, gran prócer de los bits, ¿cuál es tu deseo?",
  "Buenas",
  "¿Qué quieres?",
  "¿Otra vez necesitas ayuda?",
  "¡Hola! Soy Megabot 3000. ¿En qué puedo ayudarte?",
  "Bonito día para ser Megabot 3000",
  "Pregunta sin miedo",
  "Soy todo oídos"
};

void Util::error(Error e){
  switch(e){
    case ERR_OPTION:
      cout << "ERROR: wrong menu option" << endl;
      break;
    case ERR_INTENT:
      cout << "ERROR: wrong intent name" << endl;
      break;
    case ERR_EXAMPLE:
      cout << "ERROR: wrong example id" << endl;
      break;
    case ERR_RESPONSE:
      cout << "Lo siento, pero no tengo respuesta para eso" << endl;
      break;
    case ERR_FILE:
      cout << "ERROR: cannot open file" << endl;
      break;
    case ERR_THRESHOLD:
      cout << "ERROR: the threshold value must be between 0 and 1" << endl;
      break;
    case ERR_SIMILARITY:
      cout << "ERROR: valid values are \"jc\" (Jaccard) and \"ng\" (n-grams)" << endl;
      break;
    case ERR_EMPTY:
      cout << "ERROR: empty strings are not permited" << endl;
      break;
    case ERR_MAXEXAMPLES:
      cout << "ERROR: cannot add more examples" << endl;
  }
}

string Util::welcome(){
	int position=rand()%KSIZE;
	string saludo=greetings[position];
	return saludo;
}

/**
 * eliminara caracteres no alfanumericos,pasa de mayusculas 
 * a minusculas y elimina s final de palabra y espacios de mas
 */
void Util::normaliza(string &cleanText)
{
	int size=cleanText.length();
	
	//bucle para borrar carracteres no alfanumericos
	for(int i=0;i<size;i++)
	{
	   char c=cleanText[i];
	   cleanText[i]=tolower(c);
	   if(isalnum(cleanText[i])==false && cleanText[i]!=' '  && cleanText[i]!='\0')
	   {     
			  cleanText.erase(cleanText.begin()+i);   
			  i--;	
	   }
	}
	
	//bucle para borrar s final
	size=cleanText.length();
	for(int i=0;i<size;i++)
	{  
	   if(cleanText[i]=='s' && isalnum(cleanText[i+1])==false)
	   {     
			  cleanText.erase(cleanText.begin()+i);   
			  i--;	
	   }
	}
	
	//bucle para borrar espacios de mas
	size=cleanText.length();
	for(int i=0;i<size;i++)   
	{	
	   if((cleanText[i]==' ' && cleanText[i+1]==' ' )|| (cleanText[i]==' ' && cleanText[i+1]=='\0'))
	   {   
			  cleanText.erase(cleanText.begin()+i);   
			  i--;
	   }
	}
}


vector<string> Util::extractTokens(string text){
	
	vector<string> tokens;
					
	string cleanText = cleanString(text);
    normaliza(cleanText);
	
	
	if(cleanText!="")//ver si cadena normalizada esta vacia
	{
			stringstream ss(cleanText);
			string s;
			while(ss>>s)
			{
			  if(s!=" ")
				 tokens.push_back(s);//añadimos la palabra al token
			}
	}
	
	
	return tokens;
}



