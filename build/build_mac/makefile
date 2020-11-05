#Functions
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

#Source files and dependencies
SRC = $(call rwildcard,../../engine/src,*.cpp)
GAME_SRC = $(call rwildcard,../../game/src,*.cpp)
INCLUDE = -I../../game/headers -I../../engine/headers -I../../libs/libs_mac/SDL2.framework/Headers -I../../libs/libs_mac/SDL2_image.framework/Headers -I../../libs/libs_mac/SDL2_ttf.framework/Headers -I../../libs/libs_mac/SDL2_mixer.framework/Headers
LIBS = -F../../libs/libs_mac
LINK = -framework SDL2 -framework SDL2_image -framework SDL2_mixer -framework SDL2_ttf
FLAGS = -Wall -fdiagnostics-color=always

#Executeable name
OBJ_NAME = game

#Compilation command
build : $(SRC) $(GAME_SRC)
	g++ -std=c++17 $(SRC) $(GAME_SRC) $(INCLUDE) $(LIBS) $(LINK) $(FLAGS) -o $(OBJ_NAME)
	install_name_tool -add_rpath @executable_path/. game
	-rm -r res
	cp -r ../../res .
	find ./res -type f -name '*.aseprite' -exec rm {} +
	@echo "Build successful!"

debug : $(SRC)
	g++ -std=c++17 $(SRC) $(GAME_SRC) $(INCLUDE) $(LIBS) $(LINK) $(FLAGS) -g -o $(OBJ_NAME)
	install_name_tool -add_rpath @executable_path/. game
	-rm -r res
	cp -r ../../res .
	find ./res -type f -name '*.aseprite' -exec rm {} +
	@echo "Build successful!"

optimize : $(SRC)
	g++ -std=c++17 $(SRC) $(GAME_SRC) $(INCLUDE) $(LIBS) $(LINK) $(FLAGS) -O3 -o $(OBJ_NAME)
	install_name_tool -add_rpath @executable_path/. game
	-rm -r res
	cp -r ../../res .
	find ./res -type f -name '*.aseprite' -exec rm {} +
	@echo "Build successful!"
