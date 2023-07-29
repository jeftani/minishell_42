/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quoates.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloukas <gloukas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 02:42:01 by gloukas           #+#    #+#             */
/*   Updated: 2023/07/29 01:27:19 by gloukas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_quoates_c(char **string, char **writeptr, int *i, int *j)
{
	if ((*string)[*i] == '"')
	{
		(*i)++;
		while ((*string)[*i] && (*string)[*i] != '"')
			(*writeptr)[(*j)++] = (*string)[(*i)++];
		(*i)++;
	}
	if ((*string)[*i] && (*string)[*i] == '\'')
	{
		(*i)++;
		while ((*string)[*i] && (*string)[*i] != '\'')
			(*writeptr)[(*j)++] = (*string)[(*i)++];
		(*i)++;
	}
}

void	delete_quoates_b(char *string)
{
	char	*writeptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	writeptr = string;
	while (string[i])
	{
		delete_quoates_c(&string, &writeptr, &i, &j);
		if (string[i] && string[i] != '"' && string[i] != '\'')
			writeptr[j++] = string[i++];
	}
	writeptr[j] = '\0';
}

char	**help_quoates(char **cmd)
{
	int	i;

	i = 0;
	if (cmd != NULL)
	{
		i = 0;
		while (cmd[i])
		{
			delete_quoates_b(cmd[i]);
			i++;
		}
	}
	return (cmd);
}

t_lexer	*delete_quoates_a(t_lexer **lexer)
{
	t_lexer	*head;

	head = *lexer;
	while (head != NULL)
	{
		if (head->details != NULL)
		{
			head->details->string = help_quoates(head->details->string);
			head->details->r_in_file = help_quoates(head->details->r_in_file);
			head->details->r_out_file = help_quoates(head->details->r_out_file);
			head->details->r_app_file = help_quoates(head->details->r_app_file);
			head->details->herdoc_lim = help_quoates(head->details->herdoc_lim);
		}
		head = head->next;
	}
	return (*lexer);
}
