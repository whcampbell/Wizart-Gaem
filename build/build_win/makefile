#Functions
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

#Source files and dependencies
SRC = $(call rwildcard,../../src,*.cpp)
INCLUDE = -I../../headers -I../../libs/libs_win/include/SDL2 
LIBS = -L../../libs/libs_win/lib
LINK = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
FLAGS = -Wall -fdiagnostics-color=always

#Executeable name
OBJ_NAME = game

#Compilation command
all : $(SRC)
	g++ -std=c++17 $(SRC) $(INCLUDE) $(LIBS) $(LINK) $(FLAGS) -o $(OBJ_NAME)
	-rm -r res
	cp -r ../../res .
	find ./res -type f -name '*.aseprite' -exec rm {} +
	@echo "Build successful!"