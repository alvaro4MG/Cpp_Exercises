
#include "../include/tporo.h"

TPoro::TPoro(){             //Constructor por defecto
    x=y=0;
    volumen=0;
    color=NULL;     //el new se pondrá cuando tengamos algo que escribir en el color
}

TPoro::TPoro(int a, int b, double vol){             //Constructor con argumentos (no con color)
    x=a;
    y=b;
    volumen=vol;
    color=NULL;
}

TPoro::TPoro(int a, int b, double vol, char* orig){             //Constructor con argumentos (con color)
    x=a;
    y=b;
    volumen=vol;
    //color=orig;     //esto estaría mal porque color y orig apuntan al mismo sitio y tendrían que ser independientes, por lo que hay que hacer copia profunda para tener memoria nueva para el color
    if(orig!=NULL){
        color=new char[strlen(orig)+1];     //la memoria se reserva, ahora toca copiarlo. Puede ser NULL, hay que comprobar eso (si lo es, se pone a NULL)
        strcpy(color,orig);                 //aquí se copia
    }
    else
        color=NULL;
}

TPoro::TPoro(const TPoro &orig){            //Constructor de copia (necesario pasar el TPoro argumento como referencia o entra en un bucle de llamar al constructor de copia)
    x=orig.x;
    y=orig.y;
    volumen=orig.volumen;                       //Copia todos los datos de forma similar al contructor con argumentos
    if(orig.color!=NULL){
        color=new char[strlen(orig.color)+1];
        strcpy(color,orig.color);
    }else{
        color=NULL;
    }
}

TPoro::~TPoro(){                //Destructor o liberador
    x=y=0;
    volumen=0;
    if(color != NULL){
        delete color;           //liberamos la memoria, esto es lo que nos importa liberar, el resto se queda a 0 y el objeto sigue existiendo, pero ocupa menos
        color=NULL;
    }
    
}

TPoro& TPoro::operator=(const TPoro &op2){     //Operador de asignación, se devuelve por referencia
    if(this != &op2){
        (*this).~TPoro();                   //hacemos referencia al propio objeto y lo borramos previamente con el constructor/liberador (siempre que sean distintos)
        x=op2.x;                            //asignamos los valores como en el constructor de copia
        y=op2.y;
        volumen=op2.volumen;
        if(op2.color!=NULL){
            color=new char[strlen(op2.color)+1];
            strcpy(color,op2.color);
        }else{color=NULL;}
    }
    return *this;
}

bool TPoro::operator==(const TPoro &op2){       //Operador de igualdad
    if(color!=NULL && op2.color!=NULL){                      //no podemos hacer strcmp normal sin comprobar que no sean NULL los colores
        return ( (x==op2.x) && (y==op2.y) && (volumen==op2.volumen) && strcasecmp(color,op2.color)==0 );
        
    }else{
        return ( (color==NULL && op2.color==NULL) &&                          //Si cualquiera de los colores es NULL, los poros son distintos y se devolverá false (al utilizar &&, no se comprueba el segundo operando si el primero es falso)
                ( (x==op2.x) && (y==op2.y) && (volumen==op2.volumen) ) );
    }
    
}

bool TPoro::operator!=(const TPoro &op2){       //Operador de desigualdad, devuelve lo contrario que el operador de igualdad
    return !((*this)== op2 );
}

bool TPoro::operator<(const TPoro &op2){
    return ( volumen < op2.volumen );
}

bool TPoro::operator>(const TPoro &op2){
    return ( volumen > op2.volumen );
}

void TPoro::Posicion(int x, int y){             //Modifica la posición según la que se pase por argumento
    this->x=x;
    this->y=y;
}

void TPoro::Color(char *newColor){              //Se modifica el color que se le pase por argumento
    if(newColor!=NULL){
        color=new char[strlen(newColor)+1];
        strcpy(color,newColor);
    }
}

bool TPoro::EsVacio() const{                                    //Comprueba que el poro esté vacío, viendo si los argumentos se corresponden a un poro vacío
    if( (x==0) && (y==0) && (volumen==0) && (color==NULL) )
        return true;
    return false;
}


ostream& operator<<(ostream &os, const TPoro &poro){            //Operador salida, puede acceder a los atributos porque se declara como función amiga (puede acceder a la parte privada)

    if(!poro.EsVacio()){
        os.setf(ios::fixed);
        os.precision( 2 );
        os << "(" << poro.x << ", " << poro.y << ") " << poro.volumen << " ";
        if(poro.color!=NULL)
            os << poro.color;
        else
            os << "-";        
    }
    else
        os << "()";
    
    return os;
}