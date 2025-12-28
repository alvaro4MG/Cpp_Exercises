OPTS=-Wall -g -std=c++11
OBJS=Cliente.o Linea.o Factura.o principal.o
CC=g++

principal : $(OBJS)
	$(CC) $(OPTS) $(OBJS) -o principal

Cliente.o : Cliente.cc Cliente.h
	$(CC) $(OPTS) -c Cliente.cc

Linea.o : Linea.cc Linea.h
	$(CC) $(OPTS) -c Linea.cc

Factura.o : Factura.cc Factura.h Cliente.h Linea.h
	$(CC) $(OPTS) -c Factura.cc

principal.o : principal.cc Factura.h
	$(CC) $(OPTS) -c principal.cc
