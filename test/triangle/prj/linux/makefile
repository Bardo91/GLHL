#################################################
##
##	GLHL makefile
##		Author: Pablo Ramon Soria
##		Date:	2014-10-25
##
#################################################

APP_NAME 	= triangle


CXX = g++
CXX_FLAGS 	= -std=c++11 -O3 -Wall -Werror

SRC_FILES 	:= $(shell find ./../../src/ -name '*.cpp')
OBJ_FILES 	:= $(patsubst %.cpp, %.o, $(SRC_FILES))

INCLUDE_DIR	:=	-I/usr/include/SOIL -I../../../../library
LIB_DIR		:=	-L../../../../library/prj/linux
DEPENDENCIES	:= -lSOIL -lGLHL -lX11 -lGL -lGLU -lGLEW


all: rebuild

run: 
	./loadTexture

rebuild: clean build

clean:
	rm -f $(OBJ_FILES)

build:	$(OBJ_FILES)
	@echo "----------------------------------------------"
	$(CXX) -o $(APP_NAME) $^ $(INCLUDE_DIR) $(LIB_DIR) $(DEPENDENCIES) 

%.o: %.cpp
	@echo "----------------------------------------------"
	echo "Compiling: " $^
	$(CXX) $(CXX_FLAGS) -c $^ -o $@ $(INCLUDE_DIR) $(LIB_DIR) $(DEPENDENCIES) 
