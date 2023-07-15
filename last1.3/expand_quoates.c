/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quoates.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloukas <gloukas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 02:42:01 by gloukas           #+#    #+#             */
/*   Updated: 2023/07/15 05:43:19 by gloukas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**help_quoates(char **cmd)
{
	int	i;

	i = 0;
	if (cmd != NULL)
	{
		i = 0;
		while (cmd[i])
		{
			cmd[i] = delete_quoates_b(cmd[i]);
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
char	*delete_quoates_b(char *string)
{
	int	length;

	length = strlen(string);
	if (length >= 2 && (string[0] == '"' || string[0] == '\'') && string[length
			- 1] == string[0])
	{
		string[length - 1] = '\0';
		return (string + 1);
	}
	return (string);
}

char	*get_expanded(char *cmd_line, char *new, int *i, t_env *env)
{
	int		start;
	char	*key;
	char	*value;
	int		len;

	start = (*i) + 1;
	while (cmd_line[(*i) + 1] && (cmd_line[(*i) + 1] == '_'
			|| ft_isalnum(cmd_line[(*i) + 1])))
		(*i)++;
	len = (*i) - start + 1;
	key = malloc(len + 1);
	ft_memcpy(key, cmd_line + start, len);
	key[len] = '\0';
	value = search_env_elem1(key, env->env);
	if (value)
		new = ft_strjoin(new, value);
	else
	{
		new = ft_strjoin(new, "");
	}
	free(key);
	return (new);
}

char	*expand(char *cmd_line, t_env *env)
{
	int		i;
	char	*new;
	char	c[2];

	if (!strchr(cmd_line, '$'))
		return (cmd_line);
	i = -1;
	new = ft_strdup("");
	while (cmd_line[++i])
	{
		if (cmd_line[i] == '$' && cmd_line[i + 1] && (cmd_line[i + 1] == ' '
				|| cmd_line[i + 1] == '"' || cmd_line[i + 1] == '\''))
			return (cmd_line);
		if (cmd_line[i] == '$' && cmd_line[i + 1]
			&& (!is_inside_single_quotes(cmd_line, i)
				|| (is_inside_single_quotes(cmd_line, i)
					&& is_inside_quotes(cmd_line, i))))
			new = get_expanded(cmd_line, new, &i, env);
		else
		{
			c[0] = cmd_line[i];
			c[1] = '\0';
			new = ft_strjoin(new, c);
		}
	}
	free(cmd_line);
	return (new);
}
