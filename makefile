build:
	gcc -std=c99 src/*.c -lSDL2 -Wall -o bin/luna 

run:
	./bin/luna

clear:
	rm bin/luna