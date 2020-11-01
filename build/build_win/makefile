#Functions
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

#Source files and dependencies
SRC = $(call rwildcard,../../engine/src,*.cpp)
GAME_SRC = $(call rwildcard,../../game/src,*.cpp)
INCLUDE = -I../../game/headers -I../../engine/headers -I../../libs/libs_win/include/SDL2 
LIBS = -L../../libs/libs_win/lib
LINK = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
FLAGS = -Wall -fdiagnostics-color=always -static-libgcc -static-libstdc++

#Executeable name
OBJ_NAME = game

#Compilation command
build : $(SRC)
	g++ -std=c++17 $(SRC) $(GAME_SRC) $(INCLUDE) $(LIBS) $(LINK) $(FLAGS) -o $(OBJ_NAME)
	-rm -r res
	cp -r ../../res .
	find ./res -type f -name '*.aseprite' -exec rm {} +
	@echo "Build successful!"

debug : $(SRC)
	g++ -std=c++17 $(SRC) $(GAME_SRC) $(INCLUDE) $(LIBS) $(LINK) $(FLAGS) -g -o $(OBJ_NAME)
	-rm -r res
	cp -r ../../res .
	find ./res -type f -name '*.aseprite' -exec rm {} +
	@echo "Build successful!"

optimize : $(SRC)
	g++ -std=c++17 $(SRC) $(GAME_SRC) $(INCLUDE) $(LIBS) $(LINK) $(FLAGS) -O3 -o $(OBJ_NAME)
	-rm -r res
	cp -r ../../res .
	find ./res -type f -name '*.aseprite' -exec rm {} +
	@echo "Build successful!"