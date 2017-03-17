include ../funcfg.mak


.PHONY: all clean

all: $(MKSYMTBL)
	@echo mksymtbl is ready...
	gcc -c xread.c -o xread.o
	readelf -s xread.o > readelf.txt
	$(MKSYMTBL) ./readelf.txt	
	gcc -c symtbl.c -o symtbl.o
	gcc -o xread xread.o symtbl.o

$(MKSYMTBL):
	make -C $(TOOLS_DIR)/readsym

clean:
	rm -rf xread *.o $(MKSYMTBL) symtbl.c readelf.txt



