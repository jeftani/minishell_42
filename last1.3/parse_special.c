/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_special.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloukas <gloukas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:27:12 by gloukas           #+#    #+#             */
/*   Updated: 2023/06/03 14:41:06 by gloukas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_derec(char *cmd_line)
{
	int	i;

	i = ft_strlen(cmd_line) - 1;
	while (cmd_line[i] && (cmd_line[i] == 32 || (cmd_line[i] >= 9
				&& cmd_line[i] <= 13)))
		i--;
	if (cmd_line[i] == '>' || cmd_line[i] == '<')
	{
		g_exit = 258;
		return (1);
	}
	return (0);
}

int	is_valid_closing(int *open_count)
{
	if (*open_count <= 0)
	{
		g_exit = 258;
		return (1);
	}
	(*open_count)--;
	return (0);
}

int	check_parenthesis(char *cmd_line)
{
	int	i;
	int	open_parenthesis;

	open_parenthesis = 0;
	i = 0;
	while (cmd_line[i])
	{
		if (cmd_line[i] == '(')
			open_parenthesis++;
		else if (cmd_line[i] == ')')
		{
			if (is_valid_closing(&open_parenthesis))
				return (1);
		}
		i++;
	}
	if (open_parenthesis > 0)
	{
		g_exit = 258;
		return (1);
	}
	return (0);
}

int	check_braces(char *cmd_line)
{
	int	i;
	int	open_brace;

	open_brace = 0;
	i = 0;
	while (cmd_line[i])
	{
		if (cmd_line[i] == '{')
			open_brace++;
		else if (cmd_line[i] == '}')
		{
			if (is_valid_closing(&open_brace))
				return (1);
		}
		i++;
	}
	if (open_brace > 0)
	{
		g_exit = 258;
		return (1);
	}
	return (0);
}
