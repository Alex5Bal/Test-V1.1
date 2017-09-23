all: test

CFLAGS = -g -O2

test: test.o mystrlib.o mytoc.o 

	gcc -o test test.o mystrlib.o mytoc.o 
	
clean: 

	rm -f *.o test test.exe

demo: test
	./test