
TARGET_NAMES = examples/main

# PROJECT
PROJECT_CURRENT_PATH = ${PWD}

# compiler
ifeq (${ARHC},arm)
CC = arm-linux-gnueabihf-gcc
CPP = arm-linux-gnueabihf-g++
AR = arm-linux-gnueabihf-ar
else 
CC = gcc
endif

COM_FLAGS = -Wall -O2 -g
C_FLAGS   = $(COM_FLAGS) -std=c11
CPP_FLAGS = $(COM_FLAGS) -std=c++11

C_INCLUDES = -I./src/

C_SOURCES = $(wildcard ./src/*.c)

C_OBJECTS = $(patsubst %.c, %.o, ${C_SOURCES})

C_LIBS += -L. \
					
.PHONY: all before_build after_build debug release clean ${TARGET_NAMES}

all: before_build debug after_build 

before_build: 
	@echo "====> ${@}"
	@echo C_INCLUDES: ${C_INCLUDES}
	@echo C_SOURCES: ${C_SOURCES}
	@echo C_OBJECTS: ${C_OBJECTS}
	@echo C_LIBS: ${C_LIBS}

after_build: 
	@echo ""
	@echo "====> ${@}"

# debug: C_FLAGS+=-g
debug: ${TARGET_NAMES}

release: ${TARGET_NAMES}

${TARGET_NAMES}: %: %.o ${C_OBJECTS}
	@echo ""
	@echo "====> ${@} "
	${CC} -o $@ $^ ${C_FLAGS} ${C_INCLUDES}

%.o: %.c
	${CC} -c -o $@ $^ ${C_FLAGS} ${C_INCLUDES}

clean:
	${RM} ${TARGET_NAMES}
	${RM} *.o
	${RM} ${C_OBJECTS}

