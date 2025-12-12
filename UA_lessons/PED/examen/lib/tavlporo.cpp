
#include "../include/tavlporo.h"


TNodoAVL::TNodoAVL(): item(), iz(), de(){
    //Ya están todos los constructores, no hace falta hacer más
    fe=0;
}

TNodoAVL::TNodoAVL(const TNodoAVL &orig)    :       //los : son el inicializador de objetos (cuando hay layering)
    item(orig.item), iz(orig.iz), de(orig.de){
        fe=orig.fe;
}

TNodoAVL::~TNodoAVL(){
    //Vacio porque hay una composición que invocan a sus destructores y no hay más variables que tengamos que borrar
    fe=0;
}

TNodoAVL& TNodoAVL::operator=(const TNodoAVL &op2){     

    if(this!=&op2){
        (*this).~TNodoAVL();
        item=op2.item;
        iz=op2.iz;
        de=op2.de;
        fe=op2.fe;
    }
    return *this;
}






TAVLPoro::TAVLPoro(){
    raiz=NULL;
}

TAVLPoro::TAVLPoro(const TAVLPoro &orig){
    
    if(orig.raiz!=NULL){
        TNodoAVL *aux=new TNodoAVL();           //Se hace un puntero y tiene todo a NULL
        aux->item=orig.raiz->item;
        raiz=aux;                               //Nuestro nuevo raiz es aux
        raiz->iz.Copiar(orig.raiz->iz);         //Se harán llamadas recursivas
        raiz->de.Copiar(orig.raiz->de);
    }else{
        raiz=NULL;
    }
}

TAVLPoro::~TAVLPoro(){
    TNodoAVL *aux= new TNodoAVL();

    if(raiz!=NULL){
        aux=raiz;
        raiz->iz.~TAVLPoro();               //Borramos izquierda y derecha antes de borrar el raiz
        raiz->de.~TAVLPoro();

        delete raiz;                        //Llama a todos los destructores del raiz, tanto del item como de los dos hijos (los hijos llamaarían a este destructor porque son también AVL)
        raiz=NULL;
    }
}


void TAVLPoro::Copiar(const TAVLPoro &orig){
    if(!orig.EsVacio()){
        raiz= new TNodoAVL();
        raiz->item=orig.raiz->item;
        raiz->iz.Copiar(orig.raiz->iz);
        raiz->de.Copiar(orig.raiz->de);
    }
    else
        raiz=NULL;
}

TAVLPoro& TAVLPoro::operator=(const TAVLPoro &op2){

    if(! (this == &op2)){
        this->~TAVLPoro();
        this->Copiar(op2);
    }
    return *this;
}

bool TAVLPoro::operator==(const TAVLPoro &op2) const{           //Esto es según elementos, da igual la estructura

    if(!EsVacio() && !op2.EsVacio()){
        return (Inorden() == op2.Inorden());
    }else if(EsVacio() && op2.EsVacio()){
        return true;
    }

    return false;
}

bool TAVLPoro::operator!=(const TAVLPoro &op2) const{ 
    return !(*this==op2);
}

void TAVLPoro::EquilibrarIzquierda(){           //Rotación II o ID
    TNodoAVL* j;
    TNodoAVL* k;
    if(raiz->iz.raiz->fe==-1){              //Rotación II
        //Mover (j, HIJOIZ(I) )
        j=raiz->iz.raiz;
        raiz->iz.raiz=NULL;

        //Otro mover (HIJOIZ(I), HIJODE(J))
        raiz->iz.raiz=j->de.raiz;
        j->de.raiz=NULL;

        //mover (HIJODE(J), I)
        k=j->de.raiz;
        j->de.raiz=raiz;
        j->de.raiz->iz.raiz=k;
        raiz=j;
        
        //FACTORES
        raiz->fe=0;
        raiz->de.raiz->fe=0;
        
    }else{                                  //Rotación ID
        int e2;
        //Mover (J, HIJOIZ(I))
        j=raiz->iz.raiz;
        //raiz->iz.raiz=NULL;

        //Mover (K, HIJODE(J))
        k=j->de.raiz;
        //raiz->de.raiz=NULL;

        //E2=FE(K)
        e2=k->fe;

        //Mover (HIJOIZ(I), HIJODE(K))
        raiz->iz.raiz=k->de.raiz;

        //Mover (HIJODE(J), HIJOIZ(K))
        j->de.raiz=k->iz.raiz;

        //Mover (HIJOIZ(K), J)
        k->iz.raiz=j;

        //Mover (HIJODE(K), I)
        k->de.raiz=raiz;

        //FE(K) = 0
        k->fe=0;

        switch (e2){
            case -1: 
                    //FE(HIJOIZ(K)) = 0
                    k->iz.raiz->fe=0;
                    //FE(HIJODE(K)) = 1
                    k->de.raiz->fe=1;
                break;
            case 1: 
                    //FE(HIJOIZ(K)) = -1
                    k->iz.raiz->fe=-1;
                    //FE(HIJODE(K)) = 0
                    k->de.raiz->fe=0;
                break;
            case 0: 
                    //FE(HIJOIZ(K)) = 0
                    k->iz.raiz->fe=0;
                    //FE(HIJODE(K)) = 0
                    k->de.raiz->fe=0;
                break;
        }

        //Mover (I, K)
        raiz=k;
    }
}

