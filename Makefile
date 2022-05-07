


TARGET_NAMES = examples/main

# PROJECT
PROJECT_ROOT_PATH = ${PWD}

# SUB_DIRS = ../n_lib/cJSON ../n_lib/x_string ../n_lib/x_log ../n_lib/x_protocol
# VPATH += ${SUB_DIRS} \

C_SOURCES =  ./x_log_core.c ./x_log.c ./x_assert.c

C_OBJECTS = $(patsubst %.c, %.o, ${C_SOURCES})

# compiler

# CC = arm-linux-gnueabihf-gcc
# CPP = arm-linux-gnueabihf-g++
# AR = arm-linux-gnueabihf-ar

CC = gcc

INCLUDE_PATHS += -I./

C_LIBS += -L. \
					-pthread
					
C_FLAGS =  -Wall -O2 -fPIC -std=gnu11 ${COM_FLAGS} ${INCLUDE_PATHS} ${C_LIBS} 

CPP_FLAGS = ${COM_FLAGS} -std=gnu++11


.PHONY: all before_build after_build debug release clean ${TARGET_NAMES}

all: before_build debug after_build 

before_build: 
	@echo "========> ${@}"

after_build: 
	@echo "========> ${@}"

debug: C_FLAGS+=-g

debug: ${TARGET_NAMES} 

release: ${TARGET_NAMES}

${TARGET_NAMES}: %: %.o ${C_OBJECTS}
	@echo "========> ${@}"
	${CC} -g -o $@ $^ ${C_FLAGS}

%.o: %.c
	${CC} -c -g -o $@ $^ ${C_FLAGS}

clean:
	${RM} ${TARGET_NAMES}
	${RM} *.o
	${RM} ${C_OBJECTS}

