ej2: main.o Calendar.o Event.o
	g++ -Wall -std=c++11 main.o Calendar.o Event.o -o ej2

main.o: main.cc Calendar.h Event.h
	g++ -Wall -std=c++11 -c main.cc

Calendar.o: Calendar.cc Calendar.h Event.h
	g++ -Wall -std=c++11 -c Calendar.cc

Event.o: Event.cc Event.h
	g++ -Wall -std=c++11 -c Event.cc

clean:
	rm -f ej2 *.o
