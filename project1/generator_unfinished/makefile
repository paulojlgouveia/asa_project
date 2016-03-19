
compile: clear .o .exe clean

clear:
	@clear

.o:
	g++ -ansi -pedantic -Wall -c graph_generator.cpp

.exe: 
	g++ -o generator graph_generator.o

clean:
	@rm -f *.o
	@rm -f app

run:
	@for iterator in 0 1 2 3 4 ; \
		do ./generator < input/ve$$iterator > output/g$$iterator.in ; \
	done
	
	