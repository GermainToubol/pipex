/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:31:02 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/06 19:05:47 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <sys/wait.h>
#include <unistd.h>
#include "libft.h"
#include "pipex.h"

static int	pp_do_exec(int *pipe_in, int *pipe_out, t_exec *cmd, char *name);
static int	pp_wait_all(int is_son, int n);

int	main(int argc, char **argv, char **env)
{
	int		pfd[3][2];
	int		is_son;
	t_exec	cmd;

	if (argc != 5)
		return (0);
	cmd.env = env;
	pipe(pfd[0]);
	is_son = pp_process_read(argv[1], pfd[0]);
	if (is_son == 0)
		is_son = pp_do_exec(pfd[0], pfd[1], &cmd, argv[2]);
	if (is_son == 0)
		is_son = pp_do_exec(pfd[1], pfd[2], &cmd, argv[3]);
	if (is_son == 0)
	{
		is_son = pp_process_write(argv[4], pfd[2]);
		close(pfd[2][0]);
		close(pfd[2][1]);
	}
	return (pp_wait_all(is_son, argc - 1));
}

static int	pp_do_exec(int *pipe_in, int *pipe_out, t_exec *cmd, char *name)
{
	int	is_son;

	pipe(pipe_out);
	cmd->name = name;
	is_son = pp_process_exec(cmd, pipe_in, pipe_out);
	close(pipe_in[0]);
	close(pipe_in[1]);
	return (is_son);
}

static int	pp_wait_all(int is_son, int n)
{
	int	i;
	int	status;
	int	tmp;

	if (is_son != 0)
		return (is_son);
	i = 0;
	status = 0;
	while (i < n)
	{
		tmp = 0;
		wait(&tmp);
		if (tmp != 0)
			status |= tmp;
		i++;
	}
	return (status);
}
