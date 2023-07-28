/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 03:15:47 by ajeftani          #+#    #+#             */
/*   Updated: 2023/07/27 23:18:42 by ajeftani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_directerror(char *msg, char *utils)
{
	write(2, msg, ft_strlen(msg));
	if (utils)
		write(2, utils, ft_strlen(utils));
	write(2, "\n", 1);
	return (EXIT_FAILURE);
}

void	error_hand(char *str, int n)
{
	if (str)
	{
		ft_putstr_fd(strerror(n), 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
	exit(n);
}

int	ft_puterr(char *cmd, char *arg, char *msg, int errnum)
{
	write(2, "Minishell: ", ft_strlen("minishell: "));
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, arg, ft_strlen(arg));
	write(2, ": ", 2);
	if (!msg)
	{
		perror("");
	}
	else
	{
		write(2, msg, ft_strlen(msg));
		write(2, "\n", 1);
	}
	g_exit = errnum;
	return (errnum);
}

int	ft_puterrfree(char *cmd, char *arg, char *msg, int errnum)
{
	write(2, "Minishell: ", ft_strlen("minishell: "));
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, arg, ft_strlen(arg));
	write(2, ": ", 2);
	if (!msg)
		perror("");
	else
		write(2, arg, ft_strlen(arg));
	g_exit = errnum;
		free(arg);
	return (errnum);
}

void	error_execv(t_lexer *lexer, char **paths)
{
	(void)paths;
	if (lexer->command[0] == 0) //ask about it later
	{
		//free_paths(paths);
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(&lexer->command[0], 2);
		ft_putstr_fd(": Command not found1\n", 2);
		exit(127);
	}
	else if (access(&lexer->command[0], F_OK) == 0)
	{
		//free_paths(paths);
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(&lexer->command[0], 2);
		ft_putstr_fd(": Permission denied\n", 2);
		exit(126);
	}
}
