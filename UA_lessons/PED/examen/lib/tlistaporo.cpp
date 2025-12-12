
#include "../include/tlistaporo.h"

TListaNodo::TListaNodo(){             //Constructor por defecto
    anterior=NULL;
    siguiente=NULL;
}

TListaNodo::TListaNodo(const TListaNodo &orig){         //Constructor de copia
    anterior=orig.anterior;
    siguiente=orig.siguiente;
}

TListaNodo::~TListaNodo(){          //Destructor/liberador
    e.~TPoro();
    anterior=NULL;              //No utilizamos delete, a diferencia de como hemos utilizado varias veces hasta ahora, porque borraría el contenido de anterior y siguiente cuando solo nos importa el puntero del nodo
    siguiente=NULL;
    
}

TListaNodo& TListaNodo::operator=(const TListaNodo &op2){           //Operador de asignación
    if(this != &op2){
        (*this).~TListaNodo();
        e=op2.e;
        anterior=op2.anterior;
        siguiente=op2.siguiente;
    }
    return *this;
}







TListaPosicion::TListaPosicion(){             //Constructor por defecto
    pos=NULL;
}

TListaPosicion::TListaPosicion(const TListaPosicion &orig){            //Constructor de copia
    pos=orig.pos;
}

TListaPosicion::~TListaPosicion(){              //Destructor/liberador
    pos=NULL;
}

TListaPosicion& TListaPosicion::operator=(const TListaPosicion &op2){       //Operador de asignación
    if(this != &op2){
        pos=op2.pos;
    }
    return (*this);
}

TListaPosicion TListaPosicion::Anterior(){
    TListaPosicion a;
    if(pos->anterior !=NULL)
        a.pos=pos->anterior;
    return a;                           //Devuelve la posición vacía si no tiene anterior
}

TListaPosicion TListaPosicion::Siguiente(){
    TListaPosicion s;
    if(pos->siguiente !=NULL)
        s.pos=pos->siguiente;
    return s;
}





TListaPoro::TListaPoro(){             //Constructor por defecto
    primero=NULL;
    ultimo=NULL;
}

TListaPoro::TListaPoro(const TListaPoro &orig){            //Constructor de copia
    primero=NULL;
    for(TListaPosicion i=orig.Primera(); !i.EsVacia(); i=i.Siguiente()){
        this->Insertar(i.pos->e);
    }
    
}

TListaPoro::~TListaPoro(){              //Destructor/liberador
    TListaNodo* aux;

    while(primero !=NULL){              //borramos de uno en uno con un while donde mantenemos el siguiente
        aux=primero->siguiente;
        delete primero;
        primero=aux;
    }
}

TListaPoro& TListaPoro::operator=(const TListaPoro &op2){
    if(this != &op2){
        (*this).~TListaPoro();
        for(TListaPosicion i=op2.Primera(); !i.EsVacia(); i=i.Siguiente()){
            this->Insertar(i.pos->e);
        }
    }
    return *this;
}

bool TListaPoro::operator==(const TListaPoro &op2){
    
    if(this != &op2){
        if(Longitud()==op2.Longitud()){
            TListaPosicion j=Primera();
            for(TListaPosicion i=op2.Primera(); !i.EsVacia(); i=i.Siguiente()){
                if(!(i==j)){
                    return false;               //Devolverá false si cualquiera de las TListaPosicion son distintas
                }
                j=j.Siguiente();
            }
        }
        else{
            return false;
        }

    }
    return true;                //Si no se han cumplido las condiciones (que sean de longitudes distintas o algún elemento sea distinto), devuelve true porque significa que son iguales
}

TListaPoro& TListaPoro::operator+(const TListaPoro &op2){
    
    TListaPosicion j=op2.Primera();

    for(TListaPosicion i=Primera(); !i.EsVacia() || !j.EsVacia() ; ){

        if(i.EsVacia()){
            this->Insertar(j.pos->e);
            j=j.Siguiente();
        }else if(j.EsVacia()){
            this->Insertar(i.pos->e);
            i=i.Siguiente();
        }else{
            if(i.pos->e.Volumen() < j.pos->e.Volumen()){
                this->Insertar(i.pos->e);
                i=i.Siguiente();
            }else{
                this->Insertar(j.pos->e);
                j=j.Siguiente();
            }
        }

    }

    return *this;
}

TListaPoro& TListaPoro::operator-(const TListaPoro &op2){

    for(TListaPosicion i=Primera(); !i.EsVacia() ;i=i.Siguiente() )
        if(op2.Buscar(i.pos->e))                                   //Insertará todos los que no encuentre en op2
            this->Borrar(i.pos->e);

    return *this;
}