void TAVLPoro::EquilibrarIzquierdaBorrar(){           //Rotación II o ID
    TNodoAVL* j;
    TNodoAVL* k;
    if(raiz->iz.raiz->fe!=1){              //Rotación II
        //Mover
        j=raiz->iz.raiz;

        //Otro mover
        raiz->iz.raiz=j->de.raiz;

        j->de.raiz=raiz;
        raiz=j;
        
        //FACTORES
        //Un if para otros casos?
        if(raiz->iz.raiz->de.EsVacio()){
            raiz->fe=0;             //Tendría que ser 0? Antes estaba a 1       ESTO ESTÁ MAL
            raiz->de.raiz->fe=0;   //Tendría que ser 0? Antes estaba a -1
        }else{
            raiz->fe=1;             //Tendría que ser 0? Antes estaba a 1       ESTO ESTÁ MAL
            raiz->de.raiz->fe=-1;
        }
    
    }else{                                  //Rotación ID
        int e2;
        //Mover (J, HIJOIZ(I))
        j=raiz->iz.raiz;
        //raiz->iz.raiz=NULL;

        //Mover (K, HIJODE(J))
        k=j->de.raiz;
        //raiz->de.raiz=NULL;

        //E2=FE(K)
        e2=k->fe;

        //Mover (HIJOIZ(I), HIJODE(K))
        raiz->iz.raiz=k->de.raiz;

        //Mover (HIJODE(J), HIJOIZ(K))
        j->de.raiz=k->iz.raiz;

        //Mover (HIJOIZ(K), J)
        k->iz.raiz=j;

        //Mover (HIJODE(K), I)
        k->de.raiz=raiz;

        //FE(K) = 0
        k->fe=0;

        switch (e2){
            case -1: 
                    k->iz.raiz->fe=0;
                    k->de.raiz->fe=1;
                break;
            case 1: 
                    //FE(HIJOIZ(K)) = -1
                    k->iz.raiz->fe=-1;
                    //FE(HIJODE(K)) = 0
                    k->de.raiz->fe=0;
                break;
            case 0: 
                    //FE(HIJOIZ(K)) = 0
                    k->iz.raiz->fe=-1;
                    //FE(HIJODE(K)) = 0
                    k->de.raiz->fe=1;
                break;
        }

        //Mover (I, K)
        raiz=k;
    }
}

void TAVLPoro::EquilibrarDerecha(){           //Rotación DD o DI
    TNodoAVL* j;
    TNodoAVL* k;
    if(raiz->de.raiz->fe==1){               //Rotación DD
        //Mover
        j=raiz->de.raiz;
        raiz->de.raiz=NULL;

        //Otro mover
        raiz->de.raiz=j->iz.raiz;
        j->iz.raiz=NULL;                //Aquí lo hacemos NULL y luego lo asignamos????

        k=j->iz.raiz;
        j->iz.raiz=raiz;
        j->iz.raiz->de.raiz=k;
        raiz=j;
        
        //FACTORES
        raiz->fe=0;
        raiz->iz.raiz->fe=0;
    }else{                                  //Rotación DI
        int e2;
        
        j=raiz->de.raiz;
        
        k=j->iz.raiz;

        //E2=FE(K)
        e2=k->fe;

        raiz->de.raiz=k->iz.raiz;

        j->iz.raiz=k->de.raiz;

        k->de.raiz=j;

        k->iz.raiz=raiz;

        //FE(K) = 0
        k->fe=0;

        switch (e2){
            case -1: 
                    k->de.raiz->fe=0;
                    k->iz.raiz->fe=1;
                break;
            case 1: 
                    k->de.raiz->fe=-1;
                    k->iz.raiz->fe=0;
                break;
            case 0: 
                    k->de.raiz->fe=0;
                    k->iz.raiz->fe=0;
                break;
        }

        //Mover (I, K)
        raiz=k;
    }
}

