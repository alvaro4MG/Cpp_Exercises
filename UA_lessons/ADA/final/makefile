#Álvaro Martínez García, 48150407E
OPTS = -Wall -g -O3 -std=c++0x

met_bb: met_bb.cc
	g++ ${OPTS} -o met_bb met_bb.cc

met1: met_bb met.BB_test_files/07n03m.p
	./met_bb -f met.BB_test_files/07n03m.p

met2: met_bb met.BB_test_files/10n02m.p
	./met_bb -f met.BB_test_files/10n02m.p

met3: met_bb met.BB_test_files/10n05m.p
	./met_bb -f met.BB_test_files/10n05m.p

met4: met_bb met.BB_test_files/20n05m.p
	./met_bb -f met.BB_test_files/20n05m.p

met5: met_bb met.BB_test_files/20n10m.p
	./met_bb -f met.BB_test_files/20n10m.p

met6: met_bb met.BB_test_files/20n15m.p
	./met_bb -f met.BB_test_files/20n15m.p

met7: met_bb met.BB_test_files/30n12m.p
	./met_bb -f met.BB_test_files/30n12m.p

met8: met_bb met.BB_test_files/30n26m.p
	./met_bb -f met.BB_test_files/30n26m.p

met9: met_bb met.BB_test_files/40n05m.p
	./met_bb -f met.BB_test_files/40n05m.p

met10: met_bb met.BB_test_files/40n10m.p
	./met_bb -f met.BB_test_files/40n10m.p
 

tar: met_bb.cc makefile
	tar cvfz 48150407E.tar.gz met_bb.cc makefile

misalida: met_bb met.BB_test_files/07n03m.p
	./met_bb -f met.BB_test_files/07n03m.p >misalida

compare: misalida met.BB_test_files/07n03m.p.sol
	diff -b misalida met.BB_test_files/07n03m.p.sol

clean: 
	rm met_bb *~
 
