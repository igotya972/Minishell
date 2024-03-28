#include "../../includes/minishell.h"

void	ft_add_history(char *input)
{
	static char	*old_input;


	if (input[0] && !old_input)
	{
		old_input = ft_strdup(input);
		add_history_to_file(input);
		add_history(input);
	}
	else if (input[0] && ft_strcmp(input, old_input) != 0)
	{
		add_history_to_file(input);
		add_history(input);
	}
	free(old_input);
	old_input = ft_strdup(input);
}

void	add_history_to_file(char *input)
{
	char		*tmp;
	char		*path;
	static int	fd;

	path = get_history_path();
	tmp = ft_strjoin(input, "\n");
	if (!fd)
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		free(tmp);
		return (free(path));
	}
	ft_putstr_fd(tmp, fd);
	free(path);
	free(tmp);
}	

void	add_file_to_history(void)
{
	char	*tmp;
	int		fd;

	tmp = get_history_path();
	fd = open(tmp, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: cannot access", 2);
		ft_putstr_fd(tmp, 2);
		ft_putstr_fd("\n", 2);
		free(tmp);
		return ;
	}
	free(tmp);
	tmp = get_next_line(fd);
	if (tmp)
		tmp[ft_strlen(tmp) - 1] = 0;
	while (tmp)
	{
		add_history(tmp);
		free(tmp);
		tmp = get_next_line(fd);
		if (tmp)
			tmp[ft_strlen(tmp) - 1] = 0;
	}
	close(fd);
}

char *get_history_path(void)
{
	char	*pwd;
	char	*path;

	pwd = getcwd(NULL, 0);
	ft_protect_malloc(pwd);
	path = ft_strjoin(pwd, "/sources/history/.minishell_history");
	free(pwd);
	return (path);
}
