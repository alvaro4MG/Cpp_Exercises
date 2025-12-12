
#include "../include/tabbporo.h"


TNodoABB::TNodoABB(): item(), iz(), de(){
    //Ya están todos los constructores, no hace falta hacer más
}

TNodoABB::TNodoABB(const TNodoABB &orig)    :       //los : son el inicializador de objetos (cuando hay layering)
    item(orig.item), iz(orig.iz), de(orig.de){
}

TNodoABB::~TNodoABB(){
    //Vacio porque hay una composición que invoca a sus destructores y no hay más variables que tengamos que borrar
}

TNodoABB& TNodoABB::operator=(const TNodoABB &op2){     

    if(this!=&op2){
        (*this).~TNodoABB();
        item=op2.item;
        iz=op2.iz;
        de=op2.de;
    }
    return *this;
}






TABBPoro::TABBPoro(){
    nodo=NULL;
}

void TABBPoro::Copiar(const TABBPoro &orig){
    if(!orig.EsVacio()){
        nodo= new TNodoABB();
        nodo->item=orig.nodo->item;
        nodo->iz.Copiar(orig.nodo->iz);
        nodo->de.Copiar(orig.nodo->de);
    }
    else
        nodo=NULL;
}

TABBPoro::TABBPoro(const TABBPoro &orig){
    
    if(orig.nodo!=NULL){
        TNodoABB *aux=new TNodoABB();           //Se hace un puntero y tiene todo a NULL
        aux->item=orig.nodo->item;
        nodo=aux;                               //Nuestro nuevo nodo es aux
        nodo->iz.Copiar(orig.nodo->iz);         //Se harán llamadas recursivas
        nodo->de.Copiar(orig.nodo->de);
    }else{
        nodo=NULL;
    }

}

TABBPoro::~TABBPoro(){
    TNodoABB *aux= new TNodoABB();

    if(nodo!=NULL){
        aux=nodo;
        nodo->iz.~TABBPoro();               //Borramos izquierda y derecha antes de borrar el nodo
        nodo->de.~TABBPoro();

        delete nodo;                        //Llama a todos los destructores del nodo, tanto del item como de los dos hijos (los hijos llamaarían a este destructor porque son también ABB)
        nodo=NULL;
    }
}

TABBPoro& TABBPoro::operator=(const TABBPoro &op2){

    if(! (this == &op2)){
        this->~TABBPoro();
        this->Copiar(op2);
    }
    return *this;
}

bool TABBPoro::operator==(const TABBPoro &op2) const{           //Esto es según elementos, da igual la estructura

    if(!EsVacio() && !op2.EsVacio()){
        return (Inorden() == op2.Inorden());
    }else if(EsVacio() && op2.EsVacio()){
        return true;
    }

    return false;
}

TABBPoro TABBPoro::operator+(const TABBPoro &op2){              //No modifica a this, no devuelve por referencia, CAMBIARLO

    //Simplemente insertar los de op2 si no se encuentran en el primero
    //TVectorPoro vectorporo1= Niveles();
    //TVectorPoro vectorporo2= op2.Inorden();
    TABBPoro result(*this);     //Copia del operador 1 que modificaremos con operador2
    TABBPoro deleter(op2);
    
    TVectorPoro listaPoros=deleter.Inorden();

    for(int i=1 ; i<=listaPoros.Cantidad() ; i++){
        result.Insertar(listaPoros[i]);
    }
    

    return result;
}

TABBPoro TABBPoro::operator-(const TABBPoro &op2){

    TABBPoro result;
    TVectorPoro listaPoros=Inorden();

    for(int i=1 ; i<=listaPoros.Cantidad() ; i++){
        TPoro copia=listaPoros[i];

        if(!op2.Buscar(copia))
            result.Insertar(copia);
    }


    return result;
}

bool TABBPoro::Insertar(const TPoro &nuevo){            //Ordenados según volumen, de menor a mayor, no se puede repetir volumen

    if(!EsVacio()){
        if(!Buscar(nuevo)){
            if(nodo->item>nuevo){
                return nodo->iz.Insertar(nuevo);
            }else if(nodo->item<nuevo){
                return nodo->de.Insertar(nuevo);
            }
        }else{
            return false;               //Devuelve false si ya está
        }
    }else{
        TNodoABB *aux= new TNodoABB();                  //Utilizamos puntero auxiliar o el destructor de TPoro destruye el nuevo TPoro introducido
        aux->item=nuevo;
        nodo=aux;
        return true;
    }

    return true;

}

