appexe : movement/square.o graphic/enemy.o utils/calculus.o utils/textTools.o utils/timerTools.o view/start-menu.o view/game.o main.o
	gcc -g movement/square.o graphic/enemy.o utils/calculus.o utils/textTools.o utils/timerTools.o view/start-menu.o view/game.o main.o -o appexe -lglut -lGLU -lGL 
movement/square.o: movement/square.c
	gcc -g -c movement/square.c -o movement/square.o -Wall -std=c99
graphic/ennemy.o: graphic/enemy.c
	gcc -g -c graphic/enemy.c -o graphic/enemy.o -Wall -std=c99
utils/calculus.o : utils/calculus.c
	gcc -g -c utils/calculus.c -o utils/calculus.o -Wall -std=c99
utils/textTools.o : utils/textTools.c movement/square.h
	gcc -g -c utils/textTools.c -o utils/textTools.o -Wall -std=c99
utils/timerTools.o : utils/timerTools.c
	gcc -g -c utils/timerTools.c -o utils/timerTools.o -Wall -std=c99
view/game.o : view/game.c graphic/enemy.h movement/square.h utils/calculus.h utils/textTools.h utils/timerTools.h
	gcc -g -c view/game.c -o view/game.o -Wall -std=c99
view/start-menu.o : view/start-menu.c movement/square.h utils/textTools.h
	gcc -g -c view/start-menu.c -o view/start-menu.o -Wall -std=c99
main.o: main.c view/game.h view/start-menu.h
	gcc -g -c main.c -Wall -std=c99
clean:
	rm -rf *.o
mrproper: clean
	rm -rf appexe