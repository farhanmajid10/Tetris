CXX = g++
CXXFLAGS = -Isrc -Isrc/include -Isrc2/include -Ic:/include/harfbuzz -std=c++14

SRCS = main.cpp src/Board.cpp src/Game.cpp src/GameStateManager.cpp src/GameOverState.cpp src/PausedState.cpp src/PlayingState.cpp src/Renderer.cpp src/StartMenuState.cpp src/Pieces.cpp src/HighScores.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = tetris

LIBS = -Lsrc/lib -Lsrc2/lib -Lc:/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lharfbuzz

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LIBS)

clean:
	rm -f $(OBJS) $(TARGET)
