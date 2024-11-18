build:
	gcc -std=c99 src/*.c -o bin/luna -Wall -lSDL2

run:
	./bin/luna

clear:
	rm bin/luna