/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 16:12:17 by ajeftani          #+#    #+#             */
/*   Updated: 2023/07/29 10:57:51 by ajeftani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_what_else(char **cmd, int j, int b)
{
	int		i;
	char	*str;

	i = 0;
	if (!cmd[1])
	{
		printf("exit\n");
		exit(0);
	}
	while (cmd[j][b] == ' ')
		b++;
	str = ft_malloc(sizeof(char) * (ft_strlen(cmd[j]) + 1));
	while (cmd[j][b] != '\0')
	{
		if (cmd[j][b] != ' ')
		{
			str[i] = cmd[1][b];
			i++;
		}
		b++;
	}
	str[i] = '\0';
	cmd[1] = str;
	ft_continue5(cmd);
}

void	exit_status(char **cmd, int mark)
{
	if (mark == 1)
	{
		printf("exit\n");
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": too many arguments\n", 2);
	}
	if (mark == 2)
	{
		printf("exit\n");
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	if (mark == 3)
	{
		printf("exit\n");
		exit(255);
	}
}

void	ft_continue5(char **cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (cmd[1][j] == '+' || cmd[1][j] == '-')
		j++;
	if (cmd[1])
	{
		while (cmd[1][j])
		{
			if (ft_isdigit(cmd[1][j]) || (ft_atoi(cmd[1]) != 0
					&& ft_atoi(cmd[1]) != -1))
				j++;
			else
				exit_status(cmd, 2);
		}
		if (cmd[2])
		{
			exit_status(cmd, 1);
			return ;
		}
		printf("exit\n");
		exit(ft_atoi(cmd[1]));
	}
}

void	exit_f(t_env *environment, char **cmd)
{
	int	j;
	int	b;

	(void)environment;
	j = 1;
	b = 0;
	ft_what_else(cmd, j, b);
}
