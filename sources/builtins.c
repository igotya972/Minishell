#include "../includes/minishell.h"

void	launch_builtins(t_data *data, char **inputs)
{
	int	i;

	i = -1;
	while (inputs[++i])
	{
		if (ft_strcmp(inputs[i], "echo") == 0)
			i += ft_echo(data, inputs, i);
		else if (ft_strcmp(inputs[i], "pwd") == 0)
			ft_pwd();
		//if (ft_strcmp(inputs[i], "env") == 0)
			// ft_env();
	}
}

int	ft_echo(t_data *data, char **inputs, int i)
{
	int	add;

	add = 0;
	if (inputs[i + 1])
	{
		if (ft_strcmp(inputs[i + 1], "-n") == 0)
		{
			if (inputs[i + 2])
			{
				while (inputs[++i + 1])
				{
					add++;
					printf("%s", inputs[i + 1]);
					if (inputs[i + 2])
						printf(" ");
				}
			}
			else 
				minishell_prompt(data);
		}
		else
		{
			while (inputs[++i])
			{
				add++;
				printf("%s ", inputs[i]);
			}
			printf("\n");
		}
	}
	else
		printf("\n");
	return (add);
}

void	ft_pwd(void)
{
	printf("%s\n", getcwd(NULL, 0));
}
