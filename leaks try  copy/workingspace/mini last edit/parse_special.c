/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_special.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:27:12 by gloukas           #+#    #+#             */
/*   Updated: 2023/07/27 23:18:42 by ajeftani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_unclosed_quoate(char *cmd_line)
{
	int	booly;
	int	i;

	i = 0;
	booly = 0;
	while (cmd_line[i])
	{
		if (cmd_line[i] == '"' || cmd_line[i] == '\'')
		{
			i++;
			if (cmd_line[i - 1] == '"')
			{
				while (cmd_line[i] && cmd_line[i] != '"')
					i++;
				if (cmd_line[i] == '"')
					booly = 0;
				if (!cmd_line[i])
					booly = 1;
			}
			else if (cmd_line[i - 1] == '\'')
			{
				while (cmd_line[i] && cmd_line[i] != '\'')
					i++;
				if (cmd_line[i] == '\'')
					booly = 0;
				if (!cmd_line[i])
					booly = 1;
			}
		}
		i++;
	}
	return (booly);
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
		if (cmd_line[i] == '(' && !is_inside_quotes(cmd_line, i)
			&& !is_inside_single_quotes(cmd_line, i))
			open_parenthesis++;
		else if (cmd_line[i] == ')' && !is_inside_quotes(cmd_line, i)
				&& !is_inside_single_quotes(cmd_line, i))
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
		if (cmd_line[i] == '{' && !is_inside_quotes(cmd_line, i)
			&& !is_inside_single_quotes(cmd_line, i))
			open_brace++;
		else if (cmd_line[i] == '}' && !is_inside_quotes(cmd_line, i)
				&& !is_inside_single_quotes(cmd_line, i))
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
