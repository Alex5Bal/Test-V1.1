all: test

CFLAGS = -g -O2

test: test.o mytoc.o mystrlib.o

	gcc -o test test.o mytoc.o mystrlib.o
	
clean: 

	rm -f *.o test test.exe

demo: test
	./test