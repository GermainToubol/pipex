/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 13:36:54 by gtoubol           #+#    #+#             */
/*   Updated: 2022/05/31 14:00:16 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include "libft.h"
#include "pipex.h"

static char	**pp_path_split(char *path);
/*
 * extract the PATH from the environ variable and convert it to a NULL
 * terminated list of available pathes.
 *
 */

char	**pp_get_path(char **env)
{
	int		i;
	char	*path_env;
	char	**local_path;

	i = 0;
	path_env = "";
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path_env = env[i];
			break ;
		}
		i++;
	}
	if (path_env == NULL)
		return (NULL);
	local_path = pp_path_split();
	return (local_path);
}

static char	**pp_path_split(char *path)
{
	char	**tmp;
	int		i;

	if (path[0] == '\0')
	{
		tmp = ft_calloc(2, sizeof(*tmp));
		if (tmp == NULL)
			return (NULL);
		tmp[0] = ft_strdup("");
		tmp[1] = NULL;
		if (tmp[0] == NULL)
		{
			free(tmp);
			return (NULL);
		}
		return (tmp);
	}
	tmp = ft_split(path + 5, ':');
	if (tmp == NULL)
		return (NULL);
	return (tmp);
}
