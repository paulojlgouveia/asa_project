target=src
#target=submission/

in=3
out=files/output/$(in).out

files=src/Header.hpp src/Solution.hpp src/Node.hpp src/Graph.hpp src/Search.hpp src/main.cpp

all: clean .o .exe clean

.o:
	g++ -ansi -pedantic -Wall -c $(target)/Edge.cpp
	g++ -ansi -pedantic -Wall -c $(target)/Node.cpp
	g++ -ansi -pedantic -Wall -c $(target)/Graph.cpp
# 	g++ -ansi -pedantic -Wall -c $(target)/Dijkstra.cpp
	g++ -ansi -pedantic -Wall -c $(target)/main.cpp

.exe: 
	g++ -o main Edge.o Node.o Graph.o main.o
	@rm -f *.o

clean:
	@rm -f *.o
	@rm -f main
	@rm -f app

run: 
	./main < files/input/$(in).in
	cat $(out)
	@echo
	
memcheck:
	valgrind --leak-check=full ./main < files/input/$(in).in
	cat $(out)
	@echo

	
test:
	./tests.sh

merge:
	./utils/merge src/al095_p1.cpp ${files}

other:
	for file in files/input/*.in; do \
		echo $$file ; \
		time ./main < $$file > trash.txt ; \
		echo "\n"; \
	done
