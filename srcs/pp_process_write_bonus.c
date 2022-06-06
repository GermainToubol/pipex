#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include "libft.h"
#include "pipex.h"

int	pp_process_write_bonus(char *filename, int *pipe_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		if (pp_write_file_append(filename) != 0)
		{
			perror(filename);
			return (1);
		}
		return (7);
	}
	else if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	return (0);
}
