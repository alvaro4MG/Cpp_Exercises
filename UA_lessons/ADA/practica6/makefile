#Álvaro Martínez García, 48150407E
OPTS = -Wall -g -O3 -std=c++0x

met: met.cc
	g++ ${OPTS} -o met met.cc

met0: met met.PD_test_files/0.problem
	./met -f met.PD_test_files/0.problem 

met1: met met.PD_test_files/1.problem
	./met -f met.PD_test_files/1.problem

tar: met.cc makefile
	tar cvfz 48150407E.tar.gz met.cc makefile

misalida: met met.PD_test_files/0.problem
	./met -f met.PD_test_files/0.problem >misalida

compare: misalida met.PD_test_files/0.problem.sol
	diff -b misalida met.PD_test_files/0.problem.sol

clean: 
	rm met *~
 
