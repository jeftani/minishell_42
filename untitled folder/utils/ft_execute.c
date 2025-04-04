/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 03:43:46 by ajeftani          #+#    #+#             */
/*   Updated: 2023/07/29 21:13:57 by ajeftani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_back_it(t_lexer *lexer)
{
	if (lexer->details->r_out_file || lexer->details->r_app_file)
	{
		close(1);
		dup2(lexer->original_stdout, 1);
		close(lexer->original_stdout);
	}
}

void	ft_cut(int i, char **cmd, t_lexer *lexer, t_env *environment)
{
	if (i == 5)
		echo(cmd, lexer);
	if (i == 6)
		exit_f(environment, cmd);
	if (i == 7)
		cd(environment, cmd);
}

int	which_command(char **cmd)
{
	if (cmd && (ft_strcmp(cmd[0], "env") == 0))
		return (1);
	if (cmd && (ft_strcmp(cmd[0], "pwd") == 0))
		return (2);
	if (cmd && (ft_strcmp(cmd[0], "export") == 0))
		return (3);
	if (cmd && (ft_strcmp(cmd[0], "unset") == 0))
		return (4);
	if (cmd && (ft_strcmp(cmd[0], "echo") == 0))
		return (5);
	if (cmd && (ft_strcmp(cmd[0], "exit") == 0))
		return (6);
	if (cmd && (ft_strcmp(cmd[0], "cd") == 0))
		return (7);
	else
		return (0);
}

int	check_builtings(char **cmd)
{
	if (cmd && ft_strcmp(cmd[0], "env") == 0)
		return (1);
	if (cmd && ft_strcmp(cmd[0], "pwd") == 0)
		return (1);
	if (cmd && ft_strcmp(cmd[0], "export") == 0)
		return (1);
	if (cmd && ft_strcmp(cmd[0], "unset") == 0)
		return (1);
	if (cmd && ft_strcmp(cmd[0], "unset") == 0)
		return (1);
	if (cmd && ft_strcmp(cmd[0], "echo") == 0)
		return (1);
	if (cmd && ft_strcmp(cmd[0], "exit") == 0)
		return (1);
	if (cmd && ft_strcmp(cmd[0], "cd") == 0)
		return (1);
	else
		return (0);
}

void	ft_execute(t_env *environment, char **cmd, t_lexer *lexer)
{
	int	i;

	i = 0;
	if (lexer->details->r_out_file || lexer->details->r_app_file)
	{
		ft_redirection(lexer);
		check_filed(lexer);
	}
	if (check_builtings(cmd) == 1)
	{
		i = which_command(cmd);
		if (i == 2)
			pwd();
		if (i == 3)
			export(environment, cmd);
		if (i == 1)
			built_env(environment, cmd);
		if (i == 4)
			unset(environment, cmd);
		ft_cut(i, cmd, lexer, environment);
	}
	ft_back_it(lexer);
}
