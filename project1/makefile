#set stdin to standart input method
in = &0

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

#use "make run in=<input_file>" to run from file
run: 
	./main 0<$(in)
