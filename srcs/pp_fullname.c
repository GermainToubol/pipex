/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_fullname.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 09:34:20 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/01 17:37:32 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "pipex.h"

static char	**pp_available_path(char *name, char **path);

/* Check for the right path of the given exec file.							*/
/* Path should be formated as {"", "/bin/", ..., NULL}						*/

char	*pp_fullname(char *name, char **path)
{
	char	**fullnames;
	int		i;
	char	*fullname;

	fullnames = pp_available_path(name, path);
	if (fullnames == NULL || fullnames[0] == NULL)
		return (NULL);
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
