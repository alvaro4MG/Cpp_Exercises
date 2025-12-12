#include <iostream>
#include "tporo.h"
#include "tvectorporo.h"
#include "tavlporo.h"

using namespace std;

int
main(void)
{
/*******************************************************************/
/********** ASIGNACION , "<<" ; posible problema de CONST 	   */
/*******************************************************************/
  
  TAVLPoro a,b,c;

  TPoro p1(1,2,1,(char *) "rojo");

  a.Insertar(p1);


  cout << a.Inorden() << endl;


  return 1;
}
