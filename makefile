appexe : movement/square.o main.o
	gcc -g movement/square.o main.o -o appexe -lglut -lGLU -lGL
movement/square.o: movement/square.c
	gcc -g -c movement/square.c -Wall -std=c99
main.o: main.c movement/square.h
	gcc -g -c main.c -Wall -std=c99
clean:
	rm -rf *.o
mrproper: clean
	rm -rf appexe