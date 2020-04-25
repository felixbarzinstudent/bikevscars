CC=gcc

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
FLAGGLUT=-lglut -lGL -lGLU -lm -ldl
endif
ifeq ($(UNAME_S),Darwin)
FLAGGLUT=-Wno-deprecated-declarations -framework OpenGL -framework GLUT
endif

FLAG=-Wall -std=c99
SRCS=movement/bike-movement.c graphic/bike.c utils/calculus.c utils/text-tools.c utils/timer-tools.c view/start-menu.c view/game.c view/navigation.c view/end-game.c linked-list/shot-list.c graphic/enemy.c linked-list/enemy-list.c records/save.c linked-list/enemy-shot-list.c utils/image-loader.c graphic/obstacle.c main.c
SRCS2=bike-movement.c bike.c calculus.c text-tools.c timer-tools.c start-menu.c game.c navigation.c end-game.c shot-list.c enemy.c enemy-list.c save.c enemy-shot-list.c image-loader.c obstacle.c main.c
OBJET = $(SRCS2:.c=.o)
EXEC= batailleEtoiles

all: $(EXEC)

$(EXEC): $(SRCS)
	$(CC) -c $(SRCS) $(FLAG) $(FLAGGLUT)
	$(CC) -o $(EXEC) $(OBJET) $(FLAG) $(FLAGGLUT)
	
clean:
	rm -rf $(EXEC)
	rm -rf *.o