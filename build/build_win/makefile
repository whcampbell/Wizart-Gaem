#Functions
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

#Source files and dependencies
SRC = $(call rwildcard,../../src,*.cpp)
INCLUDE = -I../../headers -I../../libs/libs_win/include 
LIBS = -L../../libs/libs_win/lib
LINK = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer

#Executeable name
OBJ_NAME = game

#Compilation command
all : $(SRC)
	g++ $(SRC) $(INCLUDE) $(LIBS) -w -Wl,-subsystem,windows $(LINK) -o $(OBJ_NAME)