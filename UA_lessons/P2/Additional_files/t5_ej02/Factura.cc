#include "Factura.h"

int Factura::sigId = 1; // Inicializamos el atributo estático "sigId"

Factura::Factura(Cliente *c, string fecha){
  cliente = c;
  this->fecha = fecha;
  id = getSigId();
}

int Factura::getSigId(){
  return sigId++; // Devolvemos el valor actual de "sigId" y después lo incrementamos
}

void Factura::anyadirLinea(int cant, const string desc, float prec){
  Linea l;
	
  l.setCantidad(cant);
  l.setDescripcion(desc);
  l.setPrecio(prec);
	
  lineas.push_back(l);
}

ostream &operator<<(ostream &os,const Factura &f){
  os << "Factura nº: " << f.id << endl;
  os << "Fecha: " << f.fecha << endl;
  os << endl;
  os << "Datos del cliente" << endl;
  os << "-----------------" << endl;
  os << "Nombre: " << f.cliente->getNombre() << endl;
  os << "Direccion: " << f.cliente->getDireccion() << endl;
  os << "Telefono: " << f.cliente->getTelefono() << endl;
  os << endl;
  os << "Detalle de la factura" << endl;
  os << "---------------------" << endl;
  os << endl;
  os << "Linea;Producto;Cantidad;Precio ud.;Precio total" << endl;
  os << "--" << endl;

  float subtotal=0;
  for (int i=0;(unsigned)i<f.lineas.size();i++){
    os << i+1 << ";" << f.lineas[i].getDescripcion() << ";" << f.lineas[i].getCantidad() << ";" << f.lineas[i].getPrecio() << ";" << f.lineas[i].getSubtotal() << endl;
    subtotal += f.lineas[i].getSubtotal();
  }

  float impuestos=subtotal*Factura::IVA/100.0;
  float total=subtotal+impuestos;
  os << endl;
  os << "Subtotal: " << subtotal << " €" << endl;
  os << "IVA (" << Factura::IVA << "%): " << impuestos << " €" << endl;
  os << "TOTAL: " << total << " €" << endl;

  return os;
}
