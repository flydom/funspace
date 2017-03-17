#include <stdio.h> 



int main()
{
	int res = 0;
	pid_t pid;
	char child_tty[64] = {0};
	struct termios save;
	
	tcgetattr(parent_fd, &termsave);

	if ((pid = vfork()) < 0)
	{
		printf("vfork process failed.\n");
		res = -1;
	}
	else if (pid == 0)	
	{
		int errno = 0;
		int child_fd = -1;
		cosnt char *argv[];		
		struct termios termbuf;

		setsid();	

		signal(SIGCHLD, SIG_DFL);
		signal(SIGPIPE, SIG_DFL);

		child_fd = open(parent_tty, O_RDWR | );
		if (child_fd < 0) 
		{
			errno = errnoGet();
			printf("open %s failed! errno: %d.\n", child_tty, errno);
			exit(errno);
		}

		dup2(child_fd, 0);
		dup2(child_fd, 1);
		dup2(child_fd, 2);
		while (fd > 2)
		{
			close(fd--);
		}	

		tcsetpgrp(0, getpid());
		
		// get default termbuf
		termbuf.c_lflag |= ECHO;
		termbuf.c_oflag |= ONLCR | XTABS;
		termbuf.c_iflag |= ICRNL;
		termbuf.c_iflag &= ~IXOFF;
		tcsetattr(child_fd, TCSANOW, &termbuf);

		argv[0] = "sh";
		argv[1] = "-c";
		argv[2] = cmd;
		argv[3] = NULL;

		if (execvp("/bin/sh", (char **)argv) < 0)
		{
			errno = errnoGet();
			printf("fail to execve %s! errno: %d.\n", cmd, errno);
			exit(errno);
		}
		else
		{
			exit(0);
		}

	}
	else
	{
		if (pid != waitpid(pid, &res, 0))	
		{
			printf("fail to wait linux command [%s]! errno: %d.\n", cmd, errnoGet());
		}	
	}
	tcsetattr(parent_fd, TCSANOW, &save);
	
	return res;
}
