in=bt
out=files/$(in).out

compile: clear .o .exe clean

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
	./main < files/$(in).in
	cat $(out)
	@echo
	
memcheck:
	valgrind --leak-check=full ./main < files/$(in).in
	cat $(out)
	@echo
	
	
sub:
	g++ -o app -O3 -ansi -Wall al095_p1.cpp -lm

run_sub:
	time ./app < files/$(in).in
	cat $(out)
	@echo