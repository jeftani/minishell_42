/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_base.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 11:54:07 by gloukas           #+#    #+#             */
/*   Updated: 2023/06/23 22:21:02 by ajeftani         ###   ########.fr       */
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
	if (!cmd_line[i])
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
			if (cmd_line[i + 1] == c)
			{
				if (x == 1)
					return (1);
			}
			if (x == 2 && cmd_line[i + 1] == c && cmd_line[i + 2] == c)
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

int	is_unclosed_quoate(char *cmd_line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd_line[i])
	{
		if (cmd_line[i] == '\"')
			count++;
		i++;
	}
	if (count % 2)
		return (1);
	return (0);
}

int	parse(char *cmd_line)
{
	if (!is_empty(cmd_line))
		return (0);
	if (check_oper('|', cmd_line, 1) || check_oper('>', cmd_line, 2)
		|| check_oper('<', cmd_line, 2))
		return (1);
	if (check_pipe(cmd_line, '|') || is_unclosed_quoate(cmd_line)
		|| check_derec(cmd_line) || check_parenthesis(cmd_line)
		|| check_braces(cmd_line))
		return (1);
	return (0);
}
