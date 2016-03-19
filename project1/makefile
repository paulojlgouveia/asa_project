#target=src/
target=submission/

in=t04
out=files/output/$(in).out



compile: clear .o .exe clean

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
	for file in files/input/*.in; do \
		echo $$file ; \
		time ./main < $$file ; \
		echo "\n"; \
	done