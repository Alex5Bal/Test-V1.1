all: shell

CFLAGS = -g -O2

shell: mystrlib.o mytoc.o shell.o

	cc -o shell mystrlib.o mytoc.o shell.o
	
clean: 

	rm -f *.o shell shell.exe

demo: shell
	./shell