#################################################
##
##	GLHL linux  makefile
##		Author: Pablo Ramon Soria
##		Date:	2014-10-25
##
#################################################

release ?= false

APP_NAME 		= libGLHL.so

CXX = g++

CXX_FLAGS_BASE 		= -fPIC -std=c++11 -Wall -Werror -shared
CXX_RELEASE_FLAGS 	= -O3
CXX_DEBUG_FLAGS 	= -g

SRC_FILES 		:= $(shell find ./../../src/ -name '*.cpp')
OBJ_FILES 		:= $(patsubst %.cpp, %.o, $(SRC_FILES))

INCLUDE_DIR		=	-I/usr/include/SOIL -I./
LIB_DIR			=
DEPENDENCIES		= -lSOIL -lX11 -lGL -lGLU -lGLEW

ifeq ($(release), false)
	CXX_FLAGS = $(CXX_FLAGS_BASE) $(CXX_DEBUG_FLAGS)
endif
ifeq ($(release), true)
	CXX_FLAGS = $(CXX_FLAGS_BASE) $(CXX_RELEASE_FLAGS)
endif

all: rebuild

rebuild: clean build

move2system:
	sudo mv libGLHL.so /usr/lib

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
