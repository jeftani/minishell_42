/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 02:11:11 by ajeftani          #+#    #+#             */
/*   Updated: 2023/07/18 23:26:12 by ajeftani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dir(char *str)
{
	if (!ft_strncmp(".", str, 2))
	{
		ft_putstr_fd("Minishell: .: filename argument required\n", 2);
		ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
		g_exit = 2;
		return (g_exit);
	}
	else if (!ft_strncmp("..", str, 3))
	{
		ft_putstr_fd("Minishell: ..: command not found 9 \n", 2);
		g_exit = 127;
		return (g_exit);
	}
	if (!opendir(str))
		return (0);
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": is a directory\n", 2);
	g_exit = 126;
	return (g_exit);
}

void	check_filed(t_lexer *lexer)
{
	if (lexer && lexer->fd.in != STDIN_FILENO && lexer->fd.in > 0)
	{
		if (dup2(lexer->fd.in, STDIN_FILENO) == -1)
			error_hand("dup2", errno);
		if (close(lexer->fd.in) == -1)
			error_hand("close", errno);
	}
	if (lexer && lexer->fd.out != STDOUT_FILENO && lexer->fd.out > 1)
	{
		if (dup2(lexer->fd.out, STDOUT_FILENO) == -1)
			error_hand("dup2", errno);
		if (close(lexer->fd.out) == -1)
			error_hand("close", errno);
	}
}

void	close_it(t_lexer *lexer)
{
	if (lexer->fd.in != STDIN_FILENO)
		close(lexer->fd.in);
	if (lexer->fd.out != STDOUT_FILENO)
		close(lexer->fd.out);
}

void	check_it(t_lexer *lexer, int fd[2])
{
	if (lexer->command && lexer->next->command)
	{
		lexer->fd.out = fd[1];
		lexer->next->fd.in = fd[0];
	}
}

void	redirect_the_std(t_lexer *lexer)
{
	if (lexer->details->r_in_file == NULL && lexer->fd.in == 0)
	{
		lexer->fd.in = 0;
	}
	if (lexer->details->r_out_file == NULL && lexer->fd.out == 1)
	{
		lexer->fd.out = 1;
	}
	if (lexer->details->r_out_file != NULL)
	{
		lexer->fd.out = 20;
	}
	if (lexer->details->r_in_file != NULL)
	{
		lexer->fd.out = 20;
	}
}
