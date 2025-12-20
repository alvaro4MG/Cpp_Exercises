#Álvaro Martínez García, 48150407E
OPTS = -Wall -g -O3 -std=c++0x

met_greedy: met_greedy.cc
	g++ ${OPTS} -o met_greedy met_greedy.cc

met1: met_greedy met.Greedy_test_files/07n-01m.p
	./met_greedy -f met.Greedy_test_files/07n-01m.p

tar: met_greedy.cc makefile
	tar cvfz 48150407E.tar.gz met_greedy.cc makefile

misalida: met_greedy met.Greedy_test_files/07n-01m.p
	./met_greedy -f met.Greedy_test_files/07n-01m.p >misalida

compare: misalida met.Greedy_test_files/07n-01m.p.sol
	diff -b misalida met.Greedy_test_files/07n-01m.p.sol

clean: 
	rm met_greedy *~
 
