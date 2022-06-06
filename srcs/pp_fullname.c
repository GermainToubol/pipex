/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_fullname.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:35:43 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/06 17:45:03 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "pipex.h"

static char	**pp_available_path(char *name, char **path);

/*
 * Check for the right path of the given exec file.
 *
 * Path should be formated as {"", "/bin/", ..., NULL}.  The function
 * get the list of all available pathes and return the first
 * executable with the write name.
 *
 */

char	*pp_fullname(char *name, char **path)
{
	char	**fullnames;
	int		i;
	char	*fullname;

	fullnames = pp_available_path(name, path);
	if (fullnames == NULL || fullnames[0] == NULL)
		return (free(fullnames), NULL);
	i = 0;
	fullname = NULL;
	while (fullnames[i] != NULL)
	{
		if (access(fullnames[i], X_OK) == 0)
		{
			fullname = fullnames[i];
			i++;
			break ;
		}
		free(fullnames[i]);
		i++;
	}
	while (fullnames[i] != NULL)
		free(fullnames[i++]);
	free(fullnames);
	return (fullname);
}

static char	**pp_available_path(char *name, char **path)
{
	int		i;
	int		j;
	char	*fullname;
	char	**fullnames;

	i = 0;
	while (path[i] != NULL)
		i++;
	fullnames = ft_calloc(i + 1, sizeof(*fullnames));
	if (fullnames == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (path[i] != NULL && (name[0] != '.' || i == 0))
	{
		fullname = ft_strjoin(path[i], name);
		if (fullname != NULL && access(fullname, F_OK) == 0)
			fullnames[j++] = fullname;
		else
			free(fullname);
		i++;
	}
	return (fullnames);
}
