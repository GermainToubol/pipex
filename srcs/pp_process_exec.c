/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_process_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:33:23 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/06 18:57:24 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "libft.h"
#include "pipex.h"

static int	pp_set_args(t_exec *cmd, char ***paths, char ***args,
				char **fullname);
static void	pp_check_name(char **args);
static int	pp_cleanup(int *pipe_in, int *pipe_out, char **paths, char **args);

int	pp_process_exec(t_exec *cmd, int *pipe_in, int *pipe_out)
{
	char	**paths;
	char	**args;
	char	*fullname;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(pipe_in[1]);
		close(pipe_out[0]);
		dup2(pipe_in[0], STDIN_FILENO);
		dup2(pipe_out[1], STDOUT_FILENO);
		if (pp_set_args(cmd, &paths, &args, &fullname) != 0)
			return (1);
		execve(fullname, args, cmd->env);
		perror(args[0]);
		free(fullname);
		return (pp_cleanup(pipe_in, pipe_out, paths, args));
	}
	else if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	return (0);
}

static int	pp_cleanup(int *pipe_in, int *pipe_out, char **paths, char **args)
{
	close(pipe_in[0]);
	close(pipe_out[1]);
	ft_free_split(paths);
	ft_free_split(args);
	return (2);
}

static void	pp_check_name(char **args)
{
	if (args != NULL)
	{
		ft_free_split(args);
		errno = EINVAL;
	}
}

static int	pp_set_args(t_exec *cmd, char ***paths, char ***args,
				char **fullname)
{
	*paths = pp_get_path(cmd->env);
	if (*paths == NULL)
		return (1);
	*args = ft_split(cmd->name, ' ');
	if (*args == NULL || (*args)[0] == NULL)
	{
		pp_check_name(*args);
		ft_free_split(*paths);
		perror("pipex");
		return (1);
	}
	*fullname = pp_fullname((*args)[0], *paths);
	if (*fullname == NULL)
	{
		perror(cmd->name);
		ft_free_split(*paths);
		ft_free_split(*args);
		return (1);
	}
	return (0);
}
