/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 09:31:16 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/01 16:39:17 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_H
# define PIPEX_H

char	*pp_fullname(char *name, char **path);
char	**pp_get_path(char **env);
int		pp_read_file(char *filename);
int		pp_read_file_bonus(char *end_name);
int		pp_write_file_bonus(char *filename);
int		pp_write_file(char *filename);
int		pp_process_read(char *filename, int *pipe_fd);
int		pp_process_write(char *filename, int *pipe_fd);
int		pp_process_read_bonus(char *filename, int *pipe_fd);
int		pp_process_write_bonus(char *filename, int *pipe_fd);
int		pp_process_exec(char *name, int *pipe_in, int *pipe_out);
int		do_read(char *filename, int *pipe_out, int *is_son);
int		do_read_bonus(char *filename, int *pipe_out, int *is_son, int here_doc);
int		do_process(char *execfile, int *pipe_in, int *pipe_out, int *is_son);
int		do_write(char *filename, int *pipe_in, int *is_son);
int		do_write_bonus(char *filename, int *pipe_in, int *is_son, int here_doc);

#endif
