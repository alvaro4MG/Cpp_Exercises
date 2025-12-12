
#include "../include/tvectorporo.h"

TVectorPoro::TVectorPoro(){             //Constructor por defecto
    dimension=0;
    datos=NULL;
}

TVectorPoro::TVectorPoro(int a){        //Constructor con la dimensión como argumento
    if(a>0){
        dimension=a;
        datos= new TPoro[a];            //Reservamos memoria para tantos poros como a
        if (!datos){
            cerr << "ERROR: no se pudo reservar memoria" << endl;
            exit (EXIT_FAILURE);  
        }
    }else{
        dimension=0;
        datos=new TPoro[0];
    }
}

TVectorPoro::TVectorPoro(const TVectorPoro &orig){            //Constructor de copia
    dimension=orig.dimension;
    if(orig.datos!=NULL){
        datos=new TPoro[orig.dimension];                //Reservamos tanta memoria como la dimensión del poro a copiar e introduciremos los poros de uno en uno (siempre que hayan, sino el puntero apuntará a NULL)
        //bucle para cada uno
        for(int i=0;i<dimension;i++)
            datos[i]=orig.datos[i];
    }else{datos=NULL;}
}

TVectorPoro::~TVectorPoro(){            //Destructor/liberador
    dimension=0;
    if(datos != NULL){
        delete[] datos;                     //Utilizamos el delete con corchetes porque es un tipo definido por nosotros, llamará a cada destructor
        datos=NULL;
    }
}

TVectorPoro& TVectorPoro::operator=(const TVectorPoro &op2){            //Operador de asignación
    if(this != &op2){
        (*this).~TVectorPoro();                             //Como en el TPoro, comprobamos que sean distintos, liberamos la memoria del actual y copiamos (igual que el constructor de copia) el segundo operador
        dimension=op2.dimension;
        if(op2.datos!=NULL){
            datos=new TPoro[op2.dimension];
            for(int i=0;i<dimension;i++)
                datos[i]=op2.datos[i];
        }else{datos=NULL;}
    }
    return *this;
}

bool TVectorPoro::operator==(const TVectorPoro &op2){       //Operador de igualdad
    if(datos!=NULL && op2.datos!=NULL){                     //Si cualquiera de los datos es NULL o las dimensiones son disitntas, devolverá false
        if( (dimension==op2.dimension) ){
            for(int i=0;i<dimension;i++)
                if(datos[i]!=op2.datos[i])                  //Comprueba uno a uno si son distintos. Si lo son, se devolverá false (no son iguales)
                    return false;
            return true;
        }
        else
            return false;
    }else
        return false;
    
}

bool TVectorPoro::operator!=(const TVectorPoro &op2){       //Operador de desigualdad, contrario al de igualdad
    return !((*this)== op2 );
}

TPoro& TVectorPoro::operator[](int pos){        //Sobrecarga de los corchetes en el lado izquierdo. Nos interesa referencia porque nos interesa esa zona de memoria en concreto para modificarla
    //se puede decidir el orden de los indices, para el usuario es mejor 1-10 que 0-9, por lo que utilizará esos índices en el programa principal
    if( pos>0 && pos<=dimension)
        return datos[pos-1];
    else
        return error;       //devolvemos el TPoro error para que el programa no me aborte, el TPoro que le estemos asignando se guarda en ese error igual
}

TPoro TVectorPoro::operator[](int pos) const {            //Sobrecarga de los corchetes en el lado derecho. Ponemos el const porque en la parte derecha no se modifica                                           
    if( pos>0 && pos<=dimension)
        return datos[pos-1];                        //devuelve por valor, por lo que se llamará al constructor de copia por su cuenta
    else
        return error;
}

int TVectorPoro::Cantidad() const{          //Devuelve los poros del vector que no están vacíos
    int counter=0;
    for(int i=0;i<dimension;i++)
        if( !(datos[i].EsVacio()) )         //Aumentará el contador únicamente si no están vacíos
            counter++;
    return counter;
}

bool TVectorPoro::Redimensionar(int nueva){              //Método para redimensionar el vector según la dimensión pasada como argumento
    
    if(nueva<=0){
        return false;
    }
    else if(nueva==dimension){                      //Si la nueva dimensión es menor o igual que 0 o es la misma que la actual, devuelve false porque se queda con la dimensión actual
        return false;
    }

    TPoro *nuevosDatos= new TPoro[nueva];                                     //Se crea uno nuevo donde guardar los poros del vector que quepan y sustituirá al datos actual              
                                                                //Una vez vemos que la dimensión es correcta, reservamos memoria para nuevosDatos según la nueva dimensión
    
    if(nueva>dimension){
        
        for(int i=0;i<nueva;i++){
            if(i<dimension){
                nuevosDatos[i]=datos[i];
            }
            else{                                   //En caso de que la nueva dimensión sea mayor que la actual, los poros restantes serńa poros vacíos
                nuevosDatos[i]= TPoro();
            }
        }
        (*this).~TVectorPoro();
        datos=nuevosDatos;                          //Al terminar, asignaremos nuevosDatos al datos del vector
        dimension=nueva;
        
        return true;
    }
    else{
        
        for(int i=0;i<nueva;i++){
            nuevosDatos[i]=datos[i];
        }
        (*this).~TVectorPoro();
        datos=nuevosDatos;
        dimension=nueva;

        return true;
    }
}

ostream& operator<<(ostream &os, const TVectorPoro &vector){

    if(vector.dimension!=0){
        os<<"[";
        for(int i=0;i<vector.dimension;i++){
            os<< i+1 << " " << vector.datos[i];
            if(!( (i+1)==vector.dimension ) )
                os<<" ";
        }
        os<<"]";
    }
    else
        os << "[]";
    
    return os;

}