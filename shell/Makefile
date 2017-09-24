all: shell

CFLAGS = -g -O2

shell: mytoc.o mystrlib.o shell.o

	cc -o shell mytoc.o mystrlib.o shell.o
	
clean: 

	rm -f *.o shell shell.exe

demo: shell
	./shell