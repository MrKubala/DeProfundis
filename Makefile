CC = g++
CFlags = -I ./include -std=c++11
LDFlags = -L ./lib -lglfw3dll -lopengl32 -lglew32

SourcesFiles = main.cpp Shader.cpp
ExecutableName = DeProfundis

ObjectDir = obj/
SourceDir = src/
BinDir = bin/

ObjectsFiles=$(SourcesFiles:.cpp=.o)
SOURCES=$(addprefix $(SourceDir),$(SourcesFiles))
OBJECTS=$(addprefix $(ObjectDir),$(ObjectsFiles))
EXECUTABLE=$(addprefix $(BinDir),$(ExecutableName))

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFlags)

$(ObjectDir)%.o: $(SourceDir)%.cpp
	$(CC) -c -o $@ $< $(CFlags)

.PHONY: all clean

clean:
	rm -f $(OBJECTS)