/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_process_read.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:51:18 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/06 18:51:21 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include "pipex.h"
#include "libft.h"

int	pp_process_read(char *filename, int *pipe_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		if (pp_read_file(filename) != 0)
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
