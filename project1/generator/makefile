
x = 14

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
	@rm -f ../files/input/*.bigger


runforall:
	@for file in ../files/input/*.in; do \
		./generator < $$file > $$file.bigger ; \
	done
	
run:
	./generator < ../files/input/t$(x).in > ../files/input/t$$(($(x)+1)).in
