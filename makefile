build:
	g++ -std=c++17 src/*.cpp -o bin/luna -Wall -lSDL2

run:
	./bin/luna

clear:
	rm bin/luna