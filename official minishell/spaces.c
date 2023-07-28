/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:07:24 by gloukas           #+#    #+#             */
/*   Updated: 2023/07/28 16:09:58 by ajeftani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_inside_quotes(char *cmd_line, int pos)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (i < pos)
	{
		if (cmd_line[i] == '"')
			count++;
		i++;
	}
	return (count % 2);
}

int	is_inside_single_quotes(char *cmd_line, int pos)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (i < pos)
	{
		if (cmd_line[i] == '\'')
			count++;
		i++;
	}
	return (count % 2);
}

int	how_much_outside(char *cmd_line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd_line[i])
	{
		if ((cmd_line[i] == '|' || cmd_line[i] == '<' || cmd_line[i] == '>')
			&& !is_inside_quotes(cmd_line, i)
			&& !is_inside_single_quotes(cmd_line, i))
			//if (cmd_line[i] == '>' || cmd_line[i] == '<')
				count++;
		i++;
	}
	return (2 * count);
}

void	add_spaces_help(char **cmd_line, char **stock, int i, int *j)
{
	if ((*j) > 0 && (*stock)[(*j) - 1] != ' ' && (*stock)[(*j) - 1] != '>'
		&& (*stock)[(*j) - 1] != '<')
		(*stock)[(*j)++] = ' ';
	(*stock)[(*j)++] = (*cmd_line)[i];
	if ((*cmd_line)[i + 1] != '\0' && (*cmd_line)[i + 1] != ' ' && (*cmd_line)[i
		+ 1] != '>' && (*cmd_line)[i + 1] != '<')
		(*stock)[(*j)++] = ' ';
}

void	add_spaces(char **cmd_line)
{
	char	*stock;
	int		i;
	int		j;

	stock = ft_malloc((how_much_outside(*cmd_line) + ft_strlen(*cmd_line) + 1));
	i = -1;
	j = 0;
	while (++i < ft_strlen(*cmd_line))
	{
		if ((*cmd_line)[i] == '|' || (*cmd_line)[i] == '<'
			|| (*cmd_line)[i] == '>')
		{
			if (!is_inside_quotes(*cmd_line, i)
				&& !is_inside_single_quotes(*cmd_line, i))
				add_spaces_help(cmd_line, &stock, i, &j);
			else
				stock[j++] = (*cmd_line)[i];
		}
		else
			stock[j++] = (*cmd_line)[i];
	}
	stock[j] = '\0';
	free(*cmd_line);
	*cmd_line = stock;
}