bool TListaPoro::Insertar(const TPoro &nuevo){      //Hay que recorrer toda la lsita porque es ordenada y colocarlo en su lugar, si hay uno igual se inserta después
    TListaNodo* aux = new TListaNodo();
    aux->e=nuevo;
    if(this->EsVacia()){

        aux->siguiente=NULL;
        aux->anterior=NULL;
        primero=aux;
        ultimo=aux;
        return true;
    }else if(!this->Buscar(nuevo)){       //Si no está, hay que ponerlo ordenado
        TListaNodo* guia= new TListaNodo();
        guia=primero;
        do{
            if(guia==primero && (aux->e.Volumen() < guia->e.Volumen())){
                aux->siguiente=guia;
                aux->anterior=NULL;
                guia->anterior=aux;
                primero=aux;
                return true;
            }else if(guia->siguiente != NULL && (guia->siguiente->e.Volumen() >= aux->e.Volumen()  )){
                aux->siguiente=guia->siguiente;
                aux->anterior=guia;
                guia->siguiente->anterior=aux;          //Esto es necesario?
                guia->siguiente=aux;
                return true;
            }else if(guia->siguiente == NULL){
                aux->siguiente = NULL;
                aux->anterior=guia;
                guia->siguiente = aux;
                ultimo=aux;
                return true;
            }

            guia=guia->siguiente;
        }while(guia!=NULL);
        return false;               //Devuelve false si no ha podido insertarlo (si ha podido, habrá devuelto un true previamente)
    }
    return false;        //devuelve false si ya está en la lista
}

bool TListaPoro::Borrar(const TPoro &viejo){
    
    
    if(Buscar(viejo)){
        if(Longitud()==1){                  //En caso de que solo haya uno, hay que asignar NULL a primero y a ultimo
            delete primero;
            primero=NULL;
            ultimo=NULL;
            return true;
        }
        for(TListaPosicion i=Primera(); !i.EsVacia(); i=i.Siguiente()){
            TListaNodo* aux=i.pos;
            if(primero==aux && aux->e==viejo){                          //Los casos en los que el borrado son el primero o el último son especiales y se deben comprobar para asignar sus TListaNodo correspondientes
                primero->siguiente->anterior=NULL;
                primero=primero->siguiente;
                delete aux;
                return true;
            }
            else if(ultimo==aux && aux->e==viejo){
                ultimo->anterior->siguiente=NULL;
                ultimo=ultimo->anterior;
                delete aux;
                return true;
            }
            else if(aux->e==viejo){                                      //En caso de ser un caso general, simplemente nos ocupamos del siguiente y el anterior antes de borrar el TPoro
                aux->anterior->siguiente=aux->siguiente;
                aux->siguiente->anterior=aux->anterior;
                delete aux;
                return true;
            }
        }

    }
    
    return false;
}

bool TListaPoro::Borrar(const TListaPosicion &posicion){
    
    if(!posicion.EsVacia()){
        TPoro aux= posicion.pos->e;
        return Borrar(aux);
    }
    return false;
    
}

TPoro TListaPoro::Obtener(const TListaPosicion &posicion) const{
    
    if(!this->EsVacia())
        for(TListaPosicion i=Primera(); !i.EsVacia(); i=i.Siguiente())
            if(i==posicion)
                return i.pos->e;
    return TPoro();
}

bool TListaPoro::Buscar(const TPoro &buscado) const{
    
    for(TListaPosicion i=Primera(); !i.EsVacia(); i=i.Siguiente())
        if(i.pos->e==buscado)
            return true;
    return false;
}

int TListaPoro::Longitud() const{
    int contador=0;

    for(TListaPosicion i=Primera(); !i.EsVacia(); i=i.Siguiente())
        contador++;
    
    return contador;
}

TListaPosicion TListaPoro::Primera() const{
    TListaPosicion p;
    if(!EsVacia())
        p.pos=this->primero;

    return p;
}

TListaPosicion TListaPoro::Ultima() const{
    TListaPosicion u=this->Primera();
    if(!EsVacia()){
        for(int i=1;i< Longitud();i++){
            u=u.Siguiente();
        }
    }
        
    return u;
}

TListaPoro TListaPoro::ExtraerRango(int n1, int n2){
    TListaPoro a;
    int longitud=Longitud();

    if(n1>n2)
        return a;
    else{
        if(n1<1)                                            //Recordar que primera posición es 1
            n1=1;
        if(n2>longitud)
            n2=longitud;
        if((n2-n1+1)>=longitud){
            a=*this;
            this->~TListaPoro();
            return a;
        }
        else{
            int contador=1;
            for(TListaPosicion i=Primera(); (contador<=(n2-n1+2) )&& !i.EsVacia(); i=i.Siguiente()){
                if(contador>=n1 && contador <=n2){
                    a.Insertar(i.pos->e);
                }
                
                contador++;
            }
        }
        
        
    }
    for(TListaPosicion i=a.Primera(); !i.EsVacia(); i=i.Siguiente()){
        Borrar(i);
    }

    return a;
}

ostream& operator<<(ostream &os, const TListaPoro &lista){

    os << "(";

    for(TListaPosicion i = lista.Primera(); !i.EsVacia(); i=i.Siguiente()){
        os << lista.Obtener(i);
        if(!(i == lista.Ultima()) )
            os<< " ";
    }

    os << ")";

    return os;

}