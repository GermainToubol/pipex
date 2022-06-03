/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:09:17 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/03 16:48:58 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include "libft.h"
#include "pipex.h"
#include <sys/wait.h>

static int	pp_init_main(t_status *status, t_exec *cmd,
				char **env, char **argv);
static int	pp_wait(t_status *status, int n_process);

int	main(int argc, char **argv, char **env)
{
	int			pfd[2][2];
	t_status	status;
	t_exec		cmd;
	int			i;
	int			here_doc;

	if (argc < 5 || (ft_strcmp(argv[1], "here_doc") == 0 && argc < 6))
		return (0);
	i = pp_init_main(&status, &cmd, env, argv);
	here_doc = i - 1;
	status.status = do_read_bonus(argv[i], pfd[i % 2],
			&(status.is_son), here_doc);
	i++;
	while (status.is_son == 0 && i < argc - 1)
	{
		cmd.name = argv[i];
		status.status = do_process(&cmd, pfd[(i - 1) % 2],
				pfd[i % 2], &(status.is_son));
		i++;
	}
	if (status.is_son == 0)
		status.status = do_write_bonus(argv[i], pfd[(i - 1) % 2],
				&(status.is_son), here_doc);
	return (pp_wait(&status, argc - 1 - here_doc));
}

static int	pp_wait(t_status *status, int n_process)
{
	int	i;
	int tmp;

	if (status->is_son != 0)
		return (status->status);
	i = 0;
	while (i < n_process)
	{
		wait(&tmp);
		status->status |= tmp;
		i++;
	}
	return (status->status);
}

static int	pp_init_main(t_status *status, t_exec *cmd,
				char **env, char **argv)
{
	status->is_son = 0;
	cmd->env = env;
	if (ft_strcmp(argv[1], "here_doc") == 0)
		return (2);
	return (1);
}
