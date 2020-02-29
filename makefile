appexe : movement/square.o graphic/enemy.o utils/calculus.o main.o
	gcc -g movement/square.o graphic/enemy.o utils/calculus.o main.o -o appexe -lglut -lGLU -lGL 
movement/square.o: movement/square.c
	gcc -g -c movement/square.c -o movement/square.o -Wall -std=c99
graphic/ennemy.o: graphic/enemy.c
	gcc -g -c graphic/enemy.c -o graphic/enemy.o -Wall -std=c99
utils/calculus.o : utils/calculus.c
	gcc -g -c utils/calculus.c -o utils/calculus.o -Wall -std=c99
main.o: main.c movement/square.h graphic/enemy.h
	gcc -g -c main.c -Wall -std=c99
clean:
	rm -rf *.o
mrproper: clean
	rm -rf appexe