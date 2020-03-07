appexe : movement/bike-movement.o graphic/bike.o graphic/enemy.o utils/calculus.o utils/textTools.o utils/timerTools.o view/start-menu.o view/game.o view/navigation.o view/end-game.o linked-list/shot-list.o main.o
	gcc -g movement/bike-movement.o graphic/bike.o graphic/enemy.o utils/calculus.o utils/textTools.o utils/timerTools.o view/start-menu.o view/game.o view/navigation.o view/end-game.o linked-list/shot-list.o main.o -o appexe -lglut -lGLU -lGL 
movement/bike-movement.o: movement/bike-movement.c
	gcc -g -c movement/bike-movement.c -o movement/bike-movement.o -Wall -std=c99
graphic/bike.o: graphic/bike.c movement/bike-movement.h linked-list/shot-list.h
	gcc -g -c graphic/bike.c -o graphic/bike.o -Wall -std=c99
graphic/ennemy.o: graphic/enemy.c
	gcc -g -c graphic/enemy.c -o graphic/enemy.o -Wall -std=c99
utils/calculus.o : utils/calculus.c
	gcc -g -c utils/calculus.c -o utils/calculus.o -Wall -std=c99
utils/textTools.o : utils/textTools.c graphic/bike.h
	gcc -g -c utils/textTools.c -o utils/textTools.o -Wall -std=c99
utils/timerTools.o : utils/timerTools.c
	gcc -g -c utils/timerTools.c -o utils/timerTools.o -Wall -std=c99
view/navigation.o : view/navigation.c 
	gcc -g -c view/navigation.c -o view/navigation.o -Wall -std=c99
view/end-game.o : view/end-game.c graphic/enemy.h graphic/bike.h
	gcc -g -c view/end-game.c -o view/end-game.o -Wall -std=c99
view/game.o : view/game.c graphic/enemy.h graphic/bike.h movement/bike-movement.h utils/calculus.h utils/textTools.h utils/timerTools.h linked-list/shot-list.h
	gcc -g -c view/game.c -o view/game.o -Wall -std=c99
view/start-menu.o : view/start-menu.c graphic/bike.h utils/textTools.h
	gcc -g -c view/start-menu.c -o view/start-menu.o -Wall -std=c99
linked-list/shot-list.o : linked-list/shot-list.c 
	gcc -g -c linked-list/shot-list.c -o linked-list/shot-list.o -Wall -std=c99
main.o: main.c view/game.h view/start-menu.h view/navigation.h view/end-game.h
	gcc -g -c main.c -Wall -std=c99
clean:
	rm -rf *.o
mrproper: clean
	rm -rf appexe