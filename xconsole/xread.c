#include "xread.h"

char g_cmdbuf[MAX_INPUT_LINE_SIZE] = {0};

int DBG_JustForTest()
{
	printf("This is just for dbg_test.\n");
	return 0;
}

static void xcon_do_syscmd()
{
	unsigned int cmdlen= 0;

	while (1)
	{
		cmdlen = xcon_input_line("sys->", g_cmdbuf);
		if (cmdlen > 1 && g_cmdbuf[cmdlen - 1] == '\0')
		{
			if (strcmp(g_cmdbuf, "exit") == 0 ||
				strcmp(g_cmdbuf, "quit") == 0)
			{
				break;	
			}	

			system(g_cmdbuf);
		}
	}

	return;
}

static void xcon_do_dbgcmd(char *cmd)
{
	int index = 0;

	for (index = 0; index < dbg_symtbl_size; index++)
	{
		if (0 == strncmp(cmd, dbg_symtbl[index].name, strlen(cmd)))
		{
			(*(pcmd_func)(dbg_symtbl[index].addr))();
			printf("\tDone!\n");
			break;
		}	
	}

	if (index == dbg_symtbl_size)
	{
		printf("There is no this dbgcmd.\n");	
	}

	return;
}

static int xcon_read_cmd(const char *const prompt, char *cmdbuf, unsigned int *len)
{
	char ichar;
	char *tempchar = cmdbuf;

	while (1)	
	{
		(*len)++;
		fflush(stdout);
		ichar = getchar();
		if (ichar == '\n') break;
		*tempchar++ = ichar;
	}

	//printf("xcond_read_cmd: %s...\n", cmdbuf);
	return 0;
}

int xcon_input_line(const char *const prompt, char *buf)
{
	int res = 0;
	unsigned int len = 0;
	char *p = buf;

	memset(p, 0, MAX_INPUT_LINE_SIZE);
	fputs(prompt, stdout);

	res = xcon_read_cmd(prompt, p, &len);
	//printf("xcon_input_line: %s, %d...\n", p, len);
	return res < 0 ? res : len;
}

int main()
{
	unsigned int cmdlen= 0;
	
	while (1)
	{	
		cmdlen = xcon_input_line("xcon->", g_cmdbuf);
		if (cmdlen > 1 && g_cmdbuf[cmdlen - 1] == '\0')
		{
			//printf("input: %s, %d...\n", g_cmdbuf, cmdlen);
			if (strcmp(g_cmdbuf, "quit") == 0)
			{
				break;
			}
			else if (strcmp(g_cmdbuf, "sys") == 0)
			{
			//	printf("syscmd: %s...\n", g_cmdbuf);
				xcon_do_syscmd();
			}
			else if (strcmp(g_cmdbuf, "exec") == 0)
			{
				// to do dbg_exec
			}
			else
			{
			//	printf("dbgcmd: %s...\n", g_cmdbuf);
				xcon_do_dbgcmd(g_cmdbuf);
			}
		}
	}

	printf("xcon done...\n");

	return 0;
}


