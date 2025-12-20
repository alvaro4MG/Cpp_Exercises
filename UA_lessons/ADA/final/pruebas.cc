#include<iostream>
#include<vector>
#include<limits>
#include<string.h>
#include<fstream>
#include<sstream>

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

int ogw(){



}

int trace_tube_cut(const vector<int> &p, const int n, vector<int> &trace){

    if( n == 0){                //Si esto es igual al nodo m
        trace[n]=0;
        return 0;
    }

    int q=numeric_limits<int>::max();            //q podría ser -1 porque igualmente siempre es mayor que 0
    for(int i=1;i<=n;i++){
        int aux = p[i] + trace_tube_cut(p, n-i, trace);
        if(aux<q){
            q=aux;
            trace[n]=i;
        }
    }

    return q;


}

vector<int> trace_tube_cut(const vector<int> &p, const int n){
    vector<int> trace(n+1);
    trace_tube_cut(p,n,trace);
    return trace;
}

vector<int> parse(const vector<int> &trace,int n){
    //vector<int> trace= trace_tube_cut(price, n)
    vector<int> sol(trace.size(),0);

    int l=trace.size()-1;
    while(l !=0){
        sol[trace[l]]++;
        l-=trace[l];
    }

    return sol;
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

        //vector<int> trace(n);
        if(!ignoreArg){
            vector<int> trace= trace_tube_cut(almacenamientos,n);
            vector<int> sol= parse(trace,n);

            for(int i=0;i<sol.size(); i++){
                if(sol[i] !=0)
                    cout << sol[i] << " cuts of length " << i << endl; 
            }
            
            //cout << num << " ";
        }
        else{
            cout << "- ";
        }

        vector<vector<double>> matriz;

        matriz.push_back(vector<double>());
        matriz[0].push_back(2);

        /*
        met_memo();
        cout << 0 << " ";

        cout << "? ?" << endl;          //Soluciones de las otras dos funciones

        cout << "?" << endl;            //Lista de nodos
        cout << "?" << endl;            //Solución
        if(tArg){
            cout << "Memoization matrix:" << endl << "0" << endl;  //Matriz de memoización, necesario para esta entrega

            cout << "Iterative matrix:" << endl << "?" << endl;
        }*/

    }
    else{
        cerr << "Missing argument -f and the file" << endl << usageError;
    }



    return 0;
}

/*
int main(){

    vector<int> price={1,5,8,9,10,17,17,20,24,27};
    int n=10;

    //cout << price[0] << endl;

    vector<int>trace = trace_tube_cut(price,n);

    vector<int> sol= parse(trace,n);

    for(int i=0;i<sol.size(); i++){
        if(sol[i] !=0)
            cout << sol[i] << " cuts of length " << i << endl; 
    }

    return 0;
}*/