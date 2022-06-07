/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_process_write.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:28:05 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/07 10:23:09 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include "libft.h"
#include "pipex.h"

int	pp_process_write(char *filename, int *pipe_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		if (pp_write_file(filename) != 0)
		{
			close(pipe_fd[0]);
			perror(filename);
			return (1);
		}
		close(pipe_fd[0]);
		return (7);
	}
	else if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	return (0);
}
