//Uses
    //Allocation (new) and deallocation (delete)

#include<iostream>

using namespace std;

int main(){
    double *pd;
    pd = new double;      //new operator for dynamic memory, allocates memory for a double, crea una nueva cajita y guarda esa dirección
                        //free it with delete: delete pd; and then pd=NULL (to make sure it isn't still pointing)


    delete pd;

    return 0;
}