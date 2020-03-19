appexe : movement/bike-movement.o graphic/bike.o utils/calculus.o utils/text-tools.o utils/timerTools.o view/start-menu.o view/game.o view/navigation.o view/end-game.o linked-list/shot-list.o graphic/enemy.o linked-list/enemy-list.o records/save.o linked-list/enemy-shot-list.o utils/image-loader.o main.o
	gcc -g movement/bike-movement.o graphic/bike.o utils/calculus.o utils/text-tools.o utils/timerTools.o view/start-menu.o view/game.o view/navigation.o view/end-game.o linked-list/shot-list.o graphic/enemy.o linked-list/enemy-list.o records/save.o linked-list/enemy-shot-list.o utils/image-loader.o main.o -o appexe -lglut -lGLU -lGL -lm -ldl
movement/bike-movement.o: movement/bike-movement.c
	gcc -g -c movement/bike-movement.c -o movement/bike-movement.o -Wall -std=c99
graphic/bike.o: graphic/bike.c movement/bike-movement.h linked-list/shot-list.h
	gcc -g -c graphic/bike.c -o graphic/bike.o -Wall -std=c99
graphic/enemy.o: graphic/enemy.c 
	gcc -g -c graphic/enemy.c -o graphic/enemy.o -Wall -std=c99
utils/calculus.o : utils/calculus.c
	gcc -g -c utils/calculus.c -o utils/calculus.o -Wall -std=c99
utils/text-tools.o : utils/text-tools.c graphic/bike.h
	gcc -g -c utils/text-tools.c -o utils/text-tools.o -Wall -std=c99
utils/timerTools.o : utils/timerTools.c
	gcc -g -c utils/timerTools.c -o utils/timerTools.o -Wall -std=c99
utils/image-loader.o : utils/image-loader.c
	gcc -g -c utils/image-loader.c -o utils/image-loader.o -Wall -std=c99
view/navigation.o : view/navigation.c 
	gcc -g -c view/navigation.c -o view/navigation.o -Wall -std=c99
view/end-game.o : view/end-game.c graphic/enemy.h graphic/bike.h
	gcc -g -c view/end-game.c -o view/end-game.o -Wall -std=c99
view/game.o : view/game.c graphic/bike.h movement/bike-movement.h utils/calculus.h utils/text-tools.h utils/timerTools.h linked-list/shot-list.h graphic/enemy.h linked-list/enemy-list.h utils/timerTools.h linked-list/enemy-shot-list.h utils/image-loader.h
	gcc -g -c view/game.c -o view/game.o -Wall -std=c99
view/start-menu.o : view/start-menu.c graphic/bike.h utils/text-tools.h
	gcc -g -c view/start-menu.c -o view/start-menu.o -Wall -std=c99
linked-list/enemy-list.o : linked-list/enemy-list.c utils/timerTools.h
	gcc -g -c linked-list/enemy-list.c -o linked-list/enemy-list.o -Wall -std=c99
linked-list/shot-list.o : linked-list/shot-list.c 
	gcc -g -c linked-list/shot-list.c -o linked-list/shot-list.o -Wall -std=c99
linked-list/enemy-shot-list.o : linked-list/enemy-shot-list.c 
	gcc -g -c linked-list/enemy-shot-list.c -o linked-list/enemy-shot-list.o -Wall -std=c99
records/save.o : records/save.c 
	gcc -g -c records/save.c -o records/save.o -Wall -std=c99
main.o: main.c view/game.h view/start-menu.h view/navigation.h view/end-game.h lib/stb_image.h
	gcc -g -c main.c -Wall -std=c99
clean:
	rm -rf *.o
mrproper: clean
	rm -rf appexe