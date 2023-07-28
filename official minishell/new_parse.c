/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloukas <gloukas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 08:17:10 by gloukas           #+#    #+#             */
/*   Updated: 2023/07/26 12:07:36 by gloukas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_derec(char *cmd_line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd_line[i])
	{
		if ((cmd_line[i] == '<' || cmd_line[i] == '>')
			&& !is_inside_quotes(cmd_line, i)
			&& !is_inside_single_quotes(cmd_line, i))
		{
			j = i++;
			while (cmd_line[i] && (cmd_line[i] == 32 || (cmd_line[i] >= 9
						&& cmd_line[i] <= 13)))
				i++;
			if (cmd_line[i] && (cmd_line[i] == '|'))
				return (1);
			i = j;
		}
		i++;
	}
	return (0);
}

int	check_oper2(char c, char *cmd_line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd_line[i])
	{
		if (cmd_line[i] == c && !is_inside_quotes(cmd_line, i)
			&& !is_inside_single_quotes(cmd_line, i))
		{
			j = i++;
			if (cmd_line[i] && cmd_line[i] == c)
				j = i++;
			while (cmd_line[i] && (cmd_line[i] == 32 || (cmd_line[i] >= 9
						&& cmd_line[i] <= 13)))
				i++;
			if (cmd_line[i] && (cmd_line[i] == '<' || cmd_line[i] == '>'))
				return (1);
			i = j;
		}
		i++;
	}
	return (0);
}
