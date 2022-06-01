/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_process_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:44:20 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/01 13:10:18 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "pipex.h"

static int	pp_set_args(char *name, char ***paths, char ***args,
				char **fullname);

/*
 * Find the exec of the given process and exec it in the right place.
 *
 */

int	pp_process_exec(char *name, int *pipe_in, int *pipe_out)
{
	char		**paths;
	char		**args;
	char		*fullname;
	extern char	**environ;

	close(pipe_in[1]);
	close(pipe_out[0]);
	dup2(pipe_in[0], STDIN_FILENO);
	dup2(pipe_out[1], STDOUT_FILENO);
	if (pp_set_args(name, &paths, &args, &fullname) != 0)
		return (1);
	execve(fullname, args, environ);
	perror(args[0]);
	free(fullname);
	ft_free_split(paths);
	ft_free_split(args);
	return (1);
}

static int	pp_set_args(char *name, char ***paths, char ***args,
				char **fullname)
{
	extern char	**environ;

	*paths = pp_get_path(environ);
	if (*paths == NULL)
		return (1);
	*args = ft_split(name, ' ');
	if (*args == NULL)
	{
		ft_free_split(*paths);
		return (1);
	}
	*fullname = pp_fullname((*args)[0], *paths);
	if (*fullname == NULL)
	{
		perror(name);
		ft_free_split(*paths);
		ft_free_split(*args);
		return (1);
	}
	return (0);
}
