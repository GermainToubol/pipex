#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "pipex.h"
#include "libft.h"

int	pp_process_read_bonus(char *end_name, int *pipe_fd)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		if (pp_read_file_bonus(end_name) != 0)
		{
			perror("pipex: here_doc");
			return (1);
		}
		close(pipe_fd[1]);
		return (7);
	}
	else if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	status = 0;
	wait(&status);
	return (0);
}
