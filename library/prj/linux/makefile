#################################################
##
##	GLHL makefile
##		Author: Pablo Ramon Soria
##		Date:	2014-10-25
##
#################################################

APP_NAME 	= libGLHL.so


CXX = g++
CXX_FLAGS 	= -fPIC -std=c++11 -O3 -Wall -Werror -shared

SRC_FILES 	:= $(shell find ./../../src/ -name '*.cpp')
OBJ_FILES 	:= $(patsubst %.cpp, %.o, $(SRC_FILES))

INCLUDE_DIR	:=	-I/usr/include/SOIL -I./
LIB_DIR		:=
DEPENDENCIES	:= -lSOIL -lX11 -lGL -lGLU -lGLEW

all: rebuild

rebuild: clean build

clean:
	rm -f $(OBJ_FILES) libGLHL.so

build:	$(OBJ_FILES)
	@echo "--------------------------------------"
	$(CXX) $(CXX_FLAGS) -o $(APP_NAME) $^ $(INCLUDE_DIR) $(LIB_DIR) $(DEPENDENCIES)

%.o: %.cpp
	@echo "--------------------------------------"
	@echo "Compiling: " $^
	$(CXX) $(CXX_FLAGS) -c $^ -o $@ $(INCLUDE_DIR) $(LIB_DIR) $(DEPENDENCIES)


########## PHONY ##########
.PHONY: all clean run