void TAVLPoro::EquilibrarDerechaBorrar(){           //Rotación DD o DI
    TNodoAVL* j;
    TNodoAVL* k;
    if(raiz->de.raiz->fe!=-1){               //Rotación DD
    
        //Mover
        j=raiz->de.raiz;

        //Otro mover
        raiz->de.raiz=j->iz.raiz;

        j->iz.raiz=raiz;
        raiz=j;
        
        //FACTORES
        if(raiz->de.raiz->iz.EsVacio()){
            raiz->fe=0;             //Tendría que ser 0? Antes estaba a 1       ESTO ESTÁ MAL
            raiz->de.raiz->fe=0;   //Tendría que ser 0? Antes estaba a -1
        }else{
            raiz->fe=-1;             //Tendría que ser 0? Antes estaba a 1       ESTO ESTÁ MAL
            raiz->iz.raiz->fe=1;
        }
        
    }else{                                  //Rotación DI
        int e2;
        
        j=raiz->de.raiz;
        
        k=j->iz.raiz;

        //E2=FE(K)
        e2=k->fe;

        raiz->de.raiz=k->iz.raiz;

        j->iz.raiz=k->de.raiz;

        k->de.raiz=j;

        k->iz.raiz=raiz;

        //FE(K) = 0
        k->fe=0;

        switch (e2){
            case -1: 
                    k->de.raiz->fe=0;
                    k->iz.raiz->fe=1;
                break;
            case 1: 
                    k->de.raiz->fe=0;
                    k->iz.raiz->fe=-1;
                break;
            case 0: 
                    k->de.raiz->fe=-1;
                    k->iz.raiz->fe=1;
                break;
        }

        //Mover (I, K)
        raiz=k;
    }
}

bool TAVLPoro::InsertarAux(const TPoro &nuevo, bool &crece){
    bool creceHijoIz=false, creceHijoDe=false, insercionOK=false;


    if(!EsVacio()){
        if(!Buscar(nuevo)){
            if(raiz->item>nuevo){
                insercionOK = raiz->iz.InsertarAux(nuevo,creceHijoIz);
            }else if(raiz->item<nuevo){
                insercionOK = raiz->de.InsertarAux(nuevo,creceHijoDe);
            }
        }else{
            insercionOK = false;               //Devuelve false si ya está
        }

        if(creceHijoDe || creceHijoIz){
            if( (creceHijoIz && raiz->fe==1) || (creceHijoDe && raiz->fe==-1) ){
                crece=false;
                raiz->fe=0;
            }else if(creceHijoIz && raiz->fe==0){
                crece=true;
                raiz->fe--;
            }else if(creceHijoDe && raiz->fe==0){
                crece=true;
                raiz->fe++;
            }else if(creceHijoIz && raiz->fe==-1){
                EquilibrarIzquierda();
                crece=false;
            }else if(creceHijoDe && raiz->fe==1){
                EquilibrarDerecha();
                crece=false;
            }

        }else{
            crece=false;
        }
    }else{
        TNodoAVL *aux= new TNodoAVL();                  //Utilizamos puntero auxiliar o el destructor de TPoro destruye el nuevo TPoro introducido
        aux->item=nuevo;
        raiz=aux;
        //el fe está a 0 con el constructor por defecto
        crece=true;
        
        return true;
    }


    return insercionOK;
}

bool TAVLPoro::Insertar(const TPoro &nuevo){            //Ordenados según volumen, de menor a mayor, no se puede repetir volumen
    bool crece=false;
    return InsertarAux(nuevo,crece);
}

