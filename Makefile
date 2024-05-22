CXX = g++
CXXFLAGS = -Isrc -Isrc/include -Isrc2/include -Ic:/include/harfbuzz -std=c++14
LDFLAGS = -Lsrc/lib -Lsrc2/lib -Lc:/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lharfbuzz

SOURCES = main.cpp src/Board.cpp src/Game.cpp src/GameStateManager.cpp src/GameOverState.cpp src/PausedState.cpp src/PlayingState.cpp src/Renderer.cpp src/StartMenuState.cpp src/Pieces.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = tetris

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
