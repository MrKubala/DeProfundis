CC = g++
CFlags = -I ./include -std=c++11
LDFlags = -L ./lib  -lSOIL -lglfw3dll -lglew32 -lglew32.dll -lopengl32
DEBUG =

SourcesFiles = main_cube.cpp ShaderProgram.cpp GLFWControls.cpp ProgramArguments.cpp Texture.cpp Camera.cpp InputProcessor.cpp Mesh.cpp
ExecutableName = DeProfundis

ObjectDir = obj/
SourceDir = src/
BinDir = bin/

ObjectsFiles=$(SourcesFiles:.cpp=.o)
SOURCES=$(addprefix $(SourceDir),$(SourcesFiles))
OBJECTS=$(addprefix $(ObjectDir),$(ObjectsFiles))
EXECUTABLE=$(addprefix $(BinDir),$(ExecutableName))

all: $(SOURCES) $(EXECUTABLE)

run: all
ifeq ($(DEBUG), -g)
	gdb $(EXECUTABLE)
else
	$(EXECUTABLE)
endif

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFlags) $(DEBUG)

$(ObjectDir)%.o: $(SourceDir)%.cpp
	$(CC) -c -o $@ $< $(CFlags) $(DEBUG)

.PHONY: all run clean

clean:
	rm -f $(OBJECTS)