bool TAVLPoro::BorrarAux(const TPoro &borrado,bool &decrece){            //Criterio de borrado: mayor de la izquierda
    bool decreceHijoIz=false, decreceHijoDe=false, borradoOK=false;
       
    if(!EsVacio()){                 //No haría falta comprobar esto si se sabe que el TPoro sí está, si se llega a esta condición, nunca debe ser falsa
        if(raiz->item == borrado){
            //Borrar si no tiene hijos
            if(raiz->iz.EsVacio() && raiz->de.EsVacio()){
                //Simplemente borrar, es raiz hoja y no tiene hijos
                //destruir arbol o delete raiz
                delete raiz;                        //NECESITA MÁS DELETE NODOS EN EL RESTO DE BORRARS
                raiz=NULL;
                borradoOK=true;
                decrece=true;
            }else if(raiz->de.EsVacio()){                                 //Borrar si tiene hijos
                TNodoAVL* aux = raiz->iz.raiz;
                raiz=aux;
                //decreceHijoIz=true;
                borradoOK=true;
                decrece=true;
            }else if(raiz->iz.EsVacio()){
                TNodoAVL* aux = raiz->de.raiz;
                raiz=aux;
                //decreceHijoDe=true;
                borradoOK=true;
                decrece=true;
            }else{
                //Aplicamos aquí el criterio: mayor de la izquierda
                //Buscar el mayor de la izquierda e intercambiarlo
                    
                TNodoAVL *i = raiz->iz.raiz;
                
                while(!i->de.EsVacio()){
                    i=i->de.raiz;
                }

                //Borrar el item
                raiz->item=i->item;
                borradoOK = raiz->iz.BorrarAux(i->item,decreceHijoIz);
                decrece = true;
                //decreceHijoIz=true;
                
            }

            //Iba aquí lo de if(decreceHijos)

            //return borradoOK;
        }else if(raiz->item>borrado){           //Buscará el Poro que se quiere borrar comparándolo con cada raiz
            borradoOK = raiz->iz.BorrarAux(borrado,decreceHijoIz);
        }else{
            borradoOK = raiz->de.BorrarAux(borrado,decreceHijoDe);
        }

        if(decreceHijoDe || decreceHijoIz){
            if( (decreceHijoDe && raiz->fe==1) || (decreceHijoIz && raiz->fe==-1) ){
                decrece=true;
                raiz->fe=0;
            }else if(decreceHijoIz && raiz->fe==0){
                decrece=false;
                raiz->fe++;         //Cambiar estos operadores????  ESTÁN CAMBIADOS
            }else if(decreceHijoDe && raiz->fe==0){
                decrece=false;
                raiz->fe--;
            }else if(decreceHijoIz && raiz->fe==1){
                EquilibrarDerechaBorrar();          //equilibra el contrario?
                if(raiz->fe==0)
                    decrece=true;
                else
                    decrece=false;          //MAL????
            }else if(decreceHijoDe && raiz->fe==-1){
                EquilibrarIzquierdaBorrar();
                if(raiz->fe==0)
                    decrece=true;
                else
                    decrece=false;
            }

        }else{
            //decrece=false;
        }
    }
    

    return borradoOK;
}

bool TAVLPoro::Borrar(const TPoro &borrado){
    if(Buscar(borrado)){                        //Dejamos esta condición aquí para evitar que se repita en las llamadas recursivas
        bool decrece=false;
        return BorrarAux(borrado,decrece);
    }else{
        return false;
    }
}

bool TAVLPoro::Buscar(const TPoro &buscado) const{

    if(!EsVacio()){
        if(raiz->item == buscado)
            return true;
        else if(raiz->item>buscado){
            return raiz->iz.Buscar(buscado);
        }else{
            return raiz->de.Buscar(buscado);
        }
    }

    return false;
}

TPoro TAVLPoro::Raiz() const{
    TPoro raizDevuelta;

    if(!EsVacio()){              //if y si lo encuentra, lo devuelve
        raizDevuelta=raiz->item;
    }

    return raizDevuelta;
}

int TAVLPoro::Altura() const{

    if(EsVacio())
        return 0;
    else{
        return ( 1 + max(raiz->iz.Altura(), raiz->de.Altura()));
    }

}

