#include <stddef.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "libft.h"
#include "pipex.h"

static int	pp_do_read(int *pipe_out, char *filename, int here_doc,
				char *end_name);
static int	pp_do_exec(int *pipe_in, int *pipe_out, t_exec *cmd, char *name);
static int	pp_do_write(int *pipe_in, char *filename, int here_doc);
static int	pp_wait_all(int is_son, int n);

int	main(int argc, char **argv, char **env)
{
	int		*pfd;
	int		is_son;
	t_exec	cmd;
	int		here_doc;
	int		i;

	if ((argc < 5) || (pp_heredoc(argv[1], &here_doc) == 1 && argc < 6))
		return (0);
	cmd.env = env;
	i = 1 + here_doc;
	pfd = ft_calloc(2 * argc, sizeof(*pfd));
	if (pfd == NULL)
		return (1);
	is_son = pp_do_read(pfd + 2 * i, argv[i], here_doc, argv[i]);
	while (is_son == 0 && ++i < argc - 1)
		is_son = pp_do_exec(pfd + 2 * i - 2, pfd + 2 * i, &cmd, argv[i]);
	if (is_son == 0)
		is_son = pp_do_write(pfd + 2 * i - 2, argv[i], here_doc);
	free(pfd);
	return (pp_wait_all(is_son, argc - 1 - here_doc));
}

static int	pp_do_read(int *pipe_out, char *filename, int here_doc, char *end_name)
{
	int is_son;

	pipe(pipe_out);
	if (here_doc == 0)
		is_son = pp_process_read(filename, pipe_out);
	else
		is_son = pp_process_read_bonus(end_name, pipe_out);
	return (is_son);
}

static int	pp_do_exec(int *pipe_in, int *pipe_out, t_exec *cmd, char *name)
{
	int	is_son;

	pipe(pipe_out);
	cmd->name = name;
	is_son = pp_process_exec(cmd, pipe_in, pipe_out);
	close(pipe_in[0]);
	close(pipe_in[1]);
	return (is_son);
}

static int	pp_do_write(int *pipe_in, char *filename, int here_doc)
{
	int	is_son;

	if (here_doc == 0)
		is_son = pp_process_write(filename, pipe_in);
	else
		is_son = pp_process_write_bonus(filename, pipe_in);
	close(pipe_in[0]);
	close(pipe_in[1]);
	return (is_son);
}

static int	pp_wait_all(int is_son, int n)
{
	int	i;
	int	status;
	int	tmp;

	if (is_son != 0)
		return (is_son);
	i = 0;
	status = 0;
	while (i < n)
	{
		tmp = 0;
		wait(&tmp);
		if (tmp != 0)
			status |= tmp;
		i++;
	}
	return (status);
}
