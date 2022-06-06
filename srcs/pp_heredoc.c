#include "libft.h"
#include "pipex.h"

int	pp_heredoc(char *arg, int *here_doc)
{
	*here_doc = 0;
	if (ft_strcmp(arg, "here_doc") == 0)
		*here_doc = 1;
	return (0);
}
