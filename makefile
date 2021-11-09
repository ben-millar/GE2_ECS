# Compiler to use
CC              := g++

# Name for the produced executeable
EXE_NAME		:= ECS

# SDL compiler and lib flags
SDL_CFLAGS      := $(shell sdl2-config --cflags)
SDL_LDFLAGS     := $(shell sdl2-config --libs) -lSDL2_image -lSDL2_ttf

# SFML lib flags
#SFML_LDFLAGS    := -lsfml-graphics -lsfml-window -lsfml-system

# C Compiler Flags
CFLAGS          := -g #Generate debugging information

# C++ Compiler Flags
CXXFLAGS        := -I. -I./include $(SDL_CFLAGS) $(SDL_LDFLAGS)

# Temporary object file directory
OBJ_DIR         := ./bin

# Searches for all cpp files inside the src folder (non-recursive)
SRC_FILES       := $(wildcard src/*.cpp)

# Modifies extension on all cpps to object files
OBJ_FILES       := $(patsubst %.cpp, %.o, $(SRC_FILES))

# Changes from ./src to whatever the OBJ_DIR is 
# *Should be commented out if there's nested cpp folders (nesting cpp folders means obj file gets placed \
# with the cpp for at the minute - hopefully will be tuned soon*
OBJ_TARGET      := $(foreach obj,$(OBJ_FILES), $(lastword $(subst /, $(OBJ_DIR)/,$(obj))))

# Add more /* if more folders are nested
NESTED_CPP      := ./src/*.o ./src/**/*.o 
OBJ_FOLDER      := $(OBJ_DIR)/*.o

# For every object file, find the cpp and create an object file for it in OBJ_DIR
$(OBJ_DIR)/%.o : ./src/%.cpp
	@echo $(SRC_FILES)
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< $(CXXFLAGS) -o $@

# Change OBJ_TARGET to OBJ_FILES if there is nested cpp folders (CURRENTLY THE WAY TO WORK WITH NESTED CPP's)
# whatever follows build: needs to be placed after $@ too
build: $(OBJ_TARGET)
	$(CC) $(CFLAGS) -o $(EXE_NAME) $(OBJ_TARGET) $(CXXFLAGS)
	./$(EXE_NAME)
	
.PHONY: clean

# Change the variable depending on if you used a nested folder or not
clean:
	rm -f $(OBJ_FOLDER)