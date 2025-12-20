/*Álvaro Martínez García, 48150407E
ADA. 2021-22
Práctica 6.1: Encaminamiento óptimo
*/






//Por motivos personales no he podido resolver la práctica a tiempo este fin de semana, solo tenía la gestión de opciones








#include<iostream>
#include<fstream>
#include<vector>
#include<string.h>
#include<sstream>
#include<limits>

using namespace std;

bool fArg=false;
bool tArg=false;
bool ignoreArg=false;
string filename="";
int n;
int m;
vector<int> almacenamientos;                //ci
vector<double> distancias;                  //di
    //Podrían ser punteros de tamaño [m]
string usageError= "Usage: \nmet [-t] [--ignore-naive] -f file\n";


void ogw(int k, int n, vector<int> &trace){         //Devuelve el tráfico estimado mínimo y el índice del nodo que se debe colocar de puerta de enlace, esto sería la parte no recursiva que comprueba las n posibilidades



}

int met_naive(const vector<int> &almacenamiento, const int n){        //Función sin hacer, solo se han probado cosas

    if(n == 0)
        return 0;

    int q = numeric_limits<int>::max();
    for(int i=1; i<=1; i++){
        q=min(q, almacenamiento[i] + met_naive(almacenamiento, n-i));
    }

    return q;

}
void met_memo(){




}
//void met_it_matrix(){}
//void met_it_vector(){}
//void met_parser(){}

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
        
        do{
            strSeparator=line.substr(0,line.find(' '));
            int number=stoi(strSeparator);
            almacenamientos.push_back(number);
            line.erase(0,(number/10+1)+1);
        }while(line.size()>0);

        getline(file,line);
        do{
            strSeparator=line.substr(0,line.find(' '));
            double number=stod(strSeparator);
            distancias.push_back(number);
            if(strSeparator.find('.') != string::npos)
                line.erase(0,(number/10+1)+3);
            else
                line.erase(0,(number/10+1)+1);
        }while(line.size()>0);

        file.close();
    }else{
        cerr << "ERROR: can't open file: " << filename << "." << endl << usageError;
        exit (EXIT_FAILURE);
    }

}

bool checkArgs(const int& argc, char* argv[]){

    for(int i=1;i<argc;i++){
        if(strcmp("-t",argv[i])==0){
            tArg=true;
        }else if(strcmp("--ignore-naive",argv[i])==0){
            ignoreArg=true;
        }else if(strcmp("-f",argv[i])==0){
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


        readFile();

        vector<int> trace(n);
        if(!ignoreArg){
            int num=met_naive(almacenamientos,n);
            
            cout << num << " ";
        }
        else{
            cout << "- ";
        }


        met_memo();
        cout << 0 << " ";

        cout << "? ?" << endl;          //Soluciones de las otras dos funciones

        cout << "?" << endl;            //Vector de nodos
        cout << "?" << endl;            //Solución
        if(tArg){
            cout << "Memoization matrix:" << endl << "0" << endl;  //Matriz de memoización, necesario para esta entrega

            cout << "Iterative matrix:" << endl << "?" << endl;
        }

    }
    else{
        cerr << "Missing argument -f and the file" << endl << usageError;
    }



    return 0;
}