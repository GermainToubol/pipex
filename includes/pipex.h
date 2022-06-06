/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:31:33 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/06 17:19:12 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_H
# define PIPEX_H

/*
 * Definition of the reading buffer size.
 */

# define R_BUFF_SIZE 4096

typedef struct s_exec
{
	char	*name;
	char	**env;
}	t_exec;

typedef struct s_status
{
	int	status;
	int	is_son;
}	t_status;

char	*pp_fullname(char *name, char **path);
char	**pp_get_path(char **env);
int		pp_read_file(char *filename);
int		pp_read_heredoc(char *end_name);
int		pp_write_file(char *filename);
int		pp_write_file_append(char *filename);
int		pp_process_exec(t_exec *cmd, int *pipe_in, int *pipe_out);
int		pp_process_read(char *filename, int *pipe_fd);
int		pp_process_write(char *filename, int *pipe_fd);
#endif
