all: test

CFLAGS = -g -O2

test: test.o mystrlib.o 

	cc -o shell test.o mystrlib.o
	
clean: 

	rm -f *.o test test.exe

demo: test
	./test