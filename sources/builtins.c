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
		else if (ft_strcmp(inputs[i], "env") == 0)
			ft_env(data);
		else if (ft_strcmp(inputs[i], "cd") == 0)
			ft_cd(data, inputs);
		
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
			add++;
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

void	ft_env(t_data *data)
{
	int	i;

	i = -1;
	while (data->envp[++i])
		printf("%s\n", data->envp[i]);
}

void	ft_cd(t_data *data, char **inputs)
{
	(void)data;
	if (inputs[2])
		printf("cd: too many arguments\n");
	else if (inputs[1])
	{
		if (chdir(inputs[1]) == -1)
		{
			printf("cd: %s: No such file or directory\n", inputs[1]);
			return ;
		}
	}
	else
		chdir(getenv("HOME"));
}