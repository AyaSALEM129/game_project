play:play.o main.o 
	gcc main.o play.o -o prog -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -g
main.o:main.c
	gcc -c main.c -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -g
play.o:play.c
	gcc -c play.c -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -g

