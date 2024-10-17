# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -I/opt/homebrew/include/SDL2

# Linker flags
LDFLAGS = -L/opt/homebrew/lib -lSDL2 -lSDL2_image

# Source files excluding src/network/server/server.cpp
SRCS = $(filter-out src/network/server/server.cpp, $(wildcard src/*.cpp src/network/client/*.cpp src/game/*.cpp))

# Output executable name
TARGET = game

# Build target
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)

# Clean target
clean:
	rm -f $(TARGET)

.PHONY: all clean
