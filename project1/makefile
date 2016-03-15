compile: clear .o .exe clean

in=t02
out=files/$(in).out

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
	./main < files/$(in).in
	cat $(out)
	@echo
	
memcheck:
	valgrind --leak-check=full ./main < files/$(in).in
	cat $(out)
	@echo