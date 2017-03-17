#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define MAX_INPUT_LINE_SIZE 256

typedef int (*pcmd_func)(void);

typedef struct {
    char *name;
    char *addr;
    int type;
    int size;
    int section;
    int bind;
} SYMBOL_ENT;

extern SYMBOL_ENT dbg_symtbl[];
extern unsigned long dbg_symtbl_size; 


extern void xcon_print(char* fmt, ...);


int xcon_input_line(const char *const prompt, char *buf);




