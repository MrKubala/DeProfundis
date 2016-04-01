Name = DeProfundis
ExecutableName = $(Name).exe

build: ./bin/$(ExecutableName)

./bin/$(ExecutableName) : main.cpp
	g++ -o bin/$(ExecutableName) main.cpp -I ./include -L ./lib -lglfw3dll -lopengl32

run: ./bin/$(ExecutableName)
	./bin/$(ExecutableName)

clean:
	cd bin
	dir