int TAVLPoro::Nodos() const{

    if(EsVacio())
        return 0;
    else{
        if(raiz->iz.EsVacio() && raiz->de.EsVacio())
            return 1;
        else
            return (1 + raiz->iz.Nodos() + raiz->de.Nodos());
    }
    
    
}

int TAVLPoro::NodosHoja() const{

    if(!EsVacio()){
        if(raiz->iz.EsVacio() && raiz->de.EsVacio())
            return 1;
        else
            return ( raiz->iz.NodosHoja() + raiz->de.NodosHoja() );
    }

    return 0;
}

void TAVLPoro::InordenAux(TVectorPoro &recorrido, int &n)const{

    if(!EsVacio()){
        raiz->iz.InordenAux(recorrido,n);
        recorrido[n++]=Raiz();
        raiz->de.InordenAux(recorrido,n);
    }

}

void TAVLPoro::PreordenAux(TVectorPoro &recorrido, int &n) const{

    if(!EsVacio()){
        recorrido[n++]=Raiz();
        raiz->iz.PreordenAux(recorrido,n);
        raiz->de.PreordenAux(recorrido,n);
    }
}

void TAVLPoro::PostordenAux(TVectorPoro &recorrido, int &n) const{
    
    if(!EsVacio()){
        raiz->iz.PostordenAux(recorrido,n);
        raiz->de.PostordenAux(recorrido,n);
        recorrido[n++]=Raiz();
    }
}

TVectorPoro TAVLPoro::Inorden() const{

    //Posición en el vector que almacena el rcorrido
    int posicion=1;

    //Vector del tamaño adecuado para almacenar todos los raizs
    TVectorPoro v(Nodos());
    InordenAux(v, posicion);
    return v;

}

TVectorPoro TAVLPoro::Preorden() const{

    //Posición en el vector que almacena el rcorrido
    int posicion=1;

    //Vector del tamaño adecuado para almacenar todos los raizs
    TVectorPoro v(Nodos());
    PreordenAux(v, posicion);
    return v;
}

TVectorPoro TAVLPoro::Postorden() const{

    //Posición en el vector que almacena el rcorrido
    int posicion=1;

    //Vector del tamaño adecuado para almacenar todos los raizs
    TVectorPoro v(Nodos());
    PostordenAux(v, posicion);
    return v;
}

TVectorPoro TAVLPoro::Niveles() const{

    queue<TAVLPoro> queue;
    TVectorPoro vector(Nodos());

    TAVLPoro este = *this;
    queue.push(este);

    for(int i=1;!queue.empty();i++){
        vector[i] = este.raiz->item;
        este = queue.front();

        if(!este.raiz->iz.EsVacio())
            queue.push(este.raiz->iz);
        if(!este.raiz->de.EsVacio())
            queue.push(este.raiz->de);
    }

    return vector;
}

//Función práctica examen
int* TAVLPoro::BuscaAVL(const TListaPoro &lista) const{
    int* enteros= new int[lista.Longitud()];
    unsigned counter=0;
    bool found=false;
    TNodoAVL* k;

    if(!lista.EsVacia()){
        for(TListaPosicion i=lista.Primera(); !i.EsVacia(); i=i.Siguiente()){
            if(!Buscar(i.pos->e)){
                enteros[counter]=0;
                //cout << "llega " << i.pos->e << endl;
            }
            else{
                //3 si es raiz
                if(i.pos->e == raiz->item){
                    enteros[counter]=3;
                }else{

                    k=raiz;
                    found=false;
                    // 1 si es hijo izquierda
                    while(!found){
                        //cout << "empieza "<< i.pos->e << endl;
                        
                        if(i.pos->e < k->item){
                            //cout << "izquierda "<< i.pos->e << endl;
                            if(i.pos->e == k->iz.raiz->item){
                                enteros[counter]=1;
                                found=true;
                            }else
                            {
                                k=k->iz.raiz;
                            }
                        }else{      //2 si es hijo derecha
                            if(i.pos->e == k->de.raiz->item){
                                //cout << "llega" << endl;
                                enteros[counter]=2;
                                found=true;
                            }else
                            {
                                k=k->de.raiz;
                            }
                        }
                        
                    }
                }
                
                
            }
            counter++;
        }
    }

    return enteros;
}

ostream& operator<<(ostream &os, const TAVLPoro &avl){

    os << avl.Inorden();
    
    return os;

}