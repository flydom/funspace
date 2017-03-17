# ---------------------------------------------------------------------------
#                        
#                           Make for demo
#                       
# ---------------------------------------------------------------------------
#SUB_DIRS = public lib demo
#ALL_SRCS = $(foreach dir, $(SUB_DIRS), $(wildcard $(dir)/*.c))
#ALL_OBJS = $(ALL_SRCS:.c=.o)
#
#INCLUDE = -I./public -I./lib -I./demo
#
#CFLAGS = -g
#
#.PHONY: all clean $(SUB_DIRS) 
#
#all: demo_app
#
#demo_app: $(ALL_OBJS)  
#	@echo Build demo_prj start...
#	gcc $(ALL_OBJS) -o $@
#	@echo Done!!!
#
#%.o: %.c
#	@echo "Compiling $<..."
#	gcc $(INCLUDE) $(CFLAGS) -c -o $@ $<
#
#clean:
#	@rm (shell find ./ -name "*.o")
#	@rm demo 
#	@echo Clean demo_prj over... 
#
#
# ---------------------------------------------------------------------------
#                        
#                           Make for demo
#                       
# ---------------------------------------------------------------------------
# CROSS_COMPILE ?=  xxx-linux-gnu-
CROSS_COMPILE ?=
CC = $(CROSS_COMPILE)gcc
CXX = $(CROSS_COMPILE)g++
AR = $(CROSS_COMPILE)ar
LD = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy

# ---------------------------------------------------------------------------
# Compiler dir_env define
# ---------------------------------------------------------------------------
TOP_DIR := $(shell pwd)
BUILD_DIR := $(TOP_DIR)/build
BIN_DIR := $(BUILD_DIR)/bin
OBJS_DIR := $(BUILD_DIR)/objs
# Attempt to create a output target directory.
$(shell [ -d ${BUILD_DIR} ] || mkdir -p ${BUILD_DIR} && mkdir -p ${OBJS_DIR} && mkdir -p ${BIN_DIR})

# ---------------------------------------------------------------------------
# OBJS include the necessary directories and the source files 
# ---------------------------------------------------------------------------
SUB_DIRS = public lib demo
ALL_SRCS = $(foreach dir, $(SUB_DIRS), $(wildcard $(dir)/*.c))
TMP_OBJS = $(notdir $(patsubst %.c, %.o, $(ALL_SRCS)))
ALL_OBJS = $(addprefix $(OBJS_DIR)/, $(TMP_OBJS))

INCLUDE = -I./public -I./lib -I./demo

CFLAGS = -g

.PHONY: all clean

all: $(BIN_DIR)/demo_app

$(BIN_DIR)/demo_app: $(ALL_OBJS)
	@echo Build demo_prj start...
	gcc $(ALL_OBJS) -o $@
	@echo Done!!!

$(ALL_OBJS): $(ALL_SRCS)
	@echo "Compiling $(filter %$(*F).c, $(ALL_SRCS))..."
	$(CC) $(INCLUDE) $(CFLAGS) -c -o $@ $(filter %$(*F).c, $(ALL_SRCS))

clean:
	rm $(shell find ./ -name "*.o")
	rm $(BIN_DIR)/demo_app
	@echo clean demo_prj over... 
