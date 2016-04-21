target=src
#target=submission/

in=t03
out=files/output/$(in).out

files=src/Header.h src/Edge.h src/Node.h src/Edge.cpp src/Node.cpp src/Graph.h src/BHeap.h src/Dijkstra.h src/BellmanFord.h src/Johnson.h src/main.cpp

all: clean .o .exe clean

.o:
	g++ -ansi -pedantic -Wall -c $(target)/Edge.cpp
	g++ -ansi -pedantic -Wall -c $(target)/Node.cpp
	g++ -ansi -pedantic -Wall -c $(target)/main.cpp

.exe: 
	g++ -o main Edge.o Node.o main.o
	@rm -f *.o

clean:
	@rm -f *.o
	@rm -f main
	@rm -f app

release:
	g++ -ansi -pedantic -Wall -c $(target)/al095_p2.cpp
	g++ -o main al095_p2.o
	@rm -f al095_p2.o

run:
	./main < files/input/$(in).in
	
memcheck:
	valgrind --leak-check=full ./main < files/input/$(in).in
	cat $(out)
	@echo

	
test:
	./tests.sh

merge:
	./utils/merge src/al095_p2.cpp ${files}

other:
	for file in files/input/*.in; do \
		echo $$file ; \
		time ./main < $$file > trash.txt ; \
		echo "\n"; \
	done
