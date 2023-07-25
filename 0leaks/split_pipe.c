/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:13:29 by gloukas           #+#    #+#             */
/*   Updated: 2023/07/18 21:19:17 by ajeftani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*create_lexer(char *command)
{
	t_lexer	*lexer;

	lexer = (t_lexer *)malloc(sizeof(t_lexer));
	//printf(": ===> file : %s, line : %d, adress: %p\n", __FILE__, __LINE__, lexer);
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
	s->tab = (char *)malloc((ft_strlen(cmd_line) + 1) * sizeof(char));
	//printf(": ===> file : %s, line : %d, adress: %p\n", __FILE__, __LINE__, s->tab);
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
