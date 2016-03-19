target=src/
#target=submission/

in=t01
out=files/output/$(in).out

files=src/Header.hpp src/Solution.hpp src/Node.hpp src/Graph.hpp src/Search.hpp src/main.cpp

compile: clear merge .o .exe clean

clear:
	@clear

.o:
	g++ -ansi -pedantic -Wall -c $(target)/al095_p1.cpp

.exe: 
	g++ -o main al095_p1.o

clean:
	@rm -f *.o
	@rm -f app

run: 
	./main < files/input/$(in).in
	cat $(out)
	@echo
	
memcheck:
	valgrind --leak-check=full ./main < files/$(in).in
	cat $(out)
	@echo
		
generate:
	python graph_generator.py
	
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
