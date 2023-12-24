build:
	g++ -Wall ./src/*.cpp -Ilib -o wordzer
run:
	./wordzer
clean:
	rm wordzer