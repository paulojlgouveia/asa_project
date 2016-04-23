target=src
#target=submission/

in=t06
out=files/output/$(in).out

files=src/Header.h src/Edge.h src/Node.h src/Edge.cpp src/Node.cpp src/Graph.h src/BHeap.h src/Solution.h src/Dijkstra.h src/BellmanFord.h src/Johnson.h src/main.cpp

all: clean .o .exe clean

.o:
	g++ -ansi -pedantic -Wall -O3 -lm -c $(target)/Edge.cpp
	g++ -ansi -pedantic -Wall -O3 -lm -c $(target)/Node.cpp
	g++ -ansi -pedantic -Wall -O3 -lm -c $(target)/main.cpp

.exe:
	g++ -o main Edge.o Node.o main.o
	@rm -f *.o

clean:
	@rm -f *.o
	@rm -f main
	@rm -f app
	@rm -f massif.out.*

release:
	g++ -ansi -pedantic -Wall -O3 -lm -c $(target)/al095_p2.cpp
	g++ -o main al095_p2.o
	@rm -f al095_p2.o

run:
	@for FILE in 1 2 3 4 t01 t02 t03 t04 t05 t06; do \
		./main < files/input/$$FILE.in ; \
		cat files/expected/$$FILE.out ; \
		echo; \
	done
	
memcheck:
	@rm -f massif.out.*
	valgrind --leak-check=full ./main < files/input/$(in).in
	valgrind --tool=massif ./main < files/input/$(in).in
	ms_print massif.out.*
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
