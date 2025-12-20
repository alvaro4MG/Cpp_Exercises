#Álvaro Martínez García, 48150407E
OPTS = -Wall -g -O3 -std=c++0x

all: pow2 pow2.CPUtimes graphs

pow2: pow2.cc
	g++ ${OPTS} -o pow2 pow2.cc	 

pow2.CPUtimes: pow2
	./pow2 > pow2.CPUtimes

graphs: pow2.CPUtimes pow2.gnuplot
	gnuplot pow2.gnuplot

tar: pow2.cc pow2.gnuplot makefile
	tar cvfz 48150407E.tar.gz pow2.cc pow2.gnuplot makefile

clean: 
	rm pow2 pow2.CPUtimes fit.log pow2*.png *~
 
