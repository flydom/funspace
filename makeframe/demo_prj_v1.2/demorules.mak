include $(TOP_DIR)/democfg.mak


SUB_ALL_SRCS := $(notdir $(wildcard $(SUB_SRCS_DIR)/*.c))
SUB_TMP_OBJS := $(SUB_ALL_SRCS:.c=.o)
SUB_ALL_OBJS := $(addprefix $(SUB_OBJS_DIR)/, $(SUB_TMP_OBJS))
SUB_ALL_DEPS := $(SUB_ALL_OBJS:.o=.d)

$(shell [ -d $(SUB_OBJS_DIR) ] || mkdir -p $(SUB_OBJS_DIR))   

all: $(OBJS_DIR)/$(MODULE).o

$(OBJS_DIR)/$(MODULE).o: $(SUB_ALL_OBJS) 
	$(ECHO) Linking $(MODULE).o...
	$(LD) -r -o $@ $(SUB_ALL_OBJS)

$(SUB_OBJS_DIR)/%.o: $(SUB_SRCS_DIR)/%.c $(SUB_ALL_DEPS)
	$(ECHO) Compiling $(notdir $<)...
	$(CC) $(INCLUDE) $(CFLAGS) -c -o $@ $<

$(SUB_OBJS_DIR)/%.d: $(SUB_SRCS_DIR)/%.c
	@set -e; rm -f $@; \
    $(CC) $(INCLUDE) -MM $(CFLGAS) $< > $@.$$$$; \
    sed 's,\($*\).o[ :]*,$(SUB_OBJS_DIR)/\1.o $@ :,g' < $@.$$$$ > $@; \
    rm -f $@.$$$$

-include $(SUB_ALL_DEPS)
