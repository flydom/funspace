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

export CC LD

ECHO = @echo
MKDIR = mkdir -p
RM = @rm -rf

export ECHO MKDIR RM

# ---------------------------------------------------------------------------
# Compiler dir_env define
# ---------------------------------------------------------------------------
TOP_DIR := $(shell pwd)
BUILD_DIR := $(TOP_DIR)/build
BIN_DIR := $(BUILD_DIR)/bin
OBJS_DIR := $(BUILD_DIR)/objs
# Attempt to create a output target directory.
$(shell [ -d ${BUILD_DIR} ] || mkdir -p ${BUILD_DIR} && mkdir -p ${OBJS_DIR} && mkdir -p ${BIN_DIR})

export TOP_DIR OBJS_DIR

# ---------------------------------------------------------------------------
# OBJS include the necessary directories and the source files 
# ---------------------------------------------------------------------------
SUB_DIRS = public lib demo
ALL_OBJS = $(addprefix $(OBJS_DIR)/, $(addsuffix .o, $(SUB_DIRS)))

INCLUDE = -I$(TOP_DIR)/public/include \
          -I$(TOP_DIR)/lib/include \
          -I$(TOP_DIR)/demo/include

export INCLUDE 

CFLAGS = -g

.PHONY: all clean $(SUB_DIRS)

all: $(BIN_DIR)/demo_app

$(BIN_DIR)/demo_app: $(ALL_OBJS)
	$(ECHO) Build demo_prj start...
	$(CC) $(ALL_OBJS) -o $@
	$(ECHO) Done!!!

$(ALL_OBJS): $(SUB_DIRS)
$(SUB_DIRS):
	make -C $@

clean:
	$(RM) $(shell find ./ -name "*.o")
	$(RM) $(BIN_DIR)/demo_app
	$(ECHO) clean demo_prj over... 
