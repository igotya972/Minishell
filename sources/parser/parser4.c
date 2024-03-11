#include "../../includes/minishell.h"

char	*ft_delimiteur_to_control(char *str)
{
	int		j;
	char	*tmp;
	
	j = -1;
	while (str[++j])
	{
		if ((str[j] == '\"' || str[j] == '\'') && str[j + 1] && is_parser_delimiteur(str[j + 1]) && str[j + 2] && is_parser_delimiteur(str[j + 2]) && str[j + 3] && (str[j + 3] == '\"' || str[j + 3] == '\''))
		{
			tmp = ft_addcontrol(str, j, 0);
			free(str);
			str = tmp;
			j = 0;
		}
		if ((str[j] == '\"' || str[j] == '\'') && str[j + 1] && is_parser_delimiteur(str[j + 1]) && str[j + 2] && (str[j + 2] == '\"' || str[j + 2] == '\''))
		{
			tmp = ft_addcontrol(str, j, 1);
			free(str);
			str = tmp;
			j = 0;
			// i = -1;
			// printf("||||| = ");
			// while (tmp[++i])
			// {
			// 	if (tmp[i] == 18)
			// 		printf("18");
			// 	else
			// 		printf("%c", tmp[i]);
			// }
			// printf("\n");
		}
	}
	// i = -1;
	// printf("$$$$ = ");
	// while (str[++i])
	// {
	// 	if (str[i] == 18)
	// 		printf("18");
	// 	else
	// 		printf("%c", str[i]);
	// }
	// printf("\n");
	tmp = ft_strdup(str);
	free(str);
	return (tmp);
}

char	*ft_addcontrol(char *str, int j, int flag)
{
	char	*tmp2;
	char	*tmp;
	// int		i;

	// printf("%d\n" , j);
	tmp2 = malloc(sizeof(char) * (j + 4 - flag) + 1);
	// printf("str = %s\n", str);
	// printf("j + 2 - flag = %d\n", j + 4 - flag);
	ft_strlcpy(tmp2, str, j + 4 - flag);
	// printf("add = %s\n", tmp2);
	tmp2[j + 3 - flag] = 18;
	tmp2[j + 4 - flag] = '\0';
	// i = -1;
	// printf("?????? = ");
	// while (tmp2[++i])
	// {
	// 	if (tmp2[i] == 18)
	// 		printf("18");
	// 	else
	// 		printf("%d,", tmp2[i]);
	// }
	// printf("\n");
	tmp = ft_strjoin(tmp2, str + j + 3 - flag);
	free(tmp2);
	// i = -1;
	// printf("$$$$ = ");
	// while (tmp[++i])
	// {
	// 	if (tmp[i] == 18)
	// 		printf("18");
	// 	else
	// 		printf("%c", tmp[i]);
	// }
	// printf("\n");
	return (tmp);
}
