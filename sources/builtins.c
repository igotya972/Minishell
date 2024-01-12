#include "../includes/minishell.h"

void	launch_builtins(char **inputs)
{
	int	i;

	i = -1;
	while (inputs[++i])
	{
		if (ft_strcmp(inputs[i], "echo") == 0)
			ft_echo(inputs, i);
	}
}

void	ft_echo(char **inputs, int i)
{
	if (inputs[i + 1])
	{
		if (ft_strcmp(inputs[i + 1], "-n") == 0)
		{
			if (inputs[i + 2])
			{
				while (inputs[++i + 1])
				{
					printf("%s", inputs[i + 1]);
					if (inputs[i + 2])
						printf(" ");
				}
			}
			else 
				minishell_prompt();
		}
		else
		{
			while (inputs[++i])
				printf("%s ", inputs[i]);
			printf("\n");
		}
	}
	else
		printf("\n");
}
