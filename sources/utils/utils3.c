#include 	"../../includes/minishell.h"

char	**ft_remove_control_tab(char **str)
{
	int		i;
	int		j;
	int		k;
	char	**tmp;

	i = 0;
	while (str[i])
		i++;
	tmp = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (str[++i])
	{
		j = -1;
		k = -1;
		tmp[i] = malloc(sizeof(char) * (ft_strlen(str[i]) + 1));
		while (str[i][++j])
		{
			if (str[i][j] != 18)
				tmp[i][++k] = str[i][j];
		}
		tmp[i][++k] = '\0';	
	}
	tmp[i] = NULL;
	ft_free_tab(str);
	return (tmp);
}

char	*ft_remove_control(char *str)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = malloc(sizeof(char) * (ft_strlen(str) + 1));
	i = -1;
	j = -1;
	while (str[++i])
		if (str[i] != 18)
			tmp[++j] = str[i];
	tmp[++j] = '\0';
	return (tmp);
}