/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 09:31:07 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/02 17:07:03 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdio.h>
#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	int		pfd[2][2];
	int		status;
	int		is_son;
	t_exec	args;

	if (argc != 5)
		return (0);
	is_son = 0;
	args.env = env;
	status = do_read(argv[1], pfd[0], &is_son);
	if (is_son == 0)
	{
		args.name = argv[2];
		status |= do_process(&args, pfd[0], pfd[1], &is_son);
	}
	if (is_son == 0)
	{
		args.name = argv[3];
		status |= do_process(&args, pfd[1], pfd[0], &is_son);
	}
	if (is_son == 0)
		status |= do_write(argv[4], pfd[0], &is_son);
	return (status);
}
