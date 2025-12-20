#Álvaro Martínez García, 48150407E
OPTS = -Wall -g -O3 -std=c++0x

qs-vs-hs: qs-vs-hs.cc
	g++ ${OPTS} -o qs-vs-hs qs-vs-hs.cc	 

qs-vs-hs.Msteps: qs-vs-hs
	./qs-vs-hs > qs-vs-hs.Msteps

graphs: qs-vs-hs.Msteps qs-vs-hs.gnuplot
	gnuplot qs-vs-hs.gnuplot

all: qs-vs-hs qs-vs-hs.Msteps graphs

tar: qs-vs-hs.cc qs-vs-hs.gnuplot makefile
	tar cvfz 48150407E.tar.gz qs-vs-hs.cc qs-vs-hs.gnuplot makefile

clean: 
	rm qs-vs-hs qs-vs-hs.Msteps fit.log qs-vs-hs*.png *~
 
