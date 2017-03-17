#---------------------------------------------------------
#
#              Make for demo
#
#---------------------------------------------------------
#---------------------------------------------------------
# tool chain define
#---------------------------------------------------------
# CROSS_COMPILE ?=  xxx-linux-gnu-
CROSS_COMPILE ?=
CC = $(CROSS_COMPILE)gcc
CXX = $(CROSS_COMPILE)g++
AR = $(CROSS_COMPILE)ar
LD = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy


#---------------------------------------------------------
# shell command 
#---------------------------------------------------------
ECHO = @echo
MKDIR = mkdir -p
MV = @mv -r
RM = @rm -rf
MAKE = make -j

#---------------------------------------------------------
# complier flags
# v for make debug 
#---------------------------------------------------------
V ?= 
ARFLAGS =  rcs
CFLAGS = $(V) -g 
LDFLAGS = -static


#---------------------------------------------------------
# link libs 
#---------------------------------------------------------
LIBS = -ln -lrt -lpthread -lutil







