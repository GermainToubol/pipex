/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 09:31:07 by gtoubol           #+#    #+#             */
/*   Updated: 2022/05/31 17:43:23 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "pipex.h"
#include <unistd.h>

/*
 * 1. lire le fichier
 * 2. ecrire le fichier dans le pipe 0.
 * 3. exec de facon generale.
 *
 */

int	main(int argc, char **argv)
{
	char	*fullname;
	char	*name;
	char	**paths;
	extern char **environ;

	if (argc != 3)
		return (0);
	if (pp_read_file(argv[1]) != 0)
	{
		perror(argv[1]);
		return (1);
	}
	name = argv[2];
	paths = pp_get_path(environ);
	if (!paths)
		return (1);
	fullname = pp_fullname(name, paths);
	if (fullname == NULL)
		perror(name);
	else
	{
		ft_printf("%s\n", fullname);
	}
	free(fullname);
	return (0);
}
