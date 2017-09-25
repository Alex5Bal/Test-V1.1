all: test

CFLAGS = -g -O2

test: test.o mystrlib.o 

	cc -o test test.o mystrlib.o
	
clean: 

	rm -f *.o test test.exe

demo: test
	./test