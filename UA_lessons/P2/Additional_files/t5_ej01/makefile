OPTS=-Wall -g -std=c++11
OBJS=Coordenada.o principal.o
CC=g++

principal : $(OBJS)
	$(CC) $(OPTS) $(OBJS) -o principal

Coordenada.o : Coordenada.cc Coordenada.h
	$(CC) $(OPTS) -c Coordenada.cc

principal.o : principal.cc Coordenada.h
	$(CC) $(OPTS) -c principal.cc
