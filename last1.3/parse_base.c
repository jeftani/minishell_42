/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_base.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloukas <gloukas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 11:54:07 by gloukas           #+#    #+#             */
/*   Updated: 2023/07/16 23:55:09 by gloukas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_empty(char *cmd_line)
{
	int	i;

	if (!ft_strlen(cmd_line))
	{
		g_exit = 0;
		return (0);
	}
	i = 0;
	while (cmd_line[i] && (cmd_line[i] == 32 || (cmd_line[i] >= 9
				&& cmd_line[i] <= 13)))
		i++;
	if (!cmd_line[i] || cmd_line[i] == '\n')
	{
		g_exit = 0;
		return (0);
	}
	return (1);
}

int	check_oper(char c, char *cmd_line, int x)
{
	int	i;

	i = 0;
	while (cmd_line[i])
	{
		if (cmd_line[i] == c)
		{
			if (cmd_line[i + 1] == c && !is_inside_quotes(cmd_line, i)
				&& !is_inside_single_quotes(cmd_line, i))
			{
				if (x == 1)
					return (1);
			}
			if (x == 2 && cmd_line[i + 1] == c && cmd_line[i + 2] == c
				&& !is_inside_quotes(cmd_line, i + 1)
				&& !is_inside_single_quotes(cmd_line, i + 1)
				&& !is_inside_quotes(cmd_line, i + 2)
				&& !is_inside_single_quotes(cmd_line, i + 2))
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_pipe(char *cmd_line, char c)
{
	int	i;

	i = 0;
	while (cmd_line[i] && (cmd_line[i] == 32 || (cmd_line[i] >= 9
				&& cmd_line[i] <= 13)))
		i++;
	if (cmd_line[i] == c)
		return (1);
	i = ft_strlen(cmd_line) - 1;
	while (cmd_line[i] && (cmd_line[i] == 32 || (cmd_line[i] >= 9
				&& cmd_line[i] <= 13)))
		i--;
	if (cmd_line[i] == c)
		return (1);
	return (0);
}

int	check_derec(char *cmd_line)
{
	int	i;

	i = ft_strlen(cmd_line) - 1;
	while (cmd_line[i] && (cmd_line[i] == 32 || (cmd_line[i] >= 9
				&& cmd_line[i] <= 13)))
		i--;
	if ((cmd_line[i] == '>' || cmd_line[i] == '<'))
	{
		g_exit = 258;
		return (1);
	}
	return (0);
}

int	parse(char *cmd_line)
{
	if (!is_empty(cmd_line))
		return (2);
	if (check_oper('|', cmd_line, 1) || check_oper('>', cmd_line, 2)
		|| check_oper('<', cmd_line, 2))
		return (1);
	if (check_pipe(cmd_line, '|') || is_unclosed_quoate(cmd_line)
		|| check_derec(cmd_line) || check_parenthesis(cmd_line)
		|| check_braces(cmd_line))
		return (1);
	return (0);
}
