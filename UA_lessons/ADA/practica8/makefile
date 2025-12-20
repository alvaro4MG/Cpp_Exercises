#Álvaro Martínez García, 48150407E
OPTS = -Wall -g -O3 -std=c++0x

met_bt: met_bt.cc
	g++ ${OPTS} -o met_bt met_bt.cc

met1: met_bt met.BT_test_files/07n03m.p
	./met_bt -f met.BT_test_files/07n03m.p

met2: met_bt met.BT_test_files/10n02m.p
	./met_bt -f met.BT_test_files/10n02m.p

met3: met_bt met.BT_test_files/10n05m.p
	./met_bt -f met.BT_test_files/10n05m.p

met4: met_bt met.BT_test_files/20n05m.p
	./met_bt -f met.BT_test_files/20n05m.p

met5: met_bt met.BT_test_files/20n10m.p
	./met_bt -f met.BT_test_files/20n10m.p

met6: met_bt met.BT_test_files/20n15m.p
	./met_bt -f met.BT_test_files/20n15m.p

met7: met_bt met.BT_test_files/30n12m.p
	./met_bt -f met.BT_test_files/30n12m.p

met8: met_bt met.BT_test_files/30n26m.p
	./met_bt -f met.BT_test_files/30n26m.p

met9: met_bt met.BT_test_files/40n05m.p
	./met_bt -f met.BT_test_files/40n05m.p

met10: met_bt met.BT_test_files/40n10m.p
	./met_bt -f met.BT_test_files/40n10m.p
 

tar: met_bt.cc makefile
	tar cvfz 48150407E.tar.gz met_bt.cc makefile

misalida: met_bt met.BT_test_files/07n03m.p
	./met_bt -f met.BT_test_files/07n03m.p >misalida

compare: misalida met.BT_test_files/07n03m.p.sol
	diff -b misalida met.BT_test_files/07n03m.p.sol

clean: 
	rm met_bt *~
 
