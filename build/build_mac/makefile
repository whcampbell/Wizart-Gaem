#Functions
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

#Source files and dependencies
SRC = $(call rwildcard,../../src,*.cpp)
INCLUDE = -I../../headers -I../../libs/libs_mac/SDL2.framework/Headers
LIBS = -F../../libs/libs_mac
LINK = -framework SDL2 #-framework SDL2main -framework SDL2_image -framework SDL2_mixer

#Executeable name
OBJ_NAME = game

#Compilation command
all : $(SRC)
	g++ -std=c++17 $(SRC) $(INCLUDE) $(LIBS) $(LINK) -Wall -o $(OBJ_NAME)
	-rm -r res
	cp -r ../../res .