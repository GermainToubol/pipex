/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_process_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:26:02 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/06 13:02:27 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "pipex.h"
#include "libft.h"

int ft_close(int *fd)
{
	int i;

	if (*fd != 0)
		i = close(*fd);
	*fd = 0;
	return (i);
}

int	do_read_bonus(char *filename, int *pipe_out, int *is_son, int here_doc)
{
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
	ft_fprintf(2, "read: %d\n", (int)pid);
	return (pid);
}

int	do_process(t_exec *cmd, int *pipe_in, int *pipe_out, int *is_son)
{
	pid_t	pid;

	pipe(pipe_out);
	pid = fork();
	if (pid == 0)
	{
		if ((pipe_in - 2)[0] != 0)
			ft_close((pipe_in - 2));
		if ((pipe_in - 2)[1] != 0)
			ft_close(pipe_in - 1);
		close(pipe_out[0]);
		*is_son = 1;
		return (pp_process_exec(cmd, pipe_in, pipe_out));
	}
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	ft_fprintf(2, "exec: %d\n", (int)pid);
	return (pid);
}

int	do_write_bonus(char *filename, int *pipe_in, int *is_son, int here_doc)
{
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
	ft_fprintf(2, "write: %d\n", (int)pid);
	return (pid);
}
