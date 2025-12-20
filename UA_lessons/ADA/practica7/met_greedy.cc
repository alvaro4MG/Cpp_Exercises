/*Álvaro Martínez García, 48150407E
ADA. 2021-22
Práctica 7: Encaminamiento óptimo II
*/

#include<iostream>
#include<fstream>
#include<vector>
#include<string.h>
#include<sstream>
#include<limits>
#include<algorithm>

using namespace std;

bool fArg=false;
string filename="";
unsigned n;
unsigned m;
vector<int> almacenamientos;                            //ci
vector<vector<double>> distancias;                      //di
string usageError= "Usage: \nmet_greedy -f file\n";


double selectMinimum(int nodo, vector<unsigned> &indexes){      //Para seleccionar el camino más corto entre los nodos
    double minimum=distancias[nodo][indexes[n-1]];

    for(unsigned i=2; i<(m+1); i++){
        if(distancias[nodo][indexes[n-i]] < minimum)            //Comprueba los caminos hacia los nodos que haya (los m índices al final de indexes) y almacena el mínimo
            minimum=distancias[nodo][indexes[n-i]];

    }

    return minimum;
}

double met_greedy_1(){        //Usar como nodos los m con mayor capacidad

    //Ordenar el vector de tamaños indicando sus posiciones de menor a mayor en un vector de los índices
    vector<unsigned> indexes(n);
    for(unsigned i=0; i<n ; i++)
        indexes[i]=i;

    sort(indexes.begin(),indexes.end(), [&](unsigned x, unsigned y){
        return almacenamientos[x] < almacenamientos[y];
        }
    );
    

    //calcular el tráfico
    double trafico=0;

    for(unsigned i=0; i<(n-m); i++){
        trafico+=(almacenamientos[indexes[i]]*selectMinimum(indexes[i],indexes));
    }

    return trafico;

}

unsigned changeTrace(unsigned nodo, const vector<unsigned> &trace){     //Busca en la traza el índice con menor camino para sustituirlo
    double minimum=numeric_limits<double>::max();
    unsigned i, index=0;

    for(i=0;i<n;i++){
        if(i!=nodo && trace[i]==i && (distancias[nodo][i] < minimum)){         //Solo se aceptará si es distinto del nodo que estamos descartando y si se encuentra en la traza como nodo
            minimum=distancias[nodo][i];
            index=i;
        }
    }

    return index;
}

double traficoEstNodo(unsigned nodo, vector<unsigned> trace){           //Calcular tráfico si descartamos como nodo
    double trafico=0;

    trace[nodo]=changeTrace(nodo,trace);                                //Se cambia en la traza para que su camino sea el menor     

    for(unsigned i=0; i<n ; i++){
        if(trace[i]!=i)
            trafico+=(almacenamientos[i]*distancias[i][trace[i]]);      //Calculamos el tráfico para la nueva traza sin este nodo
    }

    return trafico;
}

