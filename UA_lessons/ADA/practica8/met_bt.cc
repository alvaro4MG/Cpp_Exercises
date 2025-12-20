/*Álvaro Martínez García, 48150407E
ADA. 2021-22
Práctica 8: Encaminamiento óptimo III
*/

#include<iostream>
#include<fstream>
#include<vector>
#include<string.h>
#include<sstream>
#include<limits>
#include<algorithm>
#include <chrono>
#include<tuple>
#include<iomanip>

using namespace std;

bool fArg=false;
string filename="";
unsigned n;
unsigned m;
vector<unsigned> almacenamientos;                           //ci
vector<vector<double>> distancias;                          //di
string usageError= "Usage: \nmet_greedy -f file\n";
unsigned visited_leaf_nodes, visited_nodes, explored_nodes, no_promising_discarded_nodes, no_feasible_discarded_nodes;


//met_gregedy_1
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

//met_greedy_2
unsigned changeTrace(unsigned nodo, const vector<unsigned> &trace, const vector<unsigned> &binSol){     //Busca en la traza el índice con menor camino para sustituirlo
    double minimum=numeric_limits<double>::max();
    unsigned i, index=0;

    for(i=0;i<n;i++){
        if(i!=nodo && binSol[i]==1 && (distancias[nodo][i] < minimum)){         //Solo se aceptará si es distinto del nodo que estamos descartando y si se encuentra en la traza como nodo
            minimum=distancias[nodo][i];
            index=i;
        }
    }

    return index;
}

/*double traficoEstNodo(unsigned nodo, vector<unsigned> trace){           //Calcular tráfico si descartamos como nodo
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
        for(unsigned k=0;k< traffic.size();k++){  //Vector para comprobar cómo varía el tráfico para las pruebas
            cout << traffic[k] << " ";
        }
        cout << endl;

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
        
        for(unsigned k=0;k<n;k++){          //Vector para comprobar cómo varía la traza para las pruebas
            cout << trace[k] << " ";
        }
        cout << endl;
        traffic.clear();
    }


    double trafico=0;       
    for(unsigned i=0; i<n; i++){                //Alterminar calculamos el tráfico con la traza obtenida
        if(trace[i]!=i)
            trafico+=(almacenamientos[i]*distancias[i][trace[i]]);
    }

    return trafico;

}*/

//met_bt
double traffic(const vector<unsigned> &trace){          //Método para obtener el tráfico basado en la traza de índices
    double acc_t=0.0;
    for(unsigned i=0; i<n; i++){
        acc_t+=almacenamientos[i]*distancias[i][trace[i]];
    }

    return acc_t;

}

int isSolutionFunction(const vector<unsigned> &binSol){     //Este método devuelve el números de puertas de enlace que faltan o un valor negativo si hay demasiadas
    bool counterValid=true;
    unsigned counter=0;

    for(unsigned i=0; (i<n) && counterValid; i++){
        if(binSol[i]==1){
            counter++;
            if(counter>m){
                counterValid=false;
            }
        }
    }

    if(!counterValid){
        return -1;
    }else{
        return (m-counter);
    }
}

double add_rest(vector<unsigned> &trace, unsigned k){           //Método de prueba de las diapositivas, no aplicable a este problema
    double r=0.0;
    for(unsigned i = k; i<n; i++){
        r+=distancias[i][trace[i]];
    }
    return r;
}

