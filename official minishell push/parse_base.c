/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_base.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloukas <gloukas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 11:54:07 by gloukas           #+#    #+#             */
/*   Updated: 2023/07/28 18:09:39 by gloukas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_empty(char *cmd_line)
{
	int	i;

	if (!ft_strlen(cmd_line))
		return (0);
	i = 0;
	while (cmd_line[i] && (cmd_line[i] == 32 || (cmd_line[i] >= 9
				&& cmd_line[i] <= 13)))
		i++;
	if (!cmd_line[i] || cmd_line[i] == '\n' || cmd_line[i] == ':')
		return (0);
	if (cmd_line[i] == ':')
	{
		g_exit = 0;
		return (0);
	}
	return (1);
}

int	check_oper1(char *cmd_line)
{
	int	i;

	i = 0;
	while (cmd_line[i])
	{
		if ((cmd_line[i] == ';' || cmd_line[i] == '\\')
			&& !is_inside_quotes(cmd_line, i)
			&& !is_inside_single_quotes(cmd_line, i))
			return (1);
		if (cmd_line[i] == '|' && !is_inside_quotes(cmd_line, i)
			&& !is_inside_single_quotes(cmd_line, i))
		{
			i++;
			while (cmd_line[i] && (cmd_line[i] == 32 || (cmd_line[i] >= 9
						&& cmd_line[i] <= 13)))
				i++;
			if (cmd_line[i] && cmd_line[i] == '|')
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
	if (pipe_derec(cmd_line))
		return (1);
	if (!is_empty(cmd_line))
		return (2);
	if (check_oper1(cmd_line) || check_oper2('>', cmd_line) || check_oper2('<',
			cmd_line))
		return (1);
	if (check_pipe(cmd_line, '|') || is_unclosed_quoate(cmd_line)
		|| check_derec(cmd_line) || check_parenthesis(cmd_line)
		|| check_braces(cmd_line))
		return (1);
	return (0);
}
