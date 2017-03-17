MODULE = lib
SUB_SRCS_DIR = $(TOP_DIR)/$(MODULE)/source
SUB_OBJS_DIR = $(OBJS_DIR)/$(MODULE)

INCLUDE += 

SUB_ALL_SRCS := $(notdir $(wildcard $(SUB_SRCS_DIR)/*.c))
SUB_TMP_OBJS := $(SUB_ALL_SRCS:.c=.o)
SUB_ALL_OBJS := $(addprefix $(SUB_OBJS_DIR)/, $(SUB_TMP_OBJS))

all: $(OBJS_DIR)/$(MODULE).o

$(OBJS_DIR)/$(MODULE).o: $(SUB_ALL_OBJS)
	$(ECHO) Linking $(MODULE).o...
	$(LD) -r -o $@ $(SUB_ALL_OBJS)

$(SUB_OBJS_DIR)/%.o: $(SUB_SRCS_DIR)/%.c
	$(ECHO) Compiling $(notdir $<)...
	$(shell [ -d $(SUB_OBJS_DIR) ] || mkdir -p $(SUB_OBJS_DIR))   
	$(CC) $(INCLUDE) $(CFLAGS) -c -o $@ $<
