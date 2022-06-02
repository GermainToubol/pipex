/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_process_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:26:02 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/02 16:29:24 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "pipex.h"

int	do_read_bonus(char *filename, int *pipe_out, int *is_son, int here_doc)
{
	int		status;
	pid_t	pid;

	pipe(pipe_out);
	pid = fork();
	if (pid == 0)
	{
		*is_son = 1;
		if (here_doc == 0)
			return (pp_process_read(filename, pipe_out));
		return (pp_process_read_bonus(filename, pipe_out));
	}
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	waitpid(pid, &status, 0);
	return (status);
}

int	do_process(t_exec *cmd, int *pipe_in, int *pipe_out, int *is_son)
{
	int		status;
	pid_t	pid;

	pipe(pipe_out);
	pid = fork();
	if (pid == 0)
	{
		*is_son = 1;
		return (pp_process_exec(cmd, pipe_in, pipe_out));
	}
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	close(pipe_in[0]);
	close(pipe_in[1]);
	waitpid(pid, &status, 0);
	return (status);
}

int	do_write_bonus(char *filename, int *pipe_in, int *is_son, int here_doc)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		*is_son = 1;
		if (here_doc == 0)
			return (pp_process_write(filename, pipe_in));
		return (pp_process_write_bonus(filename, pipe_in));
	}
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	close(pipe_in[0]);
	close(pipe_in[1]);
	waitpid(pid, &status, 0);
	return (status);
}
