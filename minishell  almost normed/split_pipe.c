/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloukas <gloukas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:13:29 by gloukas           #+#    #+#             */
/*   Updated: 2023/07/29 22:10:02 by gloukas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*create_lexer(char *command)
{
	t_lexer	*lexer;

	lexer = (t_lexer *)ft_malloc(sizeof(t_lexer));
	if (lexer)
	{
		lexer->command = command;
		lexer->fd.in = 0;
		lexer->fd.out = 1;
		lexer->next = NULL;
	}
	return (lexer);
}

void	split_pipe_help_a(char *cmd_line, t_splity *s)
{
	s->tab = (char *)ft_malloc((ft_strlen(cmd_line) + 1) * sizeof(char));
	if (!(s->tab))
		return ;
	s->i = -1;
	while (cmd_line[++(s->i)])
	{
		if (cmd_line[s->i] == '|' && !is_inside_quotes(cmd_line, s->i)
			&& !is_inside_single_quotes(cmd_line, s->i))
			s->tab[s->i] = '1';
		else
			s->tab[s->i] = '2';
	}
	s->tab[s->i] = '\0';
	s->i = -1;
	s->count = 0;
	while (s->tab[++(s->i)])
		if (s->tab[s->i] == '2' && (s->i == 0 || s->tab[s->i - 1] == '1'))
			(s->count)++;
	s->j = -1;
	s->i = 0;
}

void	split_pipe_help_b(char *cmd_line, t_splity *s, t_lexer **head)
{
	t_lexer	*lexer;
	t_lexer	*temp;

	while (++(s->j) < s->count)
	{
		while (cmd_line[s->i] && s->tab[s->i] == '1')
			(s->i)++;
		s->start = s->i;
		while (cmd_line[s->i] && s->tab[s->i] == '2')
			(s->i)++;
		lexer = create_lexer(ft_substr(cmd_line, s->start, s->i - s->start));
		if (lexer)
		{
			if (*head == NULL)
				*head = lexer;
			else
			{
				temp = *head;
				while (temp->next != NULL)
					temp = temp->next;
				temp->next = lexer;
			}
		}
	}
}

t_lexer	*split_pipe(char *cmd_line)
{
	t_splity	s;
	t_lexer		*head;

	head = NULL;
	split_pipe_help_a(cmd_line, &s);
	split_pipe_help_b(cmd_line, &s, &head);
	free(s.tab);
	return (head);
}

char	*expand_norm(char *cmd_line, char *new, int i)
{
	char	c[2];

	c[0] = cmd_line[i];
	c[1] = '\0';
	new = ft_strjoin(new, c);
	return (new);
}
