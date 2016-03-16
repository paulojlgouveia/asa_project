test_in=files/t02
test_out=$(test_in).out

merge_in=Graph.hpp main.cpp
merge_out=al095.cpp


compile: clear .o .exe clean

clear:
	@clear

.o:
	g++ -ansi -pedantic -Wall -c main.cpp -std=c++11

.exe: 
	g++ -o main main.o -std=c++11

clean:
	@rm -f *.o
	@rm -f app

run: 
	./main < $(test_in).in
	cat $(test_out)
	@echo
	
memcheck:
	valgrind --leak-check=full ./main < $(test_in).in
	cat $(test_out)
	@echo
	
merge:
	./utils/merge $(merge_out) $(merge_in)