bool TABBPoro::Borrar(const TPoro &borrado){            //Criterio de borrado: mayor de la izquierda

    if(Buscar(borrado)){
       
        if(!EsVacio()){                 //No haría falta comprobar esto si se sabe que el TPoro sí está, si se llega a esta condición, nunca debe ser falsa
            if(nodo->item == borrado){
                //Borrar si no tiene hijos
                if(nodo->iz.EsVacio() && nodo->de.EsVacio()){
                    //Simplemente borrar, es nodo hoja y no tiene hijos
                    //destruir arbol o delete nodo
                    delete nodo;                        //NECESITA MÁS DELETE NODOS EN EL RESTO DE BORRARS
                    nodo=NULL;

                }else if(nodo->de.EsVacio()){                                 //Borrar si tiene hijos
                    /*if(nodo->de.nodo->iz.EsVacio()){                   //En caso de no haber un "menor de la derecha", se sustituye por el nodo de la derecha directamente
                        nodo->item=nodo->de.nodo->item;
                        nodo->de.Borrar(nodo->item);                        //Después de asignar el sustituto del nodo, este se borra de donde estuviera en el árbol
                    }
                    else{
                        //Buscar el menor de la derecha si la izquierda está vacía
                        TNodoABB *i = nodo->de.nodo;
                        
                        while(!i->iz.EsVacio()){        //Seguirá buscando el menor (el nodo a la izquierda), hasta que no haya más
                            i=i->iz.nodo;
                        }

                        nodo->item=i->item;                     //Una vez encontrado el menor de la derecha, se asigna y se borra de su nodo anterior
                        nodo->iz.Borrar(i->item);
                    }*/
                    TNodoABB* aux = nodo->iz.nodo;
                    //delete nodo;
                    nodo=aux;

                }else if(nodo->iz.EsVacio()){
                    TNodoABB* aux = nodo->de.nodo;
                    //delete nodo;
                    nodo=aux;
                }else{
                    //Aplicamos aquí el criterio: mayor de la izquierda
                    //Buscar el mayor de la izquierda e intercambiarlo
                        
                    TNodoABB *i = nodo->iz.nodo;
                    
                    while(!i->de.EsVacio()){
                        i=i->de.nodo;
                    }

                    //Borrar el item
                    nodo->item=i->item;
                    nodo->iz.Borrar(i->item);
                    
                }

                return true;
            }else if(nodo->item>borrado){           //Buscará el Poro que se quiere borrar comparándolo con cada nodo
                return nodo->iz.Borrar(borrado);
            }else{
                return nodo->de.Borrar(borrado);
            }
        }
    }

    return false;
}

bool TABBPoro::Buscar(const TPoro &buscado) const{

    if(!EsVacio()){
        if(nodo->item == buscado)
            return true;
        else if(nodo->item>buscado){
            return nodo->iz.Buscar(buscado);
        }else{
            return nodo->de.Buscar(buscado);
        }
    }

    return false;
}

TPoro TABBPoro::Raiz() const{
    TPoro raiz;

    if(!EsVacio()){              //if y si lo encuentra, lo devuelve
        raiz=nodo->item;
    }

    return raiz;
}

int TABBPoro::Altura() const{

    if(EsVacio())
        return 0;
    else{
        return ( 1 + max(nodo->iz.Altura(), nodo->de.Altura()));
    }

}

int TABBPoro::Nodos() const{

    if(EsVacio())
        return 0;
    else{
        if(nodo->iz.EsVacio() && nodo->de.EsVacio())
            return 1;
        else
            return (1 + nodo->iz.Nodos() + nodo->de.Nodos());
    }
    
    
}

int TABBPoro::NodosHoja() const{

    if(!EsVacio()){
        if(nodo->iz.EsVacio() && nodo->de.EsVacio())
            return 1;
        else
            return ( nodo->iz.NodosHoja() + nodo->de.NodosHoja() );
    }

    return 0;
}

void TABBPoro::InordenAux(TVectorPoro &recorrido, int &n)const{

    if(!EsVacio()){
        nodo->iz.InordenAux(recorrido,n);
        recorrido[n++]=Raiz();
        nodo->de.InordenAux(recorrido,n);
    }

}

void TABBPoro::PreordenAux(TVectorPoro &recorrido, int &n) const{

    if(!EsVacio()){
        recorrido[n++]=Raiz();
        nodo->iz.PreordenAux(recorrido,n);
        nodo->de.PreordenAux(recorrido,n);
    }
}

void TABBPoro::PostordenAux(TVectorPoro &recorrido, int &n) const{
    
    if(!EsVacio()){
        nodo->iz.PostordenAux(recorrido,n);
        nodo->de.PostordenAux(recorrido,n);
        recorrido[n++]=Raiz();
    }
}

TVectorPoro TABBPoro::Inorden() const{

    //Posición en el vector que almacena el rcorrido
    int posicion=1;

    //Vector del tamaño adecuado para almacenar todos los nodos
    TVectorPoro v(Nodos());
    InordenAux(v, posicion);
    return v;

}

TVectorPoro TABBPoro::Preorden() const{

    //Posición en el vector que almacena el rcorrido
    int posicion=1;

    //Vector del tamaño adecuado para almacenar todos los nodos
    TVectorPoro v(Nodos());
    PreordenAux(v, posicion);
    return v;
}

TVectorPoro TABBPoro::Postorden() const{

    //Posición en el vector que almacena el rcorrido
    int posicion=1;

    //Vector del tamaño adecuado para almacenar todos los nodos
    TVectorPoro v(Nodos());
    PostordenAux(v, posicion);
    return v;
}

TVectorPoro TABBPoro::Niveles() const{

    queue<TABBPoro> queue;          //Creamos la queue y el vector (con los Nodos() )
    TVectorPoro vector(Nodos());

    TABBPoro este = *this;              //Empezamos añadiendo el primero
    queue.push(este);

    for(int i=1;!queue.empty();i++){        //Recorremos todo el resto

        vector[i] = este.nodo->item;        
        este = queue.front();

        if(!este.nodo->iz.EsVacio())
            queue.push(este.nodo->iz);
        if(!este.nodo->de.EsVacio())
            queue.push(este.nodo->de);
    }

    return vector;
}

ostream& operator<<(ostream &os, const TABBPoro &abb){

    TABBPoro este(abb);
    os << este.Niveles();
    
    return os;

}