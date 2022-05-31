/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 09:31:16 by gtoubol           #+#    #+#             */
/*   Updated: 2022/05/31 17:53:16 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_H
# define PIPEX_H

char	*pp_fullname(char *name, char **path);
char	**pp_get_path(char **env);
int		pp_read_file(char *filename);
#endif
