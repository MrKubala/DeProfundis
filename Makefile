ExecutableName = DeProfundis

build: main.cpp
	g++ -o ./bin/$(ExecutableName).exe main.cpp ./lib/glfw3dll.a -I ./include -L ./lib -lglfw3 -lopengl32

run: ./bin/$(ExecutableName).exe
	./bin/$(ExecutableName)

clean:
	cd .
	cd bin
	dir