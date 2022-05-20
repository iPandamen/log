
TARGET_NAMES = examples/main

# PROJECT

PROJECT_ROOT_DIR = ${PWD}

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

MAIN_SRCS = ./examples/main.c
MAIN_OBJS = $(MAIN_SRCS:.c=.o)

C_SRCS += $(wildcard ./src/core/*.c) \
					$(wildcard ./src/port/*.c) 

C_OBJS = $(patsubst %.c, %.o, ${C_SRCS})

C_FLAGS +=
					

C_LIBS += -L. \
					
.PHONY: all before_build after_build release clean ${TARGET_NAMES}

all: before_build default after_build 

before_build: 
	@echo "====> ${@}"
	@echo PROJECT_ROOT_DIR: ${PROJECT_ROOT_DIR}
	@echo MAIN_SRCS: ${MAIN_SRCS}
	@echo MAIN_OBJS: ${MAIN_OBJS}
	@echo C_SRCS: ${C_SRCS}
	@echo C_OBJS: ${C_OBJS}
	@echo C_LIBS: ${C_LIBS}
	@echo C_FLAGS: ${C_FLAGS}
	@echo VPATH: ${VPATH}

after_build: 
	@echo ""
	@echo "====> ${@}"

default: ${TARGET_NAMES}

release: ${TARGET_NAMES}
	strip ${TARGET_NAMES} 

${TARGET_NAMES}: ${MAIN_OBJS} ${C_OBJS}
	@echo ""
	@echo "====> ${@} "
	${CC} -o $@ $^ ${C_FLAGS} 



%.o: %.c
	${CC} ${C_FLAGS} -c $< -o $@ 

clean:
	${RM} ${TARGET_NAMES}
	${RM} *.o
	${RM} ${C_OBJS}

