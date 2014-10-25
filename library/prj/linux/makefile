#################################################
##
##	GLHL makefile
##		Author: Pablo Ramon Soria
##		Date:	2014-10-25
##
#################################################

APP_NAME 	= libGLHL.so


CXX = g++
CXX_FLAGS 	= -std=c++11 -shared -O3 -Wall -Werror

SRC_FILES 	:= $(shell find ./../source/ -name '*.cpp')
OBJ_FILES 	:= $(patsubst %.cpp, %.o, $(SRC_FILES))

INCLUDE_DIR	:=
LIB_DIR		:=
DEPENDENCIES	:=


all:

rebuild:

clean:
	rm -f $(OBJ_FILES)

build:	$(OBJ_FILES)
	$(CXX) $^ -o $(APP_NAME) $(INCLUDE_DIR) $(LIB_DIR) $(DEPENDENCIES)

run:


%.o: %.cpp
	$(CXX) $^ -o $@ $(INCLUDE_DIR) $(LIB_DIR) $(DEPENDENCIES) $(CXX_FLAGS)