void met_bt(unsigned k, vector<unsigned> &trace, double &bestVoraz, vector<unsigned> &sol, vector<unsigned> &binSol){
    bool isPromising=true, isFeasible=true;;

    //Podemos ordenar los valores previamente


    int isSolution = isSolutionFunction(binSol);                //Obtenemos 


    //Mirar si es hoja, calcular su tráfico y hacer el mínimo (si cambia, hay que seleccionarlo como solución)
        //EST: si es hoja, aumentar visited_leaf_nodes
    if(isSolution==0 ){                             //además de esto, que es una condición segura de hoja, comprobar que sea factible (se comprueba antes)
        visited_leaf_nodes++;
        double actual_t=traffic(trace);
        if(actual_t<=bestVoraz){
            bestVoraz=actual_t;
            sol=trace;
        }
    }else if(k<n){
        

    //Si no es hoja, expandimos, bajando la k un nivel (mirar antes si la solución sería factible)
        //Se le puede sumar el tráfico conforme bajamos? y así si pasa del mínimo no lo explora, además se puede guardar esta cota optimista y no calcular si cambiamos a 1
        if((n-k) >= isSolution){
            for(int i=1; i>-1 ;i--){
                visited_nodes++;
                //cambiar en la traza por 0 o 1
            //if((n-k) >= isSolution){
                
                if(i==1){
                    //if(isSolution==1)
                        binSol[k]=i;
                        trace[k]=k;
                    for(unsigned j=0; j<n && isPromising; j++){       //o se comprueban todos?
                        if(binSol[j]==0){
                            trace[j]=changeTrace(j,trace,binSol);          //Hacerlo con todos a partir de 0, por si había previos que no eran puerta de enlace y tienen que cambiar su traza
                        }else{
                            trace[j]=j;
                        }
                        
                    }
                    //if((isSolution)==1 && traffic(trace)>bestVoraz)           //No me funciona y no tengo claro por qué, aunque esto no ahorra nada ya que en la siguiente iteración ya se comprobaría y compararía
                        //isPromising=false;
                    
                }else{
                    binSol[k]=i;
                    /*if(isSolution<m){

                        for(unsigned j=k; j<n && isPromising; j++){
                            trace[j]=changeTrace(j,trace,binSol);          //Hacerlo con todos a partir de k
                            if(traffic(trace)>bestVoraz){
                                //isPromising=false;
                            }
                        }
                    }*/
                    //if(traffic(trace)>bestVoraz)
                        //isPromising=false;
                }
                
                
                if(isFeasible){
                    if(isPromising){
                        explored_nodes++;
                        met_bt(k+1,trace,bestVoraz,sol,binSol);            //Expandimos
                    }else{
                        no_promising_discarded_nodes++;
                    }
                }else{
                    no_feasible_discarded_nodes++;
                }
            }/*else{
                no_feasible_discarded_nodes++;
            }*/
        //}
        }else{
            no_feasible_discarded_nodes++;
        }
    }


}

double met_bt(double &bestVoraz, vector<unsigned> &trace, vector<unsigned> &sol, vector<unsigned> &binSol){
    double present_best = bestVoraz;            //este valor variará al mejor valor del tráfico posible
    met_bt(0,trace,present_best,sol,binSol);
    return present_best;
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

        visited_leaf_nodes=0;
        visited_nodes=0;
        explored_nodes=0;
        no_promising_discarded_nodes=0;
        no_feasible_discarded_nodes=0;
        
        auto start = clock();                       //Empieza aquí a cronometrar, antes del voraz (cuenta como preparación de datos)
        //cout << met_greedy_1() << " ";              //Lamada a met_greedy_1 para obtener el tráfico que se genera con ese criterio,ESTABLECER COMO MÍNIMO DE MOMENTO
        double bestVoraz=met_greedy_1();
        //cout << bestVoraz << endl;

        


        //Creamos trace
        vector<unsigned> trace(n), sol(n),binSol(n);        //Creamos los vectores para la traza, la traza con solución y la traza de 1s y 0s (donde 1 significa que el nodo de ese índice es una puerta de enlace)
        for(unsigned i=0; i<n ; i++){
            trace[i]=0;
            sol[i]=0;
            binSol[i]=0;
        }

        
        double bestTraffic=met_bt(bestVoraz,trace,sol,binSol);      //Aplicamos el backtracking
        auto end = clock();
        double time=(1000.0 * (end-start) / CLOCKS_PER_SEC) / 30; 
        cout << fixed  << setprecision(2) << bestTraffic << endl;


        //Mostramos los nodos que resulten puerta de enlace
        unsigned counterGW=0;
        for(unsigned i=0; i<n; i++){
            if(sol[i] == i){
                cout << i;
                counterGW++;
                if(counterGW<m){
                    cout << " ";
                }
            }
        }
        cout << endl;




        //Estadística de los nodos (5 valores)
        cout << visited_nodes << " " << explored_nodes << " " << visited_leaf_nodes << " " << no_feasible_discarded_nodes << " " << no_promising_discarded_nodes << endl;



        //Tiempo en CPU
        cout << time << endl;
        

    }
    else{
        cerr << "Missing argument -f and the file" << endl << usageError;
    }



    return 0;
}