double met_greedy_2(vector<unsigned> &trace){       //Todos son nodos y vamos descartando los que generen menos tráfico porque supondrían un menor problema

    for(unsigned i=0; i< (n-m); i++){                               //Bucle for tantas veces como nodos tengamos que descartar (n-m)
        vector<double> traffic;

        for(unsigned j=0; j<n; j++){                                //Hacemos un bucle para obtener el tráfico que se genera haciendo que cada nodo por separado ya no sea un nodo
            if(trace[j]==j)                                             //Solo se calculará si es un nodo, es decir, su posición en trace tiene su mismo valor, sino será 0 para poder descartarlo
                traffic.push_back(traficoEstNodo(j,trace) );
            else
                traffic.push_back(0);
        }
        /*for(unsigned k=0;k< traffic.size();k++){  //Vector para comprobar cómo varía el tráfico para las pruebas
            cout << traffic[k] << " ";
        }
        cout << endl;*/

        //cambiar el trace del nodo con menor tráfico
        unsigned index,k;
        double minimum=numeric_limits<double>::max();
        for( k=0;k<traffic.size();k++){                     //Comprobamos qué tráfico del vector traffic es menor para cambiar ese nodo
            if(traffic[k]!=0 && traffic[k] < minimum){
                minimum=traffic[k];
                index=k;
            }
        }
        for(unsigned k=0;k<n;k++){        
            if(trace[k]==index)                         //Buscamos el índice en el vector trace y lo sustituiremos por el nodo con menor camino
                trace[k]=changeTrace(index,trace);
        }
        
        /*for(unsigned k=0;k<n;k++){          //Vector para comprobar cómo varía la traza para las pruebas
            cout << trace[k] << " ";
        }
        cout << endl;*/
        traffic.clear();
    }


    double trafico=0;       
    for(unsigned i=0; i<n; i++){                //Alterminar calculamos el tráfico con la traza obtenida
        if(trace[i]!=i)
            trafico+=(almacenamientos[i]*distancias[i][trace[i]]);
    }

    return trafico;

}

void readFile(){
    ifstream file;
    file.open(filename);

    if(file.is_open()){
        string line, strSeparator;
        stringstream lineRead;

        getline(file,line);
        lineRead<<line;
        lineRead >> n >> m;

        getline(file,line);
        unsigned i=0;
        
        do{
            strSeparator=line.substr(0,line.find(' '));
            int number=stoi(strSeparator);
            i++;
            almacenamientos.push_back(number);
            line.erase(0,line.find(' ')+1);
        }while(i<n);

        while(getline(file,line)){
            if(line!=""){
                vector<double> fila;
                i=0;
                do{
                    strSeparator=line.substr(0,line.find(' '));
                    double number=stod(strSeparator);
                    fila.push_back(number);
                    i++;
                    line.erase(0,line.find(' ')+1);
                }while(i<n);
                
                distancias.push_back(fila);
            }
        }

        file.close();
    }else{
        cerr << "ERROR: can't open file: " << filename << "." << endl << usageError;
        exit (EXIT_FAILURE);
    }

}

bool checkArgs(const int& argc, char* argv[]){

    for(int i=1;i<argc;i++){
        if(strcmp("-f",argv[i])==0){
            if(argc>(i+1)){
                fArg=true;
                filename=argv[i+1];
                i++;
            }else{
                cerr << "ERROR: missing filename." << endl << usageError;
                exit (EXIT_FAILURE);
            }
        }else{
            cerr << "ERROR: unknown option " << argv[i] << "." << endl << usageError;
            return false;
        }
    }
    
    return true;
}

int main(int argc, char* argv[]){
    ifstream file;


    if(argc>1){
        if(!checkArgs(argc,argv)){
            exit (EXIT_FAILURE);
        }
    }else{
        cout << usageError;
        exit (EXIT_FAILURE);
    }

    if(fArg){

        readFile();                                 //Se lee el fichero de entrada
        
        cout << met_greedy_1() << " ";              //Lamada a met_greedy_1 para obtener el tráfico que se genera con ese criterio
        
        //Creamos trace para el met_greedy_2
        vector<unsigned> trace(n);
        for(unsigned i=0; i<n ; i++)
            trace[i]=i;

        cout << met_greedy_2(trace) << endl;        //Lamada a met_greedy_1 para obtener el tráfico que se genera con ese criterio

        //Tabla de encaminamiento
        for(unsigned k=0;k<n;k++){
            cout << trace[k] << " ";
        }
        cout << endl;

        //Tráfico de tabla de encaminamiento
        double trafico=0;
        for(unsigned i=0; i<n; i++){
            trafico+=(almacenamientos[i]*distancias[i][trace[i]]);
        }
        cout << trafico << endl;            //Solución según tabla de encaminamiento
        

    }
    else{
        cerr << "Missing argument -f and the file" << endl << usageError;
    }



    return 0;
}