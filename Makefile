# Makefile for Snake Game

# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude # Basic flags, C++17 standard, include dir
LDFLAGS = -Llib # Basic linker flags, lib dir
LDLIBS = -lraylib -lm -lpthread -ldl -lrt -lX11 # Raylib dependencies (Linux example, adjust for your OS)
# For MacOS, LDLIBS might be: -lraylib -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL
# For Windows (MinGW), LDLIBS might be: -lraylib -lopengl32 -lgdi32 -lwinmm

# Set paths for Raylib (ADJUST THESE if raylib is not installed system-wide)
# Example: If Raylib source is in ../raylib/raylib-5.0
# RAYLIB_PATH = ../raylib/raylib-5.0/src
# CXXFLAGS += -I$(RAYLIB_PATH)
# LDFLAGS += -L$(RAYLIB_PATH) # If you compiled raylib locally
# Or if installed via package manager, paths might be /usr/local/include, /usr/local/lib etc.
# Check your Raylib installation instructions!
# Example for standard Linux install:
CXXFLAGS += -I/usr/local/include
LDFLAGS += -L/usr/local/lib


# Source directory
SRC_DIR = src

# Source files (find all .cpp files in src directory)
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Object files (replace .cpp with .o and put in an 'obj' directory)
OBJ_DIR = obj
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Executable name
EXEC = snake_game

# --- Targets ---

# Default target: build the executable
all: $(EXEC)

# Link the executable from object files
$(EXEC): $(OBJS)
	@echo "Linking $@..."
	$(CXX) $(LDFLAGS) $^ -o $@ $(LDLIBS)
	@echo "Build complete: $(EXEC)"

# Compile source files into object files
# Create obj directory if it doesn't exist (-p suppresses errors if it exists)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(wildcard $(SRC_DIR)/*.hpp) | $(OBJ_DIR)
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to create the object directory
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Target to run the game
run: $(EXEC)
	@echo "Running $(EXEC)..."
	./$(EXEC)

# Target to clean up build files
clean:
	@echo "Cleaning up..."
	rm -rf $(OBJ_DIR) $(EXEC)
	@echo "Cleanup complete."

# Phony targets are not actual files
.PHONY: all run clean

# Optional: Prevent Make from deleting intermediate object files
.SECONDARY: $(OBJS)
