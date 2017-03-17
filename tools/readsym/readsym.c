#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
	FILE *in_fp = NULL;
	FILE *out_fp = NULL;
	char strline[1024] = {0};
	char s_s[1024] = {0};
	char *p = NULL;
	int real_symb_num = 0;

	if (argc != 2)
	{
		printf("mksymtbl readelf.\n");
		return 0;
	}

	if ((in_fp = fopen(argv[1], "r")) == NULL)
	{
		printf("Error, first open elf file failed.\n");
		return -1;
	}

	out_fp = fopen("./symtbl.c", "w+");
	if (out_fp == NULL)
	{
	    printf("Error, open symtbl.c failed.\n");
		return -1;	
	}

	while (!feof(in_fp))
	{
		fgets(strline, 1024, in_fp);
		if (strstr(strline, " FUNC ") && 
			strstr(strline, " GLOBAL ") && 
			strstr(strline, "DBG") &&
			!strstr(strline, "@"))
		{
			if (strline[strlen(strline) - 1] == '\n')
				strline[strlen(strline) - 1] = '\0';
			
			p = &strline[strlen(strline) - 1];
			while ((*p != ' ') && (p > strline)) p--;

			p++;

			sprintf(s_s, "extern int %s();\n", p);
			fputs(s_s, out_fp);

		}
	}
	fclose(in_fp);
	
	if ((in_fp = fopen(argv[1], "r")) == NULL)
	{
		printf("Error, second open elf file failed.\n");
		return -1;
	}

	fputs("\n\n", out_fp);
	fputs("typedef struct {\n", out_fp);
	fputs("    char *name;\n", out_fp);
	fputs("    char *addr;\n", out_fp);
	fputs("    int type;\n", out_fp);
	fputs("    int size;\n", out_fp);
	fputs("    int section;\n", out_fp);
	fputs("    int bind;\n", out_fp);
	fputs("} SYMBOL_ENT;\n", out_fp);
	fputs("\n\n", out_fp);
	fputs("SYMBOL_ENT dbg_symtbl[] = \n", out_fp);
	fputs("{\n", out_fp);
	
	while (!feof(in_fp))
	{
		fgets(strline, 1024, in_fp);
		if (strstr(strline, " FUNC ") && 
			strstr(strline, " GLOBAL ") && 
			strstr(strline, "DBG") &&
			!strstr(strline, "@"))
		{
			if (strline[strlen(strline) - 1] == '\n')
				strline[strlen(strline) - 1] = '\0';
			
			p = &strline[strlen(strline) - 1];
			while ((*p != ' ') && (p > strline)) p--;

			p++;

			sprintf(s_s, "{\"%s\", \t(char *)&%s, \t2, \t0x0, \t1, \t1},\n", p, p);
			fputs(s_s, out_fp);

			real_symb_num++;
		}
	}
	fputs("};\n\n", out_fp);

	sprintf(s_s, "unsigned long dbg_symtbl_size = %d; \n", real_symb_num);
	fputs(s_s, out_fp);

	fclose(in_fp);
	return 0;
}

