 
make: clear .o .exe clean run

clear:
	@clear

.o:
	g++ -ansi -pedantic -Wall -c main.cpp

.exe: 
	g++ -o main main.o

clean:
	@rm -f *.o
	@rm -f app
run:
	@./main
