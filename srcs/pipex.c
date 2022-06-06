/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:31:02 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/06 17:36:38 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <sys/wait.h>
#include <unistd.h>
#include "pipex.h"

int main(int argc, char **argv, char **env)
{
	int	pfd[3][2];
	int	is_son;
	t_exec cmd;
	int status;

	if (argc != 5)
		return (0);
	cmd.env = env;
	pipe(pfd[0]);
	is_son = pp_process_read(argv[1], pfd[0]);
	if (is_son == 0)
	{
		pipe(pfd[1]);
		cmd.name = argv[2];
		is_son = pp_process_exec(&cmd, pfd[0], pfd[1]);
		close(pfd[0][0]);
		close(pfd[0][1]);
	}
	if (is_son == 0)
	{
		pipe(pfd[2]);
		cmd.name = argv[3];
		is_son = pp_process_exec(&cmd, pfd[1], pfd[2]);
		close(pfd[1][0]);
		close(pfd[1][1]);
	}
	if (is_son == 0)
	{
		is_son = pp_process_write(argv[4], pfd[2]);
		close(pfd[2][0]);
		close(pfd[2][1]);
	}
	if (is_son == 0)
	{
		for (int i = 0; i < 4; i++)
		{
			status = 0;
			wait(&status);
			status = 0;
		}
	}
	return (0